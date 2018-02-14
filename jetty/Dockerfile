FROM alpine:edge AS builder
WORKDIR /usr/src/jetty/
COPY src/ src/ 
COPY pom.xml .
RUN apk update && \
    apk add maven openjdk8 && \
    mvn package install

FROM alpine:edge
WORKDIR /usr/app
COPY entrypoint.sh /usr/app
COPY --from=builder /usr/src/jetty/target/*.jar /usr/app/
RUN apk update && \
    apk upgrade && \
    apk add --no-cache attr openjdk8-jre openjdk8-jre-base

EXPOSE 8080
CMD [ "/usr/app/entrypoint.sh" ]
