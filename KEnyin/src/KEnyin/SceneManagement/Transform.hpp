#pragma once

#include "KEnyin/Components/Component.hpp"
#include <glm/glm.hpp>

namespace KEnyin
{
    class Transform : public Component
    {
    public:
        Transform() = default;
        Transform(const Transform&) = default;
        ~Transform() = default;

        glm::vec3 position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };;
        glm::vec3 scale = { 1.0f, 1.0f, 1.0f };;
    };
}

