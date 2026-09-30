FROM alpine:edge

RUN apk add --no-cache gcc musl-dev

WORKDIR /usr/src/app
COPY minimal-web-server.c /usr/src/app/
RUN gcc -o server minimal-web-server.c

EXPOSE 8080
CMD ["/usr/src/app/server"]
