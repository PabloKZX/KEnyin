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

    glm::vec3 Light::getDirection() const
    {
        return _transform->getForward();
    }

    Light::LightData& Light::getLightData()
    {
        return _lightData;
    }
}
