FROM alpine:edge

RUN apk add --no-cache gcc musl-dev zlib-dev

WORKDIR /usr/src/png
COPY . /usr/src/png/

RUN make

CMD ["./png", "/usr/src/hello/test.png"]
