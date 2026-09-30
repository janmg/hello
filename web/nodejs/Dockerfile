FROM alpine:edge

RUN apk add --no-cache nodejs npm

WORKDIR /usr/src/app
COPY entrypoint.sh /usr/src/app/
COPY *.js* /usr/src/app/

EXPOSE 8080
CMD [ "./entrypoint.sh" ]
