FROM alpine:edge

RUN apk add --no-cache python3

WORKDIR /usr/src/png
COPY png_parser.py /usr/src/png/png_parser.py

CMD ["python3", "png_parser.py", "/usr/src/hello/test.png"]
