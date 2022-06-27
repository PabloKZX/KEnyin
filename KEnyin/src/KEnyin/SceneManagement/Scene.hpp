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

        void renderScene();
        void onUpdate(long long timestep);
        void loadAsSampleScene();
    private:

        entt::registry _registry;

        friend class Entity;
    };
}
 