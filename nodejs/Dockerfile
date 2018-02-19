FROM alpine:edge

WORKDIR /usr/src/app

COPY entrypoint.sh /usr/src/app/
COPY *.js* /usr/src/app/

RUN apk --update --no-cache add attr nodejs-current \
 && wget https://nodejs.org/dist/v9.5.0/node-v9.5.0-linux-x64.tar.xz \
 && tar --no-same-owner -xf node-v9.5.0-linux-x64.tar.xz node-v9.5.0-linux-x64/lib/node_modules --strip 1 -C /usr \
 && ln -s /usr/lib/node_modules/ /usr/bin/ \
 && ln -s ../lib/node_modules/npm/bin/npm /usr/bin/npm \
 && npm install npm@next -g \
 && rm -rf /usr/bin/node_modules/ \
 && rm -rf node-v9.5.0-linux-x64.tar.xz \
 && npm install

EXPOSE 8002
CMD [ "./entrypoint.sh" ]
