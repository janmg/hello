FROM alpine:edge

RUN apk add --no-cache openjdk21

WORKDIR /usr/src/png
COPY PNGParser.java /usr/src/png/PNGParser.java

RUN javac PNGParser.java

CMD ["java", "PNGParser", "/usr/src/hello/test.png"]
