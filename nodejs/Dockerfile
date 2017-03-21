FROM alpine:edge

WORKDIR /usr/src/app

COPY entrypoint.sh /usr/src/app/
COPY *.js* /usr/src/app/
#COPY nodejs.* /usr/src/app/
#COPY ca.crt /usr/local/share/ca-certificates/

# && update-ca-certificates \
RUN apk --update --no-cache add nodejs nodejs-npm \
 && npm install http2 \
 && npm install

EXPOSE 8002
CMD [ "./entrypoint.sh" ]
