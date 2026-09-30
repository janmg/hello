#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <sstream>

const std::vector<uint8_t> PNG_SIG = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};

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

uint32_t read_uint32_be(const std::vector<uint8_t>& data, size_t offset) {
    return (static_cast<uint32_t>(data[offset]) << 24) |
           (static_cast<uint32_t>(data[offset + 1]) << 16) |
           (static_cast<uint32_t>(data[offset + 2]) << 8) |
           static_cast<uint32_t>(data[offset + 3]);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file.png>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open file '" << argv[1] << "'" << std::endl;
        return 1;
    }

    std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
    file.close();

    if (data.size() < 8) {
        std::cout << "Not a valid PNG file" << std::endl;
        return 0;
    }

    if (std::vector<uint8_t>(data.begin(), data.begin() + 8) != PNG_SIG) {
        std::cout << "Not a valid PNG file" << std::endl;
        return 0;
    }

    std::cout << "PNG Signature: Valid" << std::endl;
    std::cout << "\n=== PNG Header Information ===" << std::endl;

    size_t offset = 8;
    uint32_t width = 0, height = 0;
    uint8_t bit_depth = 0, color_type = 0;

    while (offset < data.size()) {
        if (offset + 4 > data.size()) break;

        uint32_t chunk_len = read_uint32_be(data, offset);
        offset += 4;

        if (offset + 4 > data.size()) break;
        std::string chunk_type(data.begin() + offset, data.begin() + offset + 4);
        offset += 4;

        std::cout << "\nChunk: " << chunk_type << " (length: " << chunk_len << " bytes)" << std::endl;

        if (chunk_type == "IHDR") {
            if (offset + 13 > data.size()) break;

            width = read_uint32_be(data, offset);
            height = read_uint32_be(data, offset + 4);
            bit_depth = data[offset + 8];
            color_type = data[offset + 9];
            uint8_t compression = data[offset + 10];
            uint8_t filter_method = data[offset + 11];
            uint8_t interlace = data[offset + 12];

            std::cout << "  Width: " << width << " pixels" << std::endl;
            std::cout << "  Height: " << height << " pixels" << std::endl;
            std::cout << "  Bit Depth: " << static_cast<int>(bit_depth) << std::endl;
            std::cout << "  Color Type: " << static_cast<int>(color_type) << " (" << color_type_name(color_type) << ")" << std::endl;
            std::cout << "  Compression: " << static_cast<int>(compression) << std::endl;
            std::cout << "  Filter: " << static_cast<int>(filter_method) << std::endl;
            std::cout << "  Interlace: " << interlace_name(interlace) << std::endl;

            offset += 13 + 4;  // IHDR data + CRC
        } else if (chunk_type == "IDAT") {
            std::cout << "  Image data chunk (skipping decompression)" << std::endl;
            offset += chunk_len + 4;  // Skip data + CRC
        } else if (chunk_type == "IEND") {
            std::cout << "  End of PNG" << std::endl;
            break;
        } else {
            offset += chunk_len + 4;  // Skip data + CRC
        }
    }

    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "Dimensions: " << width << "x" << height << std::endl;
    std::cout << "Total pixels: " << width * height << std::endl;
    std::cout << "Color type: " << color_type_name(color_type) << std::endl;

    return 0;
}
