FROM alpine:edge

RUN apk add --no-cache python3 py3-flask

WORKDIR /usr/src/app
COPY app.py /usr/src/app/

EXPOSE 8080
CMD ["python3", "app.py"]
