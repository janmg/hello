FROM golang:alpine

WORKDIR /usr/src/png
COPY png.go /usr/src/png/png.go

RUN go build -o png png.go

CMD ["./png", "/usr/src/hello/test.png"]
