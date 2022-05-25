#include "pch.hpp"
#include "KEnyin/Rendering/Color.hpp"

namespace KEnyin
{
    Color::Color(float r, float g, float b)
    : _r(r)
    , _g(g)
    , _b(b)
    , _a(1.0f)
    {

    }

    Color::Color(float r, float g, float b, float a)
    : _r(r)
    , _g(g)
    , _b(b)
    , _a(a)
    {

    }
}