#!/usr/bin/perl
use IO::Socket::INET;

my $html = '<html><head><style>#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: #000080;font-size: 40px; }</style></head><body><div id="main">Hello, World! ... brought to you by Perl</div></body></html>';
my $css  = "#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: #000080;font-size: 40px; }";

my $server = IO::Socket::INET->new(
    LocalAddr => '0.0.0.0',
    LocalPort => 8080,
    Proto     => 'tcp',
    Listen    => 10,
    ReuseAddr => 1,
) or die "Cannot create server: $!";

print "Server running on port 8080...\n";

while (my $client = $server->accept()) {
    my $request = $client->getline();
    
    if ($request =~ /\/style\.css/) {
        my $response = "HTTP/1.1 200 OK\r\n" .
                       "Content-Type: text/css\r\n" .
                       "Content-Length: " . length($css) . "\r\n" .
                       "Connection: close\r\n" .
                       "\r\n" . $css;
        $client->print($response);
    } else {
        my $response = "HTTP/1.1 200 OK\r\n" .
                       "Content-Type: text/html; charset=utf-8\r\n" .
                       "Content-Length: " . length($html) . "\r\n" .
                       "Connection: close\r\n" .
                       "\r\n" . $html;
        $client->print($response);
    }
    $client->close();
}
$server->close();
