#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static const uint8_t PNG_SIG[8] = {137, 80, 78, 71, 13, 10, 26, 10};

const char* color_type_name(uint8_t ct) {
    switch(ct) {
        case 0: return "Grayscale";
        case 2: return "RGB";
        case 3: return "Indexed (palette)";
        case 4: return "Grayscale + Alpha";
        case 6: return "RGBA";
        default: return "Unknown";
    }
}

const char* interlace_name(uint8_t il) {
    switch(il) {
        case 0: return "None";
        case 1: return "Adam7";
        default: return "Unknown";
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file.png>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("Cannot open file");
        return 1;
    }

    uint8_t sig[8];
    fread(sig, 1, 8, f);
    if (memcmp(sig, PNG_SIG, 8) != 0) {
        fprintf(stderr, "Not a valid PNG file\n");
        fclose(f);
        return 1;
    }
    printf("PNG Signature: Valid\n");
    printf("\n=== PNG Header Information ===\n");

    uint32_t width = 0, height = 0;
    uint8_t bit_depth = 0, color_type = 0;

    while (1) {
        long pos = ftell(f);
        if (pos < 0) break;

        uint8_t len_bytes[4];
        fread(len_bytes, 1, 4, f);
        uint32_t chunk_len = (len_bytes[0] << 24) | (len_bytes[1] << 16) |
                             (len_bytes[2] << 8) | len_bytes[3];

        char chunk_type[5] = {0};
        fread(chunk_type, 1, 4, f);

        printf("\nChunk: %.4s (length: %u bytes)\n", chunk_type, chunk_len);

        if (strcmp(chunk_type, "IHDR") == 0) {
            uint8_t ihdr_data[13];
            fread(ihdr_data, 1, 13, f);

            width = (ihdr_data[0] << 24) | (ihdr_data[1] << 16) |
                    (ihdr_data[2] << 8) | ihdr_data[3];
            height = (ihdr_data[4] << 24) | (ihdr_data[5] << 16) |
                     (ihdr_data[6] << 8) | ihdr_data[7];
            bit_depth = ihdr_data[8];
            color_type = ihdr_data[9];
            uint8_t compression = ihdr_data[10];
            uint8_t filter_method = ihdr_data[11];
            uint8_t interlace = ihdr_data[12];

            printf("  Width: %u pixels\n", width);
            printf("  Height: %u pixels\n", height);
            printf("  Bit Depth: %u\n", bit_depth);
            printf("  Color Type: %u (%s)\n", color_type, color_type_name(color_type));
            printf("  Compression: %u\n", compression);
            printf("  Filter: %u\n", filter_method);
            printf("  Interlace: %s\n", interlace_name(interlace));

            fseek(f, 4, SEEK_CUR);  // Skip CRC

        } else if (strcmp(chunk_type, "IDAT") == 0) {
            printf("  Image data chunk (skipping decompression)\n");
            fseek(f, chunk_len + 4, SEEK_CUR);

        } else if (strcmp(chunk_type, "IEND") == 0) {
            printf("  End of PNG\n");
            break;

        } else {
            fseek(f, chunk_len + 4, SEEK_CUR);
        }
    }

    printf("\n=== Summary ===\n");
    printf("Dimensions: %ux%u\n", width, height);
    printf("Total pixels: %u\n", width * height);
    printf("Color type: %s\n", color_type_name(color_type));

    fclose(f);
    return 0;
}
