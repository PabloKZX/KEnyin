#pragma once

namespace KEnyin
{
    class Color
    {
    public:
        Color() {};
        Color(float r, float g, float b);
        Color(float r, float g, float b, float a);
        ~Color() {};

    private:
        float _r = 0.0f;
        float _g = 0.0f;
        float _b = 0.0f;
        float _a = 1.0f;
    };
}