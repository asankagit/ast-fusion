#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quickjs.h"
#include <typeinfo>


// Define a callback function for handling the result of the asynchronous operation
// Callback for asynchronous operation completion
void FetchDataCallback(napi_env env, napi_status status, void* data) {
    napi_deferred deferred = static_cast<napi_deferred>(data);

    if (status != napi_ok) {
        napi_reject_deferred(env, deferred, NULL); // Reject on error
        return;
    }

    // Get the result from the JavaScript function (assuming it's available)
    napi_value result;
    napi_get_value_from_deferred(env, deferred, &result);

    // Resolve the promise with the result
    napi_resolve_deferred(env, deferred, result);
}

// Function called from JavaScript
napi_value CallFetchData(napi_env env, napi_callback_info info) {
    napi_status status;

    // ... argument parsing and URL retrieval (same as before) ...

    // Create async work for the operation
    napi_async_work work;
    status = napi_create_async_work(env, NULL, NULL,NULL, FetchDataCallback, &work);
    if (status != napi_ok) {
        // Handle error appropriately (e.g., log, return error value)
        return NULL;
    }

    // Queue the work (assuming `fetchDataFunc` and `fetchDataArgs` are ready)
    status = napi_queue_async_work(env, work);
    if (status != napi_ok) {
        napi_delete_async_work(env, work);
        // Handle error appropriately
        return NULL;
    }

    // Create a promise to return to JavaScript
    napi_deferred deferred;
    status = napi_create_promise(env, &deferred, &work->promise);
    if (status != napi_ok) {
        napi_delete_async_work(env, work);
        // Handle error appropriately
        return NULL;
    }

    return work->promise;
}

// Initialize the addon
napi_value Init(napi_env env, napi_value exports) {
    napi_status status;

    // Define the exported function
    napi_property_descriptor desc = { "callFetchData", NULL, CallFetchData, NULL, NULL, NULL, napi_default, NULL };
    status = napi_define_properties(env, exports, 1, &desc);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Failed to define property");
        return NULL;
    }

    return exports;
}

NAPI_MODULE(addon, Init)
