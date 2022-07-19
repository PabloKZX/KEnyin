#pragma once

#include "KEnyin/Rendering/Color.hpp"
#include <glm/glm.hpp>

namespace KEnyin
{
    namespace Components
    {
        struct Transform;
    }

    class Light
    {
    public:
        enum LightType {Directional = 0, Point = 1, Spot = 2};

        struct LightData
        {
            LightType type = LightType::Point;

            Color lightColor = Color(1.0f);
            float range = 32;
            float linearAttenuation = 0.14f;
            float quadraticAttenuation = 0.07f;
            float innerAngle = glm::radians(15.0f);
            float outerAngle = glm::radians(25.0f);
        };

        Light() = default;
        Light(const Light&) = default;
        Light(Components::Transform* transform);

        glm::vec3 getPosition() const;
        glm::vec3 getDirection() const;
        LightData& getLightData();

    private:
        Components::Transform* _transform;
        LightData _lightData;
    };
}
