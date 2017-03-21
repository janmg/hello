var http = require('http2');
var fs = require('fs');
var options = {
  key: fs.readFileSync('/etc/letsencrypt/live/aws.islief.com/privkey.pem'),
  cert: fs.readFileSync('/etc/letsencrypt/live/aws.islief.com/fullchain.pem')
};
var html = "<html><body><div style='position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Arial, Helvetica, sans-serif;color: green;font-size: 40px;'>Hello, World! ... brought to you by NodeJS</div></body></html>";

http.createServer(options, function(request, response) {
    response.writeHead(200, {'Content-Type': 'text/html'},{'Connection': 'keep-alive'},{'Content-Length': html.length});
    response.end(html);
}).listen(8002);
