#Use updated Makefile with -fPIC 
cp Makefile src/quickjs

node-gyp build LIBQUICKJS_PATH=~/Documents/my-quickjs-addon/src/quickjs