FROM alpine:edge

RUN apk add --no-cache lua lua-posix lua-socket

WORKDIR /usr/src/app
COPY server.lua /usr/src/app/

EXPOSE 8080
CMD ["lua5.5", "server.lua"]
