# https://github.com/million12/docker-haproxy/blob/master/container-files/bootstrap.sh

# http://serverfault.com/questions/580595/haproxy-graceful-reload-with-zero-packet-loss

SO_REUSEPORT
  haproxy -sf
  
DROP SYN
  http://marc.info/?l=haproxy&m=133262017329084&w=2
  iptables -I INPUT -p tcp --dport $PORT --syn -j DROP
  sleep 1
  service haproxy restart
  iptables -D INPUT -p tcp --dport $PORT --syn -j DROP
  
TC QDISC
  https://engineeringblog.yelp.com/2015/04/true-zero-downtime-haproxy-reloads.html
  sudo nl-qdisc-add --dev=lo --parent=1:4 --id=40: --update plug --buffer &> /dev/null
  ./haproxy -f /tmp/haproxy.cfg -p /tmp/haproxy.pid -sf $(cat /tmp/haproxy.pid)
  sudo nl-qdisc-add --dev=lo --parent=1:4 --id=40: --update plug--release-indefinite &> /dev/null

MULTIBINDER
  https://githubengineering.com/glb-part-2-haproxy-zero-downtime-zero-delay-reloads-with-multibinder/
  https://github.com/github/multibinder

## STATIC CONTENT ##
https://www.mail-archive.com/haproxy@formilux.org/msg15007.html
listen http-webservices
    bind :8200
    monitor-uri /favicon.ico
    errorfile 200 /etc/haproxy/errorfiles/favicon.ico

https://github.com/haproxy/haproxy/blob/master/ROADMAP	
return-html code xxx [ file "xxx" | text "xxx" ] if <acl>

