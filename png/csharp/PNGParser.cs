using System;
using System.IO;

class PNGParser
{
    private static readonly byte[] PNG_SIG = {
        0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a
    };

    private static readonly string[] COLOR_TYPES = {
        "", "Unknown", "RGB", "Indexed (palette)", "Grayscale + Alpha",
        "Unknown", "Unknown", "Unknown", "RGBA"
    };

    private static readonly string[] INTERLACE_TYPES = { "None", "Adam7" };

    static void Main(string[] args)
    {
        if (args.Length != 1)
        {
            Console.WriteLine($"Usage: {typeof(PNGParser).Assembly.GetName().Name} <file.png>");
            return;
        }

        if (!File.Exists(args[0]))
        {
            Console.WriteLine($"Error: File '{args[0]}' not found");
            return;
        }

        try
        {
            var data = File.ReadAllBytes(args[0]);

            if (data.Length < 8 || !data.Take(8).SequenceEqual(PNG_SIG))
            {
                Console.WriteLine("Not a valid PNG file");
                return;
            }

            Console.WriteLine("PNG Signature: Valid");
            Console.WriteLine("\n=== PNG Header Information ===");

            int offset = 8;
            int width = 0, height = 0, bitDepth = 0, colorType = 0;

            while (offset < data.Length - 12)
            {
                // Read chunk length (big-endian)
                uint chunkLen = ((uint)data[offset] << 24) |
                                ((uint)data[offset + 1] << 16) |
                                ((uint)data[offset + 2] << 8) |
                                data[offset + 3];
                offset += 4;

                // Read chunk type
                string chunkType = System.Text.Encoding.ASCII.GetString(data, offset, 4);
                offset += 4;

                Console.WriteLine($"\nChunk: {chunkType} (length: {chunkLen} bytes)");

                if (chunkType == "IHDR")
                {
                    width = ((int)data[offset] << 24) | ((int)data[offset + 1] << 16) |
                            ((int)data[offset + 2] << 8) | data[offset + 3];
                    height = ((int)data[offset + 4] << 24) | ((int)data[offset + 5] << 16) |
                             ((int)data[offset + 6] << 8) | data[offset + 7];
                    bitDepth = data[offset + 8];
                    colorType = data[offset + 9];
                    int compression = data[offset + 10];
                    int filterMethod = data[offset + 11];
                    int interlace = data[offset + 12];

                    Console.WriteLine($"  Width: {width} pixels");
                    Console.WriteLine($"  Height: {height} pixels");
                    Console.WriteLine($"  Bit Depth: {bitDepth}");
                    Console.WriteLine($"  Color Type: {colorType} ({(colorType < COLOR_TYPES.Length ? COLOR_TYPES[colorType] : "Unknown")})");
                    Console.WriteLine($"  Compression: {compression}");
                    Console.WriteLine($"  Filter: {filterMethod}");
                    Console.WriteLine($"  Interlace: {(interlace < INTERLACE_TYPES.Length ? INTERLACE_TYPES[interlace] : "Unknown")}");

                    offset += 13; // IHDR data
                    offset += 4;  // CRC
                }
                else if (chunkType == "IDAT")
                {
                    Console.WriteLine("  Image data chunk (skipping decompression)");
                    offset += (int)chunkLen + 4; // Skip data + CRC
                }
                else if (chunkType == "IEND")
                {
                    Console.WriteLine("  End of PNG");
                    break;
                }
                else
                {
                    offset += (int)chunkLen + 4; // Skip data + CRC
                }
            }

            Console.WriteLine("\n=== Summary ===");
            Console.WriteLine($"Dimensions: {width}x{height}");
            Console.WriteLine($"Total pixels: {width * height}");
            Console.WriteLine($"Color type: {(colorType < COLOR_TYPES.Length ? COLOR_TYPES[colorType] : "Unknown")}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }
}
