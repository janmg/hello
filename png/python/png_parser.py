#!/usr/bin/env python3
"""PNG Parser - Standalone PNG header parser for testing."""

import struct
import sys


COLOR_TYPES = {
    0: "Grayscale",
    2: "RGB",
    3: "Indexed (palette)",
    4: "Grayscale + Alpha",
    6: "RGBA",
}

INTERLACE_TYPES = {
    0: "None",
    1: "Adam7",
}


def parse_png(filename):
    try:
        with open(filename, "rb") as f:
            sig = f.read(8)
            if sig != b"\x89PNG\r\n\x1a\n":
                print("Not a valid PNG file")
                return

            print("PNG Signature: Valid")
            print("\n=== PNG Header Information ===")

            width = height = bit_depth = color_type = 0

            while True:
                pos = f.tell()
                if pos < 0:
                    break

                chunk_len_bytes = f.read(4)
                if not chunk_len_bytes:
                    break
                chunk_len = struct.unpack(">I", chunk_len_bytes)[0]

                chunk_type = f.read(4).decode("ascii")
                print(f"\nChunk: {chunk_type} (length: {chunk_len} bytes)")

                if chunk_type == "IHDR":
                    ihdr_data = f.read(13)
                    width, height, bit_depth, color_type = struct.unpack(
                        ">IIBB", ihdr_data[:10]
                    )
                    compression, filter_method, interlace = struct.unpack(
                        "BBB", ihdr_data[10:]
                    )

                    print(f"  Width: {width} pixels")
                    print(f"  Height: {height} pixels")
                    print(f"  Bit Depth: {bit_depth}")
                    print(f"  Color Type: {color_type} ({COLOR_TYPES.get(color_type, 'Unknown')})")
                    print(f"  Compression: {compression}")
                    print(f"  Filter: {filter_method}")
                    print(f"  Interlace: {INTERLACE_TYPES.get(interlace, 'Unknown')}")

                    f.read(4)  # Skip CRC

                elif chunk_type == "IDAT":
                    print("  Image data chunk (skipping decompression)")
                    f.read(chunk_len + 4)

                elif chunk_type == "IEND":
                    print("  End of PNG")
                    break

                else:
                    f.read(chunk_len + 4)

            print(f"\n=== Summary ===")
            print(f"Dimensions: {width}x{height}")
            print(f"Total pixels: {width * height}")
            print(f"Color type: {COLOR_TYPES.get(color_type, 'Unknown')}")

    except FileNotFoundError:
        print(f"Error: File '{filename}' not found")
        sys.exit(1)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <file.png>")
        sys.exit(1)
    parse_png(sys.argv[1])
