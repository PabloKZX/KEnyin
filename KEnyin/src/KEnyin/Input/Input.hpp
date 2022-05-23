#pragma once

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
