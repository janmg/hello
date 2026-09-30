FROM alpine:edge

RUN apk add --no-cache g++ make boost-dev

WORKDIR /usr/src/app
COPY hello.cpp Makefile /usr/src/app/
RUN make

EXPOSE 8080
CMD ["./hello"]
