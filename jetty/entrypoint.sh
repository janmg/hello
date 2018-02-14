#!/bin/sh
setfattr -n user.pax.flags -v "mr" /usr/bin/java
/usr/bin/java -cp HelloJetty-1.0.1.jar:http2-common.jar:http2-hpack.jar:http2-server.jar:javax.servlet-api.jar:jetty-http.jar:jetty-io.jar:jetty-server.jar:jetty-util.jar com.islief.HelloWorld 8003
