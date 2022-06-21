#pragma once

#include "KEnyin/ECS/EntityManager.hpp"

namespace KEnyin
{
    class GameObject;

    class Scene
    {
    public:
        Scene();
        Scene(const std::string& name) : _name(name) {};
        ~Scene() = default;

        void loadSampleScene();
    private:
        std::string _name = "New Scene";
        std::unique_ptr<EntityManager> _entityManager;

        friend class GameObject;
    };
}
