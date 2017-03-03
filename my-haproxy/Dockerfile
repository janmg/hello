FROM alpine:edge

RUN apk update \
 && apk upgrade \
 && apk --no-cache add libressl haproxy ca-certificates curl libcap ruby ruby-io-console ruby-bundler \
 && rm -rf /var/cache/apk/* \
 && curl -sSLo /etc/haproxy/acme-webroot.lua https://github.com/janeczku/haproxy-acme-validation-plugin/raw/master/acme-http01-webroot.lua \
 && setcap 'cap_net_bind_service,cap_sys_chroot+ep' /usr/sbin/haproxy \
 && gem install haproxyctl --no-rdoc --no-ri

COPY entrypoint.sh /
ENTRYPOINT ["/entrypoint.sh"]
CMD ["haproxy", "-f", "/etc/haproxy/haproxy.cfg"]

