import java.io.*;
import java.nio.*;

public class PNGParser {
    private static final byte[] PNG_SIG = {
        (byte)0x89, 'P', 'N', 'G', '\r', '\n', (byte)0x1a, '\n'
    };

    private static final String[] COLOR_TYPES = {
        "", "Unknown", "RGB", "Indexed (palette)", "Grayscale + Alpha", "Unknown", "Unknown", "Unknown", "RGBA"
    };

    private static final String[] INTERLACE_TYPES = {
        "None", "Adam7"
    };

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: PNGParser <file.png>");
            System.exit(1);
        }

        try (FileInputStream fis = new FileInputStream(args[0])) {
            byte[] sig = fis.readAllBytes();
            if (sig.length < 8) {
                System.out.println("Not a valid PNG file");
                return;
            }

            if (!java.util.Arrays.equals(java.util.Arrays.copyOf(sig, 8), PNG_SIG)) {
                System.out.println("Not a valid PNG file");
                return;
            }
            System.out.println("PNG Signature: Valid");
            System.out.println("\n=== PNG Header Information ===");

            int offset = 8;
            int width = 0, height = 0, bitDepth = 0, colorType = 0;

            while (offset < sig.length - 12) {
                // Read chunk length (big-endian)
                int chunkLen = ((sig[offset] & 0xFF) << 24) |
                               ((sig[offset + 1] & 0xFF) << 16) |
                               ((sig[offset + 2] & 0xFF) << 8) |
                               (sig[offset + 3] & 0xFF);
                offset += 4;

                // Read chunk type
                String chunkType = new String(sig, offset, 4, "ASCII");
                offset += 4;

                System.out.println("\nChunk: " + chunkType + " (length: " + chunkLen + " bytes)");

                if (chunkType.equals("IHDR")) {
                    width = ((sig[offset] & 0xFF) << 24) |
                            ((sig[offset + 1] & 0xFF) << 16) |
                            ((sig[offset + 2] & 0xFF) << 8) |
                            (sig[offset + 3] & 0xFF);
                    height = ((sig[offset + 4] & 0xFF) << 24) |
                             ((sig[offset + 5] & 0xFF) << 16) |
                             ((sig[offset + 6] & 0xFF) << 8) |
                             (sig[offset + 7] & 0xFF);
                    bitDepth = sig[offset + 8] & 0xFF;
                    colorType = sig[offset + 9] & 0xFF;
                    int compression = sig[offset + 10] & 0xFF;
                    int filterMethod = sig[offset + 11] & 0xFF;
                    int interlace = sig[offset + 12] & 0xFF;

                    System.out.println("  Width: " + width + " pixels");
                    System.out.println("  Height: " + height + " pixels");
                    System.out.println("  Bit Depth: " + bitDepth);
                    System.out.println("  Color Type: " + colorType + " (" +
                        (colorType < COLOR_TYPES.length ? COLOR_TYPES[colorType] : "Unknown") + ")");
                    System.out.println("  Compression: " + compression);
                    System.out.println("  Filter: " + filterMethod);
                    System.out.println("  Interlace: " +
                        (interlace < INTERLACE_TYPES.length ? INTERLACE_TYPES[interlace] : "Unknown"));

                    offset += 13; // IHDR data
                    offset += 4;  // CRC

                } else if (chunkType.equals("IDAT")) {
                    System.out.println("  Image data chunk (skipping decompression)");
                    offset += chunkLen + 4; // Skip data + CRC

                } else if (chunkType.equals("IEND")) {
                    System.out.println("  End of PNG");
                    break;

                } else {
                    offset += chunkLen + 4; // Skip data + CRC
                }
            }

            System.out.println("\n=== Summary ===");
            System.out.println("Dimensions: " + width + "x" + height);
            System.out.println("Total pixels: " + (width * height));
            System.out.println("Color type: " +
                (colorType < COLOR_TYPES.length ? COLOR_TYPES[colorType] : "Unknown"));

        } catch (FileNotFoundException e) {
            System.err.println("Error: File '" + args[0] + "' not found");
            System.exit(1);
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
