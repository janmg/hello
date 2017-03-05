# https://eclipse.org/jetty/documentation/current/advanced-embedding.html#jetty-helloworld
FROM alpine:edge 

WORKDIR /usr/src/

COPY *.jar entrypoint.sh /usr/src/

RUN apk add --update --no-cache openjdk8 \
 && chmod +x entrypoint.sh

EXPOSE 8003
CMD [ "./entrypoint.sh" ]
