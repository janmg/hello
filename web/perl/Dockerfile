FROM alpine:edge

RUN apk add --no-cache perl

WORKDIR /usr/src/app
COPY hello-world.pl /usr/src/app/

EXPOSE 8080
CMD ["perl", "hello-world.pl"]
