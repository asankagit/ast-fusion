#include <node_api.h>
#include <stdio.h>
#include <string.h>
#include "quickjs.h"
#include <stdlib.h>

static JSValue evaluateJavaScript(JSContext *ctx)
{
    const char *code = "function multiply(a, b) { return a * b; } \n const d = new Date();\n let result = multiply(32, 4); result;";
    return JS_Eval(ctx, code, strlen(code), "<input>", JS_EVAL_FLAG_STRICT);
}

napi_value MyFunction(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value result;

    size_t argc = 2; // Assuming two arguments are passed
    napi_value argv[2];

    // Get the arguments passed from JavaScript
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Failed to parse arguments");
        return NULL;
    }

    // Handle the arguments
    if (argc < 2)
    {
        napi_throw_error(env, NULL, "Insufficient number of arguments");
        return NULL;
    }

    // Assuming the arguments are strings, extract them using napi_get_value_string_utf8
    char arg1[100];
    char arg2[100];
    size_t length;

    status = napi_get_value_string_utf8(env, argv[0], arg1, sizeof(arg1), &length);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Invalid argument type");
        return NULL;
    }

    status = napi_get_value_string_utf8(env, argv[1], arg2, sizeof(arg2), &length);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Invalid argument type");
        return NULL;
    }

    // Do something with the arguments, e.g., print them
    printf("Argument 1: %s\n", arg1);
    printf("Argument 2: %s\n", arg2);

    // Create QuickJS runtime and context
    JSRuntime *rt = JS_NewRuntime();
    JSContext *ctx = JS_NewContext(rt);

    // Evaluate JavaScript code
    JSValue jsResult = evaluateJavaScript(ctx);

    // Handle result and convert to N-API value
    // For simplicity, just create a string with the result
    const char *jsResultStr = JS_ToCString(ctx, jsResult);
    status = napi_create_string_utf8(env, jsResultStr, NAPI_AUTO_LENGTH, &result);
    JS_FreeCString(ctx, jsResultStr);
    JS_FreeValue(ctx, jsResult);

    // Free QuickJS context and runtime
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);

    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Failed to create string");
    }

    return result;
}

napi_value ProcessArgs(napi_env env, napi_callback_info info)
{
    size_t argc = 3; // Expecting 3 arguments
    napi_value argv[3];
    napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

    // Check the number of arguments received
    if (argc != 3)
    {
        // Handle error or throw an exception
        napi_throw_error(env, NULL, "Invalid number of arguments");
        return NULL;
    }

    // Perform some operation with the arguments
    // For simplicity, just return the number of arguments received
    // Inside the ProcessArgs function
    // char message[100]; // Make sure it's large enough to hold your message
    // snprintf(message, sizeof(message), "Received %zu arguments", argc);

    // napi_value result;
    // napi_create_string_utf8(env, message, NAPI_AUTO_LENGTH, &result);
    // Determine the length of the message
    size_t message_length = snprintf(NULL, 0, "Received %zu arguments", argc);

    // Allocate memory for the message dynamically
    char *message = (char *)malloc(message_length + 1); // Add 1 for the null terminator

    // Check if memory allocation was successful
    if (message == NULL)
    {
        // Handle memory allocation failure
        return NULL; // Or throw an error
    }

    // Populate the message
    snprintf(message, message_length + 1, "Received %zu arguments", argc);

    // Create the N-API string from the message
    napi_value result;
    napi_create_string_utf8(env, message, NAPI_AUTO_LENGTH, &result);

    // Free dynamically allocated memory
    free(message);

    return result;
}

napi_value CreateJsObject(napi_env env) {
    napi_value jsObject;
    napi_create_object(env, &jsObject); // Create a new empty JavaScript object

    // Set the properties of the JavaScript object
    napi_value nameValue, paramsValue;

    // Create string values for the properties
    napi_create_string_utf8(env, "some_name", NAPI_AUTO_LENGTH, &nameValue);
    napi_create_string_utf8(env, "d", NAPI_AUTO_LENGTH, &paramsValue);

    // Set the properties on the JavaScript object
    napi_set_named_property(env, jsObject, "name", nameValue);
    napi_set_named_property(env, jsObject, "params", paramsValue);

    return jsObject;
}


// napi_value CallJavaScriptCallback(napi_env env, napi_value jsCallback, napi_value* args, size_t argCount, napi_value* result) {
//     // Call the JavaScript callback function with the specified arguments
//     napi_call_function(env, NULL, jsCallback, argCount, args, result);
// }
/*
napi_value CallJavaScriptCallback(napi_env env, napi_value callback, const char* cArgs) {
    napi_value global;
    napi_get_global(env, &global);

    napi_value jsCallback;
    napi_get_reference_value(env, callback, &jsCallback);

    napi_value jsArgs;
    napi_create_string_utf8(env, cArgs, NAPI_AUTO_LENGTH, &jsArgs);

    napi_value result;
    napi_call_function(env, global, jsCallback, 1, &jsArgs, &result);

    // Check if the call was successful
    if (result == NULL) {
        // Handle error
        return NULL;
    }

    // Convert the result to a string
    char buffer[512]; // Adjust the buffer size as needed
    size_t length;
    napi_get_value_string_utf8(env, result, buffer, sizeof(buffer), &length);

    // Print the result
    printf("Result from JavaScript: %s\n", buffer);

    return result;
}
napi_value CallBackFunction(napi_env env, napi_callback_info info)
{
    napi_value result = CreateJsObject(env);
    return result;
}
*/

// Define someData variable outside the callBackFunction
// napi_value someData;

napi_value CallBackFunction(napi_env env, napi_callback_info info) {
    // // Get the callback info
    // size_t argc = 1; // Assuming one argument (the callback)
    // napi_value argv[1];
    // napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

    // // Ensure the correct number of arguments
    // if (argc < 1) {
    //     napi_throw_error(env, NULL, "Expected one argument");
    //     return NULL;
    // }

    // // Extract the callback function (jsCallback)
    // napi_value jsCallback = argv[0];

    // // Call the JavaScript callback function with an argument
    // napi_value arg;
    // napi_create_int32(env, 42, &arg); // Example argument, you can replace it with your desired value

    // napi_value result_;
    // napi_call_function(env, NULL, jsCallback, 1, &arg, &result_);

    // // print callback funtion
    // size_t bufferLength = 1024; // Adjust buffer size as needed
    // char buffer[bufferLength];
    // size_t written;

    // napi_get_value_string_utf8(env, jsCallback, buffer, bufferLength, &written);

    // printf("JavaScript callback function: %s\n", buffer);

    // //end callback function print

    // // Call the JavaScript callback using CallJavaScriptCallback
    // napi_value result = CallJavaScriptCallback(env, jsCallback, &arg);

    
    // // Handle the result if needed
    // if (result == NULL) {
    //     napi_throw_error(env, NULL, "Failed to execute JavaScript callback");
    //     return NULL;
    // }

    // // Return the result to JavaScript
    // return result;
    
     size_t argc = 1; // Expecting one argument
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

    // Log the argument received from JavaScript
    printf("JavaScript function called from C with argument: ");
    napi_value arg = argv[0];
    napi_value argToString;
    napi_coerce_to_string(env, arg, &argToString);
    size_t bufferSize = 1024; // Adjust buffer size as needed
    char buffer[bufferSize];
    napi_get_value_string_utf8(env, argToString, buffer, bufferSize, NULL);
    printf("%s\n", buffer);

    // Return a value back to JavaScript
    napi_value returnValue;
    napi_create_string_utf8(env, "Hello from C!", NAPI_AUTO_LENGTH, &returnValue);
    return returnValue;
}


static napiValueToString(napi_value makeAPICallFunction, napi_env env) {
    //////////////////////////////////////////
        napi_status status;
        napi_value stringResult;
        status = napi_coerce_to_string(env, makeAPICallFunction, &stringResult);
        if (status != napi_ok) {
            // Handle error
        }

        size_t strLength;
        status = napi_get_value_string_utf8(env, stringResult, NULL, 0, &strLength);
        if (status != napi_ok) {
            // Handle error
        }

        // Allocate memory for the string
        char* str = NULL;
        str = (char*)malloc((strLength + 1) * sizeof(char));
        if (str == NULL) {
            // Handle memory allocation failure
        }

        status = napi_get_value_string_utf8(env, stringResult, str, strLength + 1, NULL);
        if (status != napi_ok) {
            // Handle error
        }

        // Print the string
        printf("Value of makeAPICallFunction: %s\n", str);

        // Free the allocated memory
        free(str);
        //////////////////////////////////////////
}


napi_value CallNodeFunction(napi_env env, napi_callback_info info) {
    // Get the function named "AddTwo" on the global object
    napi_value global, add_two, arg;
    napi_status status = napi_get_global(env, &global);
    if (status != napi_ok) return;

    status = napi_get_named_property(env, global, "AddTwo", &add_two);
    if (status != napi_ok) return;

    // const arg = 1337
    status = napi_create_int32(env, 1337, &arg);
    if (status != napi_ok) return;

    napi_value* argv = &arg;
    size_t argc = 1;

    // AddTwo(arg);
    napi_value return_val;
    status = napi_call_function(env, global, add_two, argc, argv, &return_val);
    if (status != napi_ok) return;

    // Convert the result back to a native type
    int32_t result;
    status = napi_get_value_int32(env, return_val, &result);
    napiValueToString(return_val, env);

    if (status != napi_ok) return;
}


napi_value Init(napi_env env, napi_value exports)
{
    napi_status status;
    napi_value fn, processArgs, callBackfn, callNodefn;

    status = napi_create_function(env, NULL, 0, MyFunction, NULL, &fn);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Failed to create function");
    }

    status = napi_set_named_property(env, exports, "myFunction", fn);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Failed to set named property");
    }

    // Create and export ProcessArgs
    status = napi_create_function(env, NULL, 0, ProcessArgs, NULL, &processArgs);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Failed to export ProcessArgs function");
        return NULL;
    }

    status = napi_set_named_property(env, exports, "processArgs", processArgs);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Failed to set named property");
        return NULL;
    }

    status = napi_create_function(env, NULL, 0, CallBackFunction, NULL, &callBackfn);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Failed to create function");
    }

    status = napi_set_named_property(env, exports, "callBackFunction", callBackfn);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Failed to set named property");
    }


    status = napi_create_function(env, NULL, 0, CallNodeFunction, NULL, &callNodefn);
    if (status != napi_ok) return NULL;

    status = napi_set_named_property(env, exports, "callNodeFunction", callNodefn);
    if (status != napi_ok) return NULL;
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
