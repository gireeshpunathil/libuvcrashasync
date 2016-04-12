# libuvcrashasync
A test case which demonstrates libuv crash through usage of async routines

foo.cc: Native source which makes use of 5 threads, and each calls async routines
foo.js: a wrapper around the native addon
plugin.node: The native addon, biult for linux x64
core.8286.gz: system dump generated after few seconds of execution, compressed
