# Hello World - Lua

A simple HTTP web server in Lua using the `lua-posix` library.

## Running locally

```bash
lua server.lua
```

Then visit `http://localhost:8002/`

## Running with Docker

```bash
docker build -t lua-hello .
docker run -p 8002:8002 lua-hello
```
