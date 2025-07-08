const {makeAPICall} = require('./host-functions/apiCall');
const myQuickJSAddon = require('bindings')('ast-fusion');


console.log(myQuickJSAddon.myFunction(`function multiply(a, b) { return a * b; } \n`+
`const d = new Date();\n`+
// `console.log(1)`+
`let result = multiply(32, 4); `+
`js_native_addon(typeof '100x');`+
`result;`, "20"));

const result = myQuickJSAddon.processArgs(42,'s36s',6);
console.log(result); 


// Define a JavaScript function to be called from C
function myCallback(x) {
    console.log('JavaScript function called from C!',x);
    return 'Hello from JavaScript!';
}

function AddTwo(num) {
    console.log({ num})
    return num + 23.23 +"HI";
}

global.AddTwo = AddTwo;
// Call the C function from the native addon
const cb_result = myQuickJSAddon.callBackFunction(myCallback);

console.log('Result from C:', JSON.stringify(cb_result));


// Call the C/C++ function from Node.js
// console.log({ module }, module.children[0])
const apiResponse =  myQuickJSAddon.callNodeFunction("https://api.example.com/data");


// // console.log('gloabl>',global)
// module.require = makeAPICall
// console.log({ apiResponse })
// Handle the API response
// apiResponse.then(response => {
//     console.log('API Response:', response);
// }).catch(error => {
//     console.error('Error:', error);
// });


const path = require('path');

try {
    // Try to load your addon
    const astFusion = require('./build/Release/ast-fusion.node');
    
    console.log('✅ Addon loaded successfully!');
    console.log('Available methods:', Object.keys(astFusion));
    
    // Try calling a method if any exist
    if (Object.keys(astFusion).length > 0) {
        console.log('Addon has exposed methods - QuickJS likely linked correctly');
    } else {
        console.log('⚠️  No methods exposed - check your addon implementation');
    }
    
} catch (error) {
    console.error('❌ Failed to load addon:');
    console.error('Error:', error.message);
    
    if (error.message.includes('undefined symbol')) {
        console.log('\n🔍 This suggests QuickJS symbols are missing (not linked properly)');
        console.log('Check your binding.gyp configuration');
    }
}