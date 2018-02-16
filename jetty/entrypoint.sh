#!/bin/sh
setfattr -n user.pax.flags -v "mr" /usr/bin/java
/usr/bin/java -cp "*" com.islief.HelloWorld 8003
