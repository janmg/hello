FROM alpine:latest

RUN apk add --no-cache lua lua-posix

WORKDIR /usr/src/app
COPY server.lua /usr/src/app/

EXPOSE 8002
CMD ["lua", "server.lua"]
