var http = require('http');

http.createServer(function(request, response) {
  var headers = request.headers;
  var method = request.method;
  var url = request.url;
  var body = [];

  request.on('error', function(err) {
    console.error(err);
  }).on('data', function(chunk) {
    body.push(chunk);
  }).on('end', function() {
    body = Buffer.concat(body).toString();

    response.writeHead(200, {'Content-Type': 'text/html'});
    response.end('<html><body><div style="position:absolute;top:50%;left:40;margin-top:-50px;right:-40;text-align: center;font-family: Arial, Helvetica, sans-serif;color: green;font-size: 40px;">Hello, World! ... brought to you by NodeJS</div></body></html>');
  });
}).listen(8002);

