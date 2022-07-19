#pragma once

#include "KEnyin/Rendering/Color.hpp"
#include <glm/glm.hpp>

namespace KEnyin
{
    namespace Components
    {
        struct Transform;
    }

    class Light
    {
    public:
        Light() = default;
        Light(const Light&) = default;
        Light(Components::Transform* transform);

        glm::vec3 getPosition() const;
        const Color& getColor() const;

    private:
        Components::Transform* _transform;
        Color _lightColor = Color(1.0f);

    };
}
