FROM golang:1.10rc2-alpine3.7 

WORKDIR /usr/src/app
COPY hello-world.go /usr/src/app

EXPOSE 8080
CMD [ "go", "run", "hello-world.go" ]
