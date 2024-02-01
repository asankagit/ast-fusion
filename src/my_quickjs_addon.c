#include <node_api.h>
#include <stdio.h>
#include <string.h>
#include "quickjs.h" 

static JSValue evaluateJavaScript(JSContext *ctx) {
    const char *code = "function multiply(a, b) { return a * b; } \n const d = new Date();\n let result = multiply(30, 4); result;";
    return JS_Eval(ctx, code, strlen(code), "<input>", JS_EVAL_FLAG_STRICT);
}

napi_value MyFunction(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value result;
    
    size_t argc = 2; // Assuming two arguments are passed
    napi_value argv[2];
    // napi_status status;

    // Get the arguments passed from JavaScript
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Failed to parse arguments");
        return NULL;
    }

    // Handle the arguments
    if (argc < 2) {
        napi_throw_error(env, NULL, "Insufficient number of arguments");
        return NULL;
    }

    // Assuming the arguments are strings, extract them using napi_get_value_string_utf8
    char arg1[100];
    char arg2[100];
    size_t length;

    status = napi_get_value_string_utf8(env, argv[0], arg1, sizeof(arg1), &length);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Invalid argument type");
        return NULL;
    }

    status = napi_get_value_string_utf8(env, argv[1], arg2, sizeof(arg2), &length);
    if (status != napi_ok) {
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

    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Failed to create string");
    }

    return result;
}

napi_value Init(napi_env env, napi_value exports) {
    napi_status status;
    napi_value fn;

    status = napi_create_function(env, NULL, 0, MyFunction, NULL, &fn);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Failed to create function");
    }

    status = napi_set_named_property(env, exports, "myFunction", fn);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Failed to set named property");
    }

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
