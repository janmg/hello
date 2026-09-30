#!/usr/bin/env perl
use strict;
use warnings;

my %color_types = (
    0 => "Grayscale",
    2 => "RGB",
    3 => "Indexed (palette)",
    4 => "Grayscale + Alpha",
    6 => "RGBA",
);

my %interlace_types = (
    0 => "None",
    1 => "Adam7",
);

sub main {
    my $filename = $ARGV[0];
    if (!$filename) {
        print "Usage: $0 <file.png>\n";
        exit 1;
    }

    unless (-f $filename) {
        print "Error: File '$filename' not found\n";
        exit 1;
    }

    open(my $fh, '<:raw', $filename) or die "Cannot open file: $!";
    my $sig;
    read($fh, $sig, 8);

    my $expected_sig = "\x89PNG\r\n\x1a\n";
    if ($sig ne $expected_sig) {
        print "Not a valid PNG file\n";
        close($fh);
        return;
    }
    print "PNG Signature: Valid\n";
    print "\n=== PNG Header Information ===\n";

    my ($width, $height, $bit_depth, $color_type) = (0) x 4;

    while (1) {
        my $pos = tell($fh);
        last if $pos < 0;

        # Read chunk length (big-endian)
        my $chunk_len;
        my $bytes = read($fh, $chunk_len, 4);
        last unless $bytes;
        $chunk_len = unpack('N', $chunk_len);  # Big-endian unsigned 32-bit

        # Read chunk type
        my $chunk_type;
        read($fh, $chunk_type, 4);

        print "\nChunk: $chunk_type (length: $chunk_len bytes)\n";

        if ($chunk_type eq 'IHDR') {
            my $ihdr;
            read($fh, $ihdr, 13);
            my ($w, $h, $bd, $ct, $comp, $filt, $il) = unpack('NNCCCCC', $ihdr);

            $width = $w;
            $height = $h;
            $bit_depth = $bd;
            $color_type = $ct;

            print "  Width: $w pixels\n";
            print "  Height: $h pixels\n";
            print "  Bit Depth: $bd\n";
            print "  Color Type: $ct (" . ($color_types{$ct} // 'Unknown') . ")\n";
            print "  Compression: $comp\n";
            print "  Filter: $filt\n";
            print "  Interlace: " . ($interlace_types{$il} // 'Unknown') . "\n";

            # Skip CRC
            read($fh, my $crc, 4);

        } elsif ($chunk_type eq 'IDAT') {
            print "  Image data chunk (skipping decompression)\n";
            seek($fh, $chunk_len + 4, 1);  # Skip data + CRC

        } elsif ($chunk_type eq 'IEND') {
            print "  End of PNG\n";
            last;

        } else {
            seek($fh, $chunk_len + 4, 1);  # Skip data + CRC
        }
    }

    print "\n=== Summary ===\n";
    print "Dimensions: ${width}x${height}\n";
    print "Total pixels: " . ($width * $height) . "\n";
    print "Color type: " . ($color_types{$color_type} // 'Unknown') . "\n";

    close($fh);
}

main();
