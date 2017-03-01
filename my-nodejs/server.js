var http = require('http');
var response = "<html><body><div style="position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Arial, Helvetica, sans-serif;color: green;font-size: 40px;">Hello, World! ... brought to you by NodeJS</div></body></html>";

http.createServer(function (request, response) {
    response.writeHead(200, {'Content-Type': 'text/html'},{'Connection': 'keep-alive'},{'Content-Length': response.length});
    response.end(response);
}).listen(8002);
