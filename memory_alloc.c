#include <node_api.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

napi_value AllocateCharArray(napi_env env, napi_callback_info info) {
    size_t length = 1024;
    char* ptr = (char*)malloc(length);
    if (ptr == NULL) {
        napi_throw_error(env, NULL, "Memory allocation failed");
        return NULL;
    }

    char ptrStr[20];
    sprintf(ptrStr, "%p", ptr);

    napi_value result;
    napi_create_string_utf8(env, ptrStr, NAPI_AUTO_LENGTH, &result);
    printf("Allocated pointer in C: %p\n", ptr);
    return result;
}

napi_value SetCharArray(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    if (argc < 3) {
        napi_throw_error(env, NULL, "Expected 3 arguments: pointer, offset, value");
        return NULL;
    }

    size_t length;
    char ptrStr[20];
    napi_get_value_string_utf8(env, args[0], ptrStr, 20, &length);

    char* ptr = (char*)strtoull(ptrStr, NULL, 16);
    printf("Pointer in C (Set): %p\n", ptr);
    uint32_t offset;
    int value;

    napi_get_value_uint32(env, args[1], &offset);
    napi_get_value_int32(env, args[2], &value);

    if (ptr == NULL) {
        napi_throw_error(env, NULL, "Invalid pointer");
        return NULL;
    }

    ptr[offset] = (char)value;

    return NULL;
}

napi_value GetCharArray(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    if (argc < 2) {
        napi_throw_error(env, NULL, "Expected 2 arguments: pointer, offset");
        return NULL;
    }

    size_t length;
    char ptrStr[20];
    napi_get_value_string_utf8(env, args[0], ptrStr, 20, &length);

    char* ptr = (char*)strtoull(ptrStr, NULL, 16);
    printf("Pointer in C (Get): %p\n", ptr);
    uint32_t offset;

    napi_get_value_uint32(env, args[1], &offset);

    if (ptr == NULL) {
        napi_throw_error(env, NULL, "Invalid pointer");
        return NULL;
    }

    napi_value result;
    napi_create_int32(env, (int)ptr[offset], &result);

    return result;
}

napi_value Init(napi_env env, napi_value exports) {
    napi_value allocFn, setFn, getFn;
    napi_create_function(env, NULL, 0, AllocateCharArray, NULL, &allocFn);
    napi_create_function(env, NULL, 0, SetCharArray, NULL, &setFn);
    napi_create_function(env, NULL, 0, GetCharArray, NULL, &getFn);

    napi_set_named_property(env, exports, "allocateCharArray", allocFn);
    napi_set_named_property(env, exports, "setCharArray", setFn);
    napi_set_named_property(env, exports, "getCharArray", getFn);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)