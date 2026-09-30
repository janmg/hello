FROM alpine:edge

RUN apk add --no-cache g++

WORKDIR /usr/src/png
COPY png.cpp /usr/src/png/png.cpp

RUN g++ -o png png.cpp

CMD ["./png", "/usr/src/hello/test.png"]
