#pragma once

#include "KEnyin/Core/Log.hpp"
#include "KEnyin/Core/Base.hpp"

#ifdef KE_ASSERTS_ENABLED
    #define KECheck(cnd, ...) {if(!(cnd)) {KEError("Assert triggered {0}: ", __VA_ARGS__); __debugbreak();}}
    #define KECheck_Engine(cnd, ...) {if(!(cnd)) {KEError_Engine("Assert triggered: {0} ", __VA_ARGS__); __debugbreak();}}
#else
    #define KECheck(cnd, ...)
    #define KECheck_Engine(cnd, ...)
#endif // KE_ASSERTS_ENABLED