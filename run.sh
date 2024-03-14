# update linker if needed
export LDFLAGS="-L$PWD/src/quickjs:$LDFLAGS" 
export LIBQUICKJS_PATH=$PWD/src/quickjs

#Use updated Makefile with -fPIC 
cp Makefile src/quickjs

npx node-gyp  configure build 
