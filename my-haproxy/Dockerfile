FROM alpine:edge

COPY entrypoint.sh /
COPY dummy.pem /etc/letsencrypt/live/aws.islief.com/fullchain.pem

RUN apk --update --no-cache add libressl haproxy inotify-tools ca-certificates curl libcap ruby ruby-io-console ruby-bundler \
 && curl -sSLo /usr/bin/acme-webroot.lua https://github.com/janeczku/haproxy-acme-validation-plugin/raw/master/acme-http01-webroot.lua \
 && setcap 'cap_net_bind_service,cap_sys_chroot+ep' /usr/sbin/haproxy \
 && gem install haproxyctl --no-rdoc --no-ri

ENTRYPOINT ["./entrypoint.sh"]
