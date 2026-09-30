FROM alpine:edge

RUN apk add --no-cache perl

WORKDIR /usr/src/png
COPY png.pl /usr/src/png/png.pl

CMD ["perl", "png.pl", "/usr/src/hello/test.png"]
