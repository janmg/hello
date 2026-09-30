FROM rust:alpine

WORKDIR /usr/src/png
COPY png.rs /usr/src/png/png.rs

RUN rustc png.rs

CMD ["./png", "/usr/src/hello/test.png"]
