#pragma once

#include <glm/glm.hpp>

namespace KEnyin::Math
{
    float min(float a, float b);
    float max(float a, float b);
    float clamp(float value, float min, float max);
    glm::vec3 clamp(glm::vec3 vector, float min, float max);
}
