#!/bin/sh
#https://github.com/million12/docker-haproxy/blob/master/container-files/bootstrap.sh

set -u

HAPROXY_CONFIG=${HAPROXY_CONFIG:="/etc/haproxy/haproxy.cfg"}
HAPROXY_PID_FILE="/var/run/haproxy.pid"
HAPROXY_CMD="haproxy -f ${HAPROXY_CONFIG} -p ${HAPROXY_PID_FILE}"
HAPROXY_CHECK_CONFIG_CMD="haproxy -f ${HAPROXY_CONFIG} -c"

${HAPROXY_CHECK_CONFIG_CMD}
${HAPROXY_CMD}
# Exit immidiately in case of any errors or when we have interactive terminal
if [[ $? != 0 ]] || test -t 0; then exit $?; fi


while inotifywait -q -e create,delete,modify,attrib ${HAPROXY_CONFIG}; do
  ${HAPROXY_CHECK_CONFIG_CMD} > /dev/null
  if [ $? -eq 0 ]; then
    ${HAPROXY_CMD} -sf $(cat ${HAPROXY_PID_FILE})
  fi
done
