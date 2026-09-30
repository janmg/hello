import http.server
import socketserver
from http import HTTPStatus

class Handler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/style.css':
            self.send_response(HTTPStatus.OK)
            self.send_header('Content-Type', 'text/css')
            self.end_headers()
            self.wfile.write(b"#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: #3776AB;font-size: 40px; }")
        else:
            self.send_response(HTTPStatus.OK)
            self.end_headers()
            self.wfile.write(b"<html><head><link rel='stylesheet' type='text/css' href='/style.css' integrity='sha384-4WJdVTMawfOcN7Ew6t1hVmEftXkAvAeca5zw5h7D1p0BEusQdIGs67otru/PlhRb' /></head><body><div id='main'>Hello, World! ... brought to you by Python</div></body></html>")

# "Content-Type", "text/html; charset=utf-8"
# "Content-Type", "text/css; charset=utf-8"

httpd = socketserver.TCPServer(('', 8080), Handler)
httpd.serve_forever()
