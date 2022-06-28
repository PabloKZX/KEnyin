#pragma once

#include "KEnyin/Core/Timestep.hpp"
#include "KEnyin/Rendering/Mesh.hpp"
#include "KEnyin/Rendering/Material.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace KEnyin
{
    class ScriptableEntity;

    namespace Components
    {
        struct Tag
        {
            std::string tag;

            Tag() = default;
            Tag(const Tag&) = default;
            Tag(const std::string& tag)
                : tag(tag) { }
        };

        struct Transform
        {
            Transform() = default;
            Transform(const Transform&) = default;
            Transform(const glm::vec3& position)
                : position(position)
            {
            }

            glm::mat4 getTransformationMatrix() const
            {
                return glm::translate(glm::mat4(1.0f), position) * glm::toMat4(glm::quat(rotation)) * glm::scale(glm::mat4(1.0f), scale);
            }

            glm::vec3 position = { 0.0f, 0.0f, 0.0f };
            glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
            glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
        };

        struct MeshRenderer
        {
            std::shared_ptr<Mesh> mesh;
            std::shared_ptr<Material> material;

            MeshRenderer() = default;
            MeshRenderer(const MeshRenderer&) = default;
        };

        struct NativeScript
        {
            ScriptableEntity* instance = nullptr;

            // Function pointer
            // return type (name)(arguments)

            ScriptableEntity*(*instantiateScript)();
            void (*destroyScript)(Components::NativeScript*);

            template<typename T>
            void bind()
            {
                instantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
                destroyScript = [](Components::NativeScript* nativeScript)
                { 
                    delete nativeScript->instance;
                    nativeScript->instance = nullptr;
                };
            }
        };
    }
}