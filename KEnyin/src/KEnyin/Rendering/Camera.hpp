#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace KEnyin
{
    namespace Components
    {
        struct Transform;
    }

    class Camera
    {
    public:
        using TransformSPtr = std::shared_ptr<Components::Transform>;

        enum ProjectionType {Perspective = 0, Orthographic = 1};

        Camera() = default;
        Camera(const Components::Transform& transform);
        Camera(const Camera&) = default;

        const glm::mat4 getViewProjectionMatrix() const;
        const glm::mat4 getProjectionMatrix() const;
        const glm::mat4 getViewMatrix() const;

        void resize(unsigned int width, unsigned int height);

        void setProjectionType(ProjectionType type);
        ProjectionType getProjectionType() const;
        ///Returns field of view of camera (in radians)
        float getPerspectiveFOV() const;
        ///Sets field of view of camera (in radians)
        void setPerspectiveFOV(float fov);
        float getNearPlane() const;
        void setNearPlane(float near);
        float getFarPlane() const;
        void setFarPlane(float far);
        float getOrthographicSize() const;
        void setOrthographicSize(float size);

    private:
        const Components::Transform& _transform;

        ProjectionType _projectionType = ProjectionType::Perspective;

        float _perspectiveFOV = glm::radians(60.0f); // In radians
        float _nearPlane = 0.3f;
        float _farPlane = 1000.0f;
        float _orthographicSize = 5.0f;
        float _aspectRatio = 0.0f;
    };
}
