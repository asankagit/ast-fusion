# update linker if needed
export LDFLAGS="-L/home/asanka/Documents/my-quickjs-addon/src/quickjs $LDFLAGS" 

#Use updated Makefile with -fPIC 
cp Makefile src/quickjs

node-gyp build LIBQUICKJS_PATH=~/Documents/my-quickjs-addon/src/quickjs
