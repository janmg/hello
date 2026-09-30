use std::fs;
use std::env;

const INTERLACE_TYPES: [&str; 2] = ["None", "Adam7"];

fn color_type_name(ct: u8) -> &'static str {
    match ct {
        0 => "Grayscale",
        2 => "RGB",
        3 => "Indexed (palette)",
        4 => "Grayscale + Alpha",
        6 => "RGBA",
        _ => "Unknown",
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 2 {
        eprintln!("Usage: {} <file.png>", args[0]);
        std::process::exit(1);
    }

    let filename = &args[1];
    let data = match fs::read(filename) {
        Ok(d) => d,
        Err(e) => {
            eprintln!("Error: File '{}' not found: {}", filename, e);
            std::process::exit(1);
        }
    };

    let png_sig = [0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a];
    if data.len() < 8 || data[..8] != png_sig {
        println!("Not a valid PNG file");
        return;
    }

    println!("PNG Signature: Valid");
    println!("\n=== PNG Header Information ===");

    let mut offset = 8;
    let mut width: u32 = 0;
    let mut height: u32 = 0;
    let mut bit_depth: u8 = 0;
    let mut color_type: u8 = 0;

    while offset < data.len() {
        if offset + 8 > data.len() {
            break;
        }

        let chunk_len = u32::from_be_bytes([
            data[offset], data[offset + 1],
            data[offset + 2], data[offset + 3]
        ]);
        offset += 4;

        if offset + 4 > data.len() {
            break;
        }
        let chunk_type = String::from_utf8_lossy(&data[offset..offset + 4]);
        offset += 4;

        println!("\nChunk: {} (length: {} bytes)", chunk_type, chunk_len);

        if chunk_type == "IHDR" {
            if offset + 13 > data.len() {
                break;
            }
            width = u32::from_be_bytes([
                data[offset], data[offset + 1],
                data[offset + 2], data[offset + 3]
            ]);
            height = u32::from_be_bytes([
                data[offset + 4], data[offset + 5],
                data[offset + 6], data[offset + 7]
            ]);
            bit_depth = data[offset + 8];
            color_type = data[offset + 9];
            let compression = data[offset + 10];
            let filter_method = data[offset + 11];
            let interlace = data[offset + 12];

            println!("  Width: {} pixels", width);
            println!("  Height: {} pixels", height);
            println!("  Bit Depth: {}", bit_depth);
            println!("  Color Type: {} ({})", color_type, color_type_name(color_type));
            println!("  Compression: {}", compression);
            println!("  Filter: {}", filter_method);
            println!("  Interlace: {}", INTERLACE_TYPES[interlace as usize]);

            offset += 17; // IHDR data (13) + CRC (4)
        } else if chunk_type == "IDAT" {
            println!("  Image data chunk (skipping decompression)");
            if offset + chunk_len as usize + 4 > data.len() {
                break;
            }
            offset += chunk_len as usize + 4; // Skip data + CRC
        } else if chunk_type == "IEND" {
            println!("  End of PNG");
            break;
        } else {
            if offset + chunk_len as usize + 4 > data.len() {
                break;
            }
            offset += chunk_len as usize + 4; // Skip data + CRC
        }
    }

    println!("\n=== Summary ===");
    println!("Dimensions: {}x{}", width, height);
    println!("Total pixels: {}", width * height);
    println!("Color type: {}", color_type_name(color_type));
}
