#include "pch.hpp"
#ifdef KE_PLATFORM_MACOS

#include "KEnyin/Utils/PlatformUtils.hpp"

#include <GLFW/glfw3.h>

namespace KEnyin
{
    double Time::getTime()
    {
        return glfwGetTime() * 1000;
    }
}
#endif