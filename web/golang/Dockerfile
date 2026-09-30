FROM alpine:edge

RUN apk add --no-cache go

WORKDIR /usr/src/app
COPY hello-world.go /usr/src/app/

EXPOSE 8080
CMD ["go", "run", "hello-world.go"]
