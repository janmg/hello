FROM alpine:edge AS builder
WORKDIR /usr/src/jetty/
COPY src/ src/ 
COPY pom.xml .
RUN apk update && \
    apk add maven openjdk17 && \
    mvn versions:update-properties && \
    mvn package install

FROM alpine:edge
WORKDIR /usr/app
COPY entrypoint.sh /usr/app
COPY --from=builder /usr/src/jetty/target/*.jar /usr/app/
RUN apk update && \
    apk --no-cache upgrade && \
    apk --no-cache add attr openjdk8-jre

EXPOSE 8080
CMD [ "/usr/app/entrypoint.sh" ]
