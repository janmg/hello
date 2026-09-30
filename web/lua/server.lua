local socket = require("socket")

local html = [[<html><head><link rel='stylesheet' type='text/css' href='/style.css' integrity='sha384-McfmMBFBHnAalktBoJzUL7/UZ7sHCHQonjVXi+OvaJxesNq/+p11BUcxvtjesP1c' /></head><body><div id='main'>Hello, World! ... brought to you by Lua</div></body></html>]]
local css  = "#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: #000080;font-size: 40px; }"

local server = socket.tcp()
server:setoption("reuseaddr", true)
server:bind("0.0.0.0", 8080)
server:listen(10)

print("Server running on port 8080...")

while true do
    local client = server:accept()
    
    local request = client:receive()
    
    if request:match("GET / ") then
        local response = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n" .. html
        client:send(response .. "\r\n")
    elseif request:match("GET /style.css ") then
        local response = "HTTP/1.1 200 OK\r\nContent-Type: text/css\r\n\r\n" .. css
        client:send(response .. "\r\n")
    end
    
    client:close()
end
