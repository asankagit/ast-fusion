# update linker if needed
export LDFLAGS="-L/home/asanka/Documents/ast-fusion/src/quickjs:$LDFLAGS" 
export LIBQUICKJS_PATH=/home/asanka/Documents/ast-fusion/src/quickjs

#Use updated Makefile with -fPIC 
cp Makefile src/quickjs

# npx node-gyp  configure build --LIBQUICKJS_PATH=~/Documents/ast-fusion/src/quickjs 
npx node-gyp  configure build 
