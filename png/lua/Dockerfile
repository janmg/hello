FROM alpine:edge

RUN apk add --no-cache lua54 lua54-ffi

WORKDIR /usr/src/png
COPY png.lua /usr/src/png/png.lua

CMD ["lua5.4", "png.lua", "/usr/src/hello/test.png"]
