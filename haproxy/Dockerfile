FROM alpine:edge

COPY entrypoint.sh /
COPY hosts /etc/hosts
COPY ca.crt /usr/local/share/ca-certificates/
COPY haproxy.pem /etc/letsencrypt/live/aws.islief.com/fullchain.pem

RUN apk --update --no-cache add libressl haproxy inotify-tools certbot curl libcap \
 && curl -sSLo /usr/bin/acme-webroot.lua https://github.com/janeczku/haproxy-acme-validation-plugin/raw/master/acme-http01-webroot.lua \
 && setcap 'cap_net_bind_service,cap_sys_chroot+ep' /usr/sbin/haproxy \
 && update-ca-certificates 

ENTRYPOINT ["./entrypoint.sh"]
