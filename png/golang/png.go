package main

import (
	"fmt"
	"os"
)

var pngSig = []byte{137, 80, 78, 71, 13, 10, 26, 10}

func colorTypeName(ct uint8) string {
	switch ct {
	case 0:
		return "Grayscale"
	case 2:
		return "RGB"
	case 3:
		return "Indexed (palette)"
	case 4:
		return "Grayscale + Alpha"
	case 6:
		return "RGBA"
	default:
		return "Unknown"
	}
}

func interlaceName(il uint8) string {
	switch il {
	case 0:
		return "None"
	case 1:
		return "Adam7"
	default:
		return "Unknown"
	}
}

func main() {
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Usage: %s <file.png>\n", os.Args[0])
		os.Exit(1)
	}

	f, err := os.Open(os.Args[1])
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error: %v\n", err)
		os.Exit(1)
	}
	defer f.Close()

	// Read PNG signature
	sig := make([]byte, 8)
	f.Read(sig)
	if !bytesEqual(sig, pngSig) {
		fmt.Println("Not a valid PNG file")
		return
	}
	fmt.Println("PNG Signature: Valid")
	fmt.Println("\n=== PNG Header Information ===")

	var width, height uint32
	var bitDepth, colorType, compression, filterMethod, interlace uint8

	for {
		// Read chunk length
		var chunkLen uint32
		if err := readUint32(f, &chunkLen); err != nil {
			break
		}

		// Read chunk type
		chunkTypeBytes := make([]byte, 4)
		f.Read(chunkTypeBytes)
		chunkType := string(chunkTypeBytes)

		fmt.Printf("\nChunk: %s (length: %d bytes)\n", chunkType, chunkLen)

		if chunkType == "IHDR" {
			ihdrData := make([]byte, 13)
			f.Read(ihdrData)

			width = uint32(ihdrData[0])<<24 | uint32(ihdrData[1])<<16 | uint32(ihdrData[2])<<8 | uint32(ihdrData[3])
			height = uint32(ihdrData[4])<<24 | uint32(ihdrData[5])<<16 | uint32(ihdrData[6])<<8 | uint32(ihdrData[7])
			bitDepth = ihdrData[8]
			colorType = ihdrData[9]
			compression = ihdrData[10]
			filterMethod = ihdrData[11]
			interlace = ihdrData[12]

			fmt.Printf("  Width: %d pixels\n", width)
			fmt.Printf("  Height: %d pixels\n", height)
			fmt.Printf("  Bit Depth: %d\n", bitDepth)
			fmt.Printf("  Color Type: %d (%s)\n", colorType, colorTypeName(colorType))
			fmt.Printf("  Compression: %d\n", compression)
			fmt.Printf("  Filter: %d\n", filterMethod)
			fmt.Printf("  Interlace: %s\n", interlaceName(interlace))

			// Skip CRC
			f.Read(make([]byte, 4))

		} else if chunkType == "IDAT" {
			fmt.Println("  Image data chunk (skipping decompression)")
			skipChunk(f, chunkLen)

		} else if chunkType == "IEND" {
			fmt.Println("  End of PNG")
			break

		} else {
			skipChunk(f, chunkLen)
		}
	}

	fmt.Println("\n=== Summary ===")
	fmt.Printf("Dimensions: %dx%d\n", width, height)
	fmt.Printf("Total pixels: %d\n", width * height)
	fmt.Printf("Color type: %s\n", colorTypeName(colorType))
}

func bytesEqual(a, b []byte) bool {
	return string(a) == string(b)
}

func readUint32(f *os.File, val *uint32) error {
	buf := make([]byte, 4)
	_, err := f.Read(buf)
	if err != nil {
		return err
	}
	*val = uint32(buf[0])<<24 | uint32(buf[1])<<16 | uint32(buf[2])<<8 | uint32(buf[3])
	return nil
}

func skipChunk(f *os.File, chunkLen uint32) {
	f.Read(make([]byte, chunkLen))
	f.Read(make([]byte, 4)) // CRC
}
