#include "pch.hpp"
#include "KEnyin/Rendering/Camera.hpp"
#include "KEnyin/SceneManagement/Components/Components.hpp"

namespace KEnyin
{
    Camera::Camera(const Components::Transform& transform)
        : _transform(transform)
    {
    }

    const glm::mat4 Camera::getViewProjectionMatrix() const
    {
        return getProjectionMatrix() * getViewMatrix();
    }

    const glm::mat4 Camera::getProjectionMatrix() const
    {
        return glm::perspective(_perspectiveFOV, _width / (float)_height, 0.1f, 100.0f);
    }

    const glm::mat4 Camera::getViewMatrix() const
    {
        return glm::lookAt(_transform.position, _transform.position + _transform.getForward(), _transform.getUp());
    }

    void Camera::resize(unsigned int width, unsigned int height)
    {
        _width = width;
        _height = height;
    }
}