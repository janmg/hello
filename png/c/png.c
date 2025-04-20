#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <zlib.h>
#include <SDL2/SDL.h>

#define MAX_SIZE (8 * 1024 * 1024)
#define CHUNK 16 * 1024

static const uint8_t SIGNATURE[8] = {137, 80, 78, 71, 13, 10, 26, 10};

struct Chunk
{
    uint32_t length;
    char type[4];
    // unsigned char *data; // would make a great pointer to keep track off
    uint32_t crc;
};

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
    fprintf(stderr, "%s\n", errtext);
    exit(errno);
}

uint32_t flip_byte_order(uint32_t value)
{
    return ((value & 0xFF) << 24) | ((value & 0xFF00) << 8) | ((value & 0xFF0000) >> 8) | ((value & 0xFF000000) >> 24);
}

void print_hex(const unsigned char *buffer, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%02X ", buffer[i]);
        if ((i + 1) % 16 == 0)
        {
            printf("\n");
        }
    }
    if (size % 16 != 0)
    {
        printf("\n");
    }
}

void display_image(const unsigned char *buffer, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *win = SDL_CreateWindow("Decompressed Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return;
    }

    // Create an SDL texture from the decompressed image buffer
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, width, height);
    if (!texture) {
        fprintf(stderr, "SDL_CreateTexture Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return;
    }

    SDL_UpdateTexture(texture, NULL, buffer, width * 3); // Assuming RGB format

    // Render loop
    SDL_Event event;
    int running = 1;
    while (running) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
            running = 0;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

// litteral copy of zpipe.c
int inflate_buffer(FILE *source, FILE *dest, uint32_t compressed_size)
{
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    // Decompress loop
    while (compressed_size > 0) {
        // Calculate how much to read
        size_t bytes_to_read = (compressed_size > CHUNK) ? CHUNK : compressed_size;

        // Read data from the source file into the input buffer
        size_t bytes_read = fread(in, 1, bytes_to_read, source);
        if (bytes_read == 0 && ferror(source)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }

        strm.avail_in = (unsigned)bytes_read;
        strm.next_in = in;
        compressed_size -= bytes_read;

        // Decompress and write to the destination file
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);

            // Handle zlib errors
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR; /* Fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }

            have = CHUNK - strm.avail_out;

            // Write decompressed data to the destination
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);

        // Stop on the end of the stream
        if (ret == Z_STREAM_END)
            break;
    }

    // Clean up and return
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

int main(int argc, char **argv)
{
    int width;
    int height;
    int size;
    FILE *output_stream = tmpfile();

    if (argc != 2)
    {
        char usage_msg[256];
        sprintf(usage_msg, "Usage: %s <png file>", argv[0]);
        error(1, usage_msg);
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f)
    {
        perror("fopen");
        error(3, "file failed to open");
    }
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    // PNG Signature (8 bytes)
    char *sig = (char *)malloc(sizeof(SIGNATURE));
    fread(sig, 1, sizeof(SIGNATURE), f);
    if (memcmp(SIGNATURE, sig, sizeof(SIGNATURE)) != 0)
    {
        error(4, "Invalid PNG signature");
    }
    // print_hex(sig, 8);
    free(sig);

    while (ftell(f) < file_size)
    {
        struct Chunk chunk;

        // chunksize
        fread(&chunk.length, sizeof(uint32_t), 1, f);
        // printf("%04x\n",chunk.length);
        chunk.length = flip_byte_order(chunk.length);
        // printf("%d\n",chunk.length);

        // chunktype
        fread(&chunk.type, 4, 1, f);

        printf("chunk: %.4s at %ld - len: %d (%ld)\n", chunk.type, ftell(f), chunk.length, file_size - ftell(f) - chunk.length - 4);
        bool found = false;
        if (strncmp("IHDR", chunk.type, 4) == 0)
        {
            found = true;
            char chunkbuf[chunk.length];
            fread(chunkbuf, 1, chunk.length, f);
            struct IHDR *ihdr = (struct IHDR *)chunkbuf;
            width = flip_byte_order(ihdr->width);
            height = flip_byte_order(ihdr->height);
            int pixelsize = width * height;
            printf("  width: %u x height: %u = %d\n", width, height, pixelsize);
            printf("  compression type: %u\n", ihdr->compression); // it's always zero, so always use zlib
            fread(&chunk.crc, 1, 4, f);
            chunk.crc = flip_byte_order(chunk.crc);
        }
        if (strncmp("IDAT", chunk.type, 4) == 0)
        {
            found = true;

            if (!output_stream)
            {
                error(5, "Failed to create temporary file for decompression.");
            }

            // Decompress the data from the chunk into the temporary file
            int ret = inflate_buffer(f, output_stream, chunk.length);
            if (ret != Z_OK)
            {
                error(6, "Decompression failed.");
            }

            // Rewind the temporary file to the beginning for reading
            size = ftell(output_stream);
            rewind(output_stream); // be kind

            // Close and clean up the temporary file
            //fclose(output_stream);

            // Read CRC from the original PNG file
            fread(&chunk.crc, 1, 4, f);
            chunk.crc = flip_byte_order(chunk.crc);
        }
        if (strncmp("IEND", chunk.type, 4) == 0)
        {
            found = true;
            break;
        }
        if (!found)
        {
            exit(9);
        }
    }

    // Read and process the decompressed data
    char *buffer = (char *)malloc(size);
    fread(buffer, 1, size, output_stream);
    
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(f);
        return 1;
    }

    // Display the image
    display_image(buffer, width, height);

    //free(buffer);
    fclose(f);
    // free(buf);
    return 0;
}
