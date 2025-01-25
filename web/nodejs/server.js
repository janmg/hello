const http = require('http');
var html = "<html><body><div id='main'>Hello, World! ... brought to you by NodeJS</div></body></html>";
var css  = "#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: green;font-size: 40px; }";

const server = http.createServer((req, res) => {
  res.end(html);
}).listen(8002);
