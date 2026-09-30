FROM alpine:edge

RUN apk add --no-cache python3

WORKDIR /usr/src/app
COPY hello-world.py /usr/src/app/

EXPOSE 8080
CMD ["python3", "hello-world.py"]
