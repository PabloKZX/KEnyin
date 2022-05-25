#pragma once

#include "KEnyin/Rendering/Color.hpp"

namespace KEnyin
{
    class Shader;
}

namespace KEnyin
{
    class Material
    {
    public:
        Material();
        Material(const Shader& shader);
        Material(const Shader& shader, const Color& color);
        ~Material();
    private:
        const Shader& _shader;
        Color _color;
    };
}

