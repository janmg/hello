// https://medium.com/@0xwan/png-structure-for-beginner-8363ce2a9f73
// https://sourceforge.net/p/libpng/code/ci/master/tree/png.c#l1958
// http://www.libpng.org/pub/png/libpng-manual.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <zlib.h>

#define MAX_SIZE (16 * 1024 * 1024)

static const uint8_t SIGNATURE[8] = {137, 80, 78, 71, 13, 10, 26, 10};

struct IHDR
{
	uint32_t width;
	uint32_t height;
	uint8_t colorsize;
	uint8_t colortype;
	uint8_t compression;
	uint8_t filter;
	uint8_t enlacement;
};

void error(int errno, const char *errtext)
{
	fprintf(stderr, "%s", errtext);
	exit(errno);
}

int flip_char_order(const char *buf)
{
	return ((unsigned char)buf[0] << 24) | ((unsigned char)buf[1] << 16) | ((unsigned char)buf[2] << 8) | (unsigned char)buf[3];
}

uint32_t flip_byte_order(uint32_t value)
{
	return ((value & 0xFF) << 24) | ((value & 0xFF00) << 8) | ((value & 0xFF0000) >> 8) | ((value & 0xFF000000) >> 24);
}


int decompress_data(const char *input, size_t input_size, char *output, size_t output_size)
{
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = input_size;
    stream.next_in = (Bytef *)input;
    stream.avail_out = output_size;
    stream.next_out = (Bytef *)output;

    if (inflateInit(&stream) != Z_OK) { error(6,"Failed to initialize zlib");}
    int result = inflate(&stream, Z_FINISH);
    if (result != Z_STREAM_END) { error(7, "Failed to decompress data");} // could have included result to the error message
    inflateEnd(&stream);
    return stream.total_out; // Returns the size of decompressed data
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		char usage_msg[256];
		sprintf(usage_msg, "Usage: %s <png file>", argv[0]);
		error(1, usage_msg);
	}
	char *buf = (char *)malloc(MAX_SIZE);
	if (!buf) { error(2, "Couldn't allocate memory"); }
	FILE *f = fopen(argv[1], "r");
	if (!f)
	{
		perror("fopen");
		free(buf);
		error(3, "file failed to open");
	}
	int size = fread(buf, 1, MAX_SIZE, f);
	if (strncmp(SIGNATURE, buf, 8) != 0) { error(4, "Couldn't allocate memory"); }
	int pos = 8;
	while (pos < size)
	{
		char lenbuf[4];
		memcpy(lenbuf, buf + pos, 4);
		int len = flip_char_order(lenbuf);
		char type[4];
		memcpy(type, buf+pos+4, 4);
		char chunkbuf[len];
		memcpy(chunkbuf, buf+pos+8, len);
		printf("chunk: %s at %d - len: %d (%d)\n", type, pos, len, size - (pos + len + 12));
		pos += len + 12;
		int width = 0;
		int height = 0;
		int size = 0;
		if (strncmp("IHDR", type, 4) == 0)
		{
			struct IHDR *ihdr = (struct IHDR *)chunkbuf;
			width = flip_byte_order(ihdr->width);
			height = flip_byte_order(ihdr->height);
			size = width * height;
			printf("  width: %u x height: %u = %d\n", width, height, size);
			// printf("  compression type: %u\n", ihdr->compression); // it's always zero, so always use zlib
		}
		if (strncmp("IDAT", type, 4) == 0)
		{
			char output[16000000];
			int decompressed_size = decompress_data(chunkbuf, len, output, sizeof(output));
			if (decompressed_size == 0) { error(5, "Decompression failed"); }
			printf("Decompressed %d bytes: %s\n", decompressed_size, output);
		}
		if (strncmp("IEND", type, 4) == 0)
			break;
	}

	fclose(f);
	free(buf);
	return 0;
}
