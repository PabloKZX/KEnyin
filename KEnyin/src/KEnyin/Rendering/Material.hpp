#pragma once

#include "pch.hpp"
#include "KEnyin/Rendering/Color.hpp"
#include "KEnyin/Rendering/Shader.hpp"
#include "KEnyin/Rendering/Texture2D.hpp"

namespace KEnyin
{
    class Shader;

    struct Material
    {
        std::shared_ptr<Shader> shader;
        std::vector<std::shared_ptr<Texture2D>> textures;
        Color color;
        float shininess = 32.0f;

        Material() = default;
        Material(const Material&) = default;
        ~Material() = default;
    };
}

