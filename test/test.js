const myQuickJSAddon = require('bindings')('my_quickjs_addon');


console.log(myQuickJSAddon.myFunction("_native_function", "20"));

const result = myQuickJSAddon.processArgs(42,'s36s',6);
console.log(result); 


// Define a JavaScript function to be called from C
function myCallback(x) {
    console.log('JavaScript function called from C!',x);
    return 'Hello from JavaScript!';
}

// Call the C function from the native addon
const cb_result = myQuickJSAddon.callBackFunction(myCallback);

console.log('Result from C:', JSON.stringify(cb_result));