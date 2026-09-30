FROM alpine:edge

RUN apk add --no-cache openjdk21

WORKDIR /usr/src/app
COPY WebServerApp.java /usr/src/app/
RUN javac WebServerApp.java

EXPOSE 8080
CMD ["java", "-cp", "/usr/src/app", "WebServerApp"]
