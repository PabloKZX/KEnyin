#include "pch.hpp"
#include "KEnyin/Rendering/Light.hpp"
#include "KEnyin/SceneManagement/Components/Components.hpp"

namespace KEnyin
{
    Light::Light(Components::Transform* transform)
    : _transform(transform)
    {
    }

    glm::vec3 Light::getPosition() const
    {
        return _transform->position;

    }
    const Color& Light::getColor() const
    {
        return _lightColor;
    }
}
