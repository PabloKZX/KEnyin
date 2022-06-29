#include "pch.hpp"
#include "KEnyin/Rendering/Camera.hpp"
#include "KEnyin/SceneManagement/Components/Components.hpp"

namespace KEnyin
{
    Camera::Camera(const Components::Transform& transform)
        : _transform(transform)
    {
    }

    const glm::mat4& Camera::getViewProjectionMatrix() const
    {
        return getProjectionMatrix() * getViewMatrix();
    }

    const glm::mat4& Camera::getProjectionMatrix() const
    {
        return glm::perspective(_perspectiveFOV, 1280.0f / 720.0f, 0.1f, 100.0f);
    }

    const glm::mat4& Camera::getViewMatrix() const
    {
        return glm::lookAt(_transform.position, _transform.position + _transform.getForward(), _transform.getUp());
    }
}