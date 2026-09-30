FROM alpine:edge

RUN apk --update --no-cache add libressl haproxy inotify-tools libcap \
 && setcap 'cap_net_bind_service,cap_sys_chroot+ep' /usr/sbin/haproxy 

COPY entrypoint.sh /
COPY haproxy.cfg /etc/haproxy/

ENTRYPOINT ["./entrypoint.sh"]
