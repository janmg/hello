FROM alpine:3.5

RUN mkdir -p /usr/src/app \
 && apk update;apk add nodejs

WORKDIR /usr/src/app

COPY package.json /usr/src/app/
RUN npm install

COPY . /usr/src/app

EXPOSE 8002
CMD [ "npm", "start" ]
