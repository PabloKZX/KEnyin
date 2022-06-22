#pragma once

#include <entt.hpp>

namespace KEnyin
{
    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity createEntity(const std::string& name = "New Entity");

        void onUpdate(long long timestep);
    private:
        entt::registry _registry;

        friend class Entity;
    };
}
 