#pragma once

#include "KEnyin/Core/Log.hpp"
#include "KEnyin/Core/Base.hpp"

#ifdef KE_ASSERTS_ENABLED
    #ifdef HZ_PLATFORM_WINDOWS
        #define KECheck(x, ...) { if(!(x)) { KEError("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
        #define KECheck_Engine(x, ...) { if(!(x)) { KEError_Engine("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #else
        #define KECheck(x, ...) { if(!(x)) { KEError("Assertion Failed: {0}", __VA_ARGS__); } }
        #define KECheck_Engine(x, ...) { if(!(x)) { KEError_Engine("Assertion Failed: {0}", __VA_ARGS__); } }
    #endif
#else
    #define KECheck(cnd, ...)
    #define KECheck_Engine(cnd, ...)
#endif // KE_ASSERTS_ENABLED
