cmd_Release/obj.target/my_quickjs_addon.node := g++ -o Release/obj.target/my_quickjs_addon.node -shared -pthread -rdynamic -m64  -Wl,-soname=my_quickjs_addon.node -Wl,--start-group Release/obj.target/my_quickjs_addon/src/my_quickjs_addon.o -Wl,--end-group -L/home/asanka/Documents/my-quickjs-addon/src/quickjs -lquickjs -lm