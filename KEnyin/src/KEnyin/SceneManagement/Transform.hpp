#pragma once

#include <glm/glm.hpp>

namespace KEnyin
{
    class Transform
    {
    public:
        using VTransform = std::vector<Transform*>;

    private:
        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec3 _scale;

        Transform* _parent;
        VTransform _children;
    };
}

