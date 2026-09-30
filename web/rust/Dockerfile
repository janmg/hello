FROM alpine:edge

RUN apk add --no-cache rust

WORKDIR /usr/src/app
COPY hello.rs index.html style.css /usr/src/app/
RUN rustc hello.rs -o hello

EXPOSE 8080
CMD ["/usr/src/app/hello"]
