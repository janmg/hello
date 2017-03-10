#!/bin/sh
openssl genrsa -out dummy.key 2048
openssl req -new -key dummy.key -out dummy.csr -subj "/O=islief/CN=aws.islief.com"
openssl x509 -req -days 3650 -in dummy.csr -signkey dummy.key -out dummy.crt
cat dummy.crt dummy.key > dummy.pem
