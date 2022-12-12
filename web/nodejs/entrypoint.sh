#!/bin/sh
setfattr -n user.pax.flags -v "mr" /usr/bin/node
npm start
