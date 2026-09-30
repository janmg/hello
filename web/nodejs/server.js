const http = require('http');
var html = "<html><head><link rel='stylesheet' type='text/css' href='/style.css' integrity='sha384-lJswbKW/6brO1pRBk6ghoNTKkNs44AyjW5EtLSWVU7RTX3Pec7GqFWv2c2oeDOgi' /></head><body><div id='main'>Hello, World! ... brought to you by NodeJS</div></body></html>";
var css  = "#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: #4386b8;font-size: 40px; }";

const server = http.createServer((req, res) => {
  if (req.url === '/style.css') {
    res.writeHead(200, {'Content-Type': 'text/css'});
    res.end(css);
  } else {
    res.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});
    res.end(html);
  }
}).listen(8080);
