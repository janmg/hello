FROM 138546162266.dkr.ecr.eu-central-1.amazonaws.com/haproxy-base:latest

COPY haproxy.cfg /etc/haproxy/haproxy.cfg
RUN  apk update \
     && apk add libcap \
     && addgroup haproxy \
     && adduser -H -D -S -G haproxy -s /sbin/nologin haproxy \
     && mkdir -p /usr/local/run/ \
     && chown -R haproxy:haproxy /usr/local/ \
     && chown haproxy:haproxy /etc/haproxy/haproxy.cfg \
     && chown haproxy:haproxy /run \
     && setcap 'cap_net_bind_service=+ep' /usr/local/sbin/haproxy

USER haproxy
ENTRYPOINT ["/docker-entrypoint.sh"]
CMD ["haproxy", "-f", "/etc/haproxy/haproxy.cfg"]
