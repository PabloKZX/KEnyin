#pragma once

#include "KEnyin/Core/Timestep.hpp"
#include "KEnyin/SceneManagement/Components/Components.hpp"
#include "KEnyin/Rendering/Camera.hpp"
#include "entt.hpp"

namespace KEnyin
{
    class Entity;

    namespace KEditor::Panels
    {
        class Hierarchy;
    }

    class Scene
    {
    public:
        Scene() = default;
        ~Scene() = default;

        Entity createEntity(const std::string& name = "New Entity");
        void destroyEntity(Entity entity);

        void renderScene();
        void onUpdate(Timestep timestep);
    private:
        template<typename T>
        void onComponentAdded(Entity entity, T& component);

        entt::registry _registry;
        std::shared_ptr<Components::CameraComponent> _mainCamera;

        friend class Entity;
        friend class KEditor::Panels::Hierarchy;
    };
}
 
