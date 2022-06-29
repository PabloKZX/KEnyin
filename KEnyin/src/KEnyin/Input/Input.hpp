#pragma once

#include "KEnyin/Input/KeyCodes.hpp"
#include "KEnyin/Input/MouseCodes.hpp"

namespace KEnyin
{
    class Input
    {
    public:
        static bool getKeyDown(int keyCode);
        static bool getMouseButtonDown(int keyCode);
        static std::pair<float, float> getMousePosition();
    };
}
