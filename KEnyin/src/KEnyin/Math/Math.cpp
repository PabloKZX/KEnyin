#include "pch.hpp"
#include "KEnyin/Math/Math.hpp"

namespace KEnyin::Math
{
    float min(float a, float b)
    {
        return (a <= b) ? a : b;
    }

    float max(float a, float b)
    {
        return (a >= b) ? a : b;
    }

    float clamp(float value, float minVal, float maxVal)
    {
        return min(max(value, minVal), maxVal);
    }

    glm::vec3 clamp(glm::vec3 vector, float min, float max)
    {
        glm::vec3 vec;
        vec.x = clamp(vector.x, min, max);
        vec.y = clamp(vector.y, min, max);
        vec.z = clamp(vector.z, min, max);
        return vec;
    }
}
