#pragma once

#include "KEnyin/Core/Timestep.hpp"
#include <entt.hpp>

namespace KEnyin
{
    class Entity;

    class Scene
    {
    public:
        Scene() = default;
        ~Scene() = default;

        Entity createEntity(const std::string& name = "New Entity");

        void renderScene();
        void onUpdate(Timestep timestep);
        void loadAsSampleScene();
    private:
        template<typename T>
        void onComponentAdded(Entity entity, T& component);

        entt::registry _registry;
        friend class Entity;
    };
}
 