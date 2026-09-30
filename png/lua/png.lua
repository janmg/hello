local ffi = require("ffi")
local C = ffi.C

-- Define types
ffi.cdef[[
    typedef unsigned char uint8_t;
    typedef unsigned int uint32_t;
]]

local COLOR_TYPES = {
    [0] = "Grayscale",
    [2] = "RGB",
    [3] = "Indexed (palette)",
    [4] = "Grayscale + Alpha",
    [6] = "RGBA",
}

local INTERLACE_TYPES = {
    [0] = "None",
    [1] = "Adam7",
}

local PNG_SIG = string.char(0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a)

function read_uint32_be(data, offset)
    return (string.byte(data, offset) << 24) +
           (string.byte(data, offset + 1) << 16) +
           (string.byte(data, offset + 2) << 8) +
           string.byte(data, offset + 3)
end

function parse_png(filename)
    local f = io.open(filename, "rb")
    if not f then
        print("Error: File '" .. filename .. "' not found")
        return
    end

    local data = f:read("*all")
    f:close()

    if data:len() < 8 or data:sub(1, 8) ~= PNG_SIG then
        print("Not a valid PNG file")
        return
    end

    print("PNG Signature: Valid")
    print("\n=== PNG Header Information ===")

    local offset = 9  -- Skip signature (1-indexed)
    local width, height, bit_depth, color_type = 0, 0, 0, 0

    while offset <= data:len() - 8 do
        -- Read chunk length (big-endian)
        local chunk_len = read_uint32_be(data, offset)
        offset = offset + 4

        -- Read chunk type
        local chunk_type = data:sub(offset, offset + 3)
        offset = offset + 4

        print("\nChunk: " .. chunk_type .. " (length: " .. chunk_len .. " bytes)")

        if chunk_type == "IHDR" then
            width = read_uint32_be(data, offset)
            height = read_uint32_be(data, offset + 4)
            bit_depth = string.byte(data, offset + 8)
            color_type = string.byte(data, offset + 9)
            local compression = string.byte(data, offset + 10)
            local filter_method = string.byte(data, offset + 11)
            local interlace = string.byte(data, offset + 12)

            print("  Width: " .. width .. " pixels")
            print("  Height: " .. height .. " pixels")
            print("  Bit Depth: " .. bit_depth)
            print("  Color Type: " .. color_type .. " (" .. (COLOR_TYPES[color_type] or "Unknown") .. ")")
            print("  Compression: " .. compression)
            print("  Filter: " .. filter_method)
            print("  Interlace: " .. (INTERLACE_TYPES[interlace] or "Unknown"))

            offset = offset + 13 + 4  -- IHDR data + CRC

        elseif chunk_type == "IDAT" then
            print("  Image data chunk (skipping decompression)")
            offset = offset + chunk_len + 4  -- Skip data + CRC

        elseif chunk_type == "IEND" then
            print("  End of PNG")
            break

        else
            offset = offset + chunk_len + 4  -- Skip data + CRC
        end
    end

    print("\n=== Summary ===")
    print("Dimensions: " .. width .. "x" .. height)
    print("Total pixels: " .. width * height)
    print("Color type: " .. (COLOR_TYPES[color_type] or "Unknown"))
end

local filename = arg[1]
if not filename then
    print("Usage: " .. arg[0] .. " <file.png>")
    os.exit(1)
end
parse_png(filename)
