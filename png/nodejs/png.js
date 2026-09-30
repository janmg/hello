const fs = require('fs');
const path = require('path');

const COLOR_TYPES = {
    0: "Grayscale",
    2: "RGB",
    3: "Indexed (palette)",
    4: "Grayscale + Alpha",
    6: "RGBA",
};

const INTERLACE_TYPES = {
    0: "None",
    1: "Adam7",
};

function parsePNG(filename) {
    if (!fs.existsSync(filename)) {
        console.error(`Error: File '${filename}' not found`);
        process.exit(1);
    }

    const buffer = fs.readFileSync(filename);

    // Verify PNG signature
    const sig = Buffer.from([0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a]);
    if (!buffer.slice(0, 8).equals(sig)) {
        console.log("Not a valid PNG file");
        return;
    }
    console.log("PNG Signature: Valid");
    console.log("\n=== PNG Header Information ===");

    let width = 0, height = 0, bitDepth = 0, colorType = 0;

    let offset = 8; // Skip signature

    while (offset < buffer.length) {
        // Read chunk length (big-endian)
        const chunkLen = buffer.readUInt32BE(offset);
        offset += 4;

        // Read chunk type
        const chunkType = buffer.slice(offset, offset + 4).toString('ascii');
        offset += 4;

        console.log(`\nChunk: ${chunkType} (length: ${chunkLen} bytes)`);

        if (chunkType === 'IHDR') {
            width = buffer.readUInt32BE(offset);
            height = buffer.readUInt32BE(offset + 4);
            bitDepth = buffer.readUInt8(offset + 8);
            colorType = buffer.readUInt8(offset + 9);
            const compression = buffer.readUInt8(offset + 10);
            const filterMethod = buffer.readUInt8(offset + 11);
            const interlace = buffer.readUInt8(offset + 12);

            console.log(`  Width: ${width} pixels`);
            console.log(`  Height: ${height} pixels`);
            console.log(`  Bit Depth: ${bitDepth}`);
            console.log(`  Color Type: ${colorType} (${COLOR_TYPES[colorType] || 'Unknown'})`);
            console.log(`  Compression: ${compression}`);
            console.log(`  Filter: ${filterMethod}`);
            console.log(`  Interlace: ${INTERLACE_TYPES[interlace] || 'Unknown'}`);

            offset += 13; // IHDR data
            offset += 4;  // CRC

        } else if (chunkType === 'IDAT') {
            console.log("  Image data chunk (skipping decompression)");
            offset += chunkLen + 4; // Skip data + CRC

        } else if (chunkType === 'IEND') {
            console.log("  End of PNG");
            break;

        } else {
            offset += chunkLen + 4; // Skip data + CRC
        }
    }

    console.log("\n=== Summary ===");
    console.log(`Dimensions: ${width}x${height}`);
    console.log(`Total pixels: ${width * height}`);
    console.log(`Color type: ${COLOR_TYPES[colorType] || 'Unknown'}`);
}

const filename = process.argv[2];
if (!filename) {
    console.log(`Usage: ${process.argv[1]} <file.png>`);
    process.exit(1);
}
parsePNG(filename);
