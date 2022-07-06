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

        Camera() = default;
        Camera(const Components::Transform& transform);
        Camera(const Camera&) = default;

        const glm::mat4 getViewProjectionMatrix() const;
        const glm::mat4 getProjectionMatrix() const;
        const glm::mat4 getViewMatrix() const;

        void resize(unsigned int width, unsigned int height);

    private:
        const Components::Transform& _transform;

        float _perspectiveFOV = 45.0f;
        float _perspectiveNear;
        float _aspectRatio;

        unsigned int _width = 1280.0f;
        unsigned int _height = 720.0;
    };
}
