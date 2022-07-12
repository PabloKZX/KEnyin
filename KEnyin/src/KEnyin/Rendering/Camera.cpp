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
        if(_projectionType == ProjectionType::Perspective)
        {
            return glm::perspective(_perspectiveFOV, _aspectRatio, _nearPlane, _farPlane);
        }
        else
        {
            float left = -_orthographicSize * _aspectRatio * 0.5f;
            float right = _orthographicSize * _aspectRatio * 0.5f;
            float top = -_orthographicSize * 0.5f;
            float bottom = _orthographicSize * 0.5f;

            return glm::ortho(left, right, bottom, top, _nearPlane, _farPlane);
        }
    }

    const glm::mat4 Camera::getViewMatrix() const
    {
        return glm::lookAt(_transform.position, _transform.position + _transform.getForward(), _transform.getUp());
    }

    void Camera::resize(unsigned int width, unsigned int height)
    {
        KECheck_Engine(width > 0 && height > 0, "");
        _aspectRatio = (float)width / (float) height;
    }

    void Camera::setProjectionType(ProjectionType type)
    {
        _projectionType = type;
    }

    Camera::ProjectionType Camera::getProjectionType() const
    {
        return _projectionType;
    }

    float Camera::getPerspectiveFOV() const
    {
        return _perspectiveFOV;
    }

    void Camera::setPerspectiveFOV(float fov)
    {
        _perspectiveFOV = fov;
    }

    float Camera::getNearPlane() const
    {
        return _nearPlane;
    }

    void Camera::setNearPlane(float near)
    {
        _nearPlane = near;
    }

    float Camera::getFarPlane() const
    {
        return _farPlane;
    }

    void Camera::setFarPlane(float far)
    {
        _farPlane = far;
    }

    float Camera::getOrthographicSize() const
    {
        return _orthographicSize;
    }

    void Camera::setOrthographicSize(float size)
    {
        _orthographicSize = size;
    }
}