FROM 138546162266.dkr.ecr.eu-central-1.amazonaws.com/golang-base:latest

WORKDIR /usr/src/app
COPY hello-world.go /usr/src/app

EXPOSE 8001
CMD [ "go", "run", "hello-world.go" ]
