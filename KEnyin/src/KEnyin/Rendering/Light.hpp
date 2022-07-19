#pragma once

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

    private:
        Components::Transform* _transform;
    };
}
