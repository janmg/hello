#!/bin/sh

HAPROXY_CONFIG="/etc/haproxy/haproxy.cfg"
HAPROXY_PID_FILE="/var/run/haproxy.pid"

# Wait for backend containers to be resolvable
echo "Waiting for backends to be available..."
for i in $(seq 1 30); do
    if getent hosts golang > /dev/null 2>&1 && \
       getent hosts nodejs > /dev/null 2>&1 && \
       getent hosts java > /dev/null 2>&1 && \
       getent hosts csharp > /dev/null 2>&1 && \
       getent hosts python > /dev/null 2>&1 && \
       getent hosts python-flask > /dev/null 2>&1 && \
       getent hosts perl > /dev/null 2>&1 && \
       getent hosts rust > /dev/null 2>&1 && \
       getent hosts lua > /dev/null 2>&1 && \
       getent hosts c-web > /dev/null 2>&1 && \
       getent hosts cpp > /dev/null 2>&1; then
        echo "All backends resolved!"
        break
    fi
    sleep 1
done

# Validate config
haproxy -c -f "$HAPROXY_CONFIG"

# Start haproxy
haproxy -f "$HAPROXY_CONFIG" -p "$HAPROXY_PID_FILE"
