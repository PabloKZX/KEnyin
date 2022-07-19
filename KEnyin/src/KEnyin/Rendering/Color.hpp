#pragma once

#include <glm/glm.hpp>

namespace KEnyin
{
    struct Color
    {
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 1.0f;

        Color() = default;
        Color(float c) : r(c), g(c), b(c), a(1.0f) {};
        Color(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) {};
        Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}; ;
        Color(const glm::vec4& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}; ;
        Color(const glm::vec3& color) : r(color.r), g(color.g), b(color.b), a(1.0f) {}; ;
        ~Color() = default;

        operator glm::vec3() { return { r, g, b }; };
        operator glm::vec4() { return { r, g, b, a }; };
    };
}
