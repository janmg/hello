# PNG Parsers

Standalone PNG header parsers for various programming languages. Each parser reads a PNG file and displays its header information including dimensions, color type, bit depth, and other metadata.

## Languages

- **C** - Uses zlib for potential decompression, SDL2 for optional image display
- **C++** - Uses Boost.Beast-style binary parsing
- **Go** - Pure Go implementation with no external dependencies
- **Java** - Uses Java NIO ByteBuffer for binary parsing
- **Python** - Uses struct module for binary unpacking
- **Perl** - Uses pack/unpack for binary data handling
- **Rust** - Pure Rust with no external crates
- **Lua** - Uses LuaJIT FFI for binary operations
- **Node.js** - Uses Buffer API for binary parsing
- **C#** - Uses System.IO for file reading

## Usage

```bash
# C
cd c
make
./png test.png

# C++
cd c++
g++ -o png png.cpp
./png test.png

# Go
cd golang
go run png.go test.png

# Java
cd java
javac PNGParser.java
java PNGParser test.png

# Python
cd python
python3 png_parser.py test.png

# Perl
cd perl
perl png.pl test.png

# Rust
cd rust
rustc png.rs
./png test.png

# Lua
cd lua
lua png.lua test.png

# Node.js
cd nodejs
node png.js test.png

# C#
cd csharp
dotnet run --project .
```

## Output Format

All parsers produce consistent output:

```
PNG Signature: Valid

=== PNG Header Information ===

Chunk: IHDR (length: 13 bytes)
  Width: 2 pixels
  Height: 2 pixels
  Bit Depth: 8
  Color Type: 6 (RGBA)
  Compression: 0
  Filter: 0
  Interlace: None

Chunk: IDAT (length: XX bytes)
  Image data chunk (skipping decompression)

Chunk: IEND (length: 0 bytes)
  End of PNG

=== Summary ===
Dimensions: 2x2
Total pixels: 4
Color type: RGBA
```

## PNG Structure

A PNG file consists of:
1. **Signature** - 8-byte magic number identifying PNG format
2. **Chunks** - Each chunk contains:
   - Length (4 bytes, big-endian)
   - Type (4 bytes: IHDR, IDAT, IEND, etc.)
   - Data (variable length)
   - CRC (4 bytes, checksum)

### Key Chunks

- **IHDR** - Image header with dimensions, color type, bit depth
- **IDAT** - Image data (compressed with zlib)
- **IEND** - End of PNG file

### Color Types

| Code | Description |
|------|-------------|
| 0 | Grayscale |
| 2 | RGB |
| 3 | Indexed (palette) |
| 4 | Grayscale + Alpha |
| 6 | RGBA |
