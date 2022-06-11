#pragma once

#include "KEnyin/ECS/EntityManager.hpp"

namespace KEnyin
{
    class GameObject;
}

namespace KEnyin
{
    class Scene
    {
    public:
        Scene();
        Scene(const std::string& name) : _name(name) {};
        ~Scene() = default;

        GameObjectSharedPtr newGameObject();

        template<typename T>
        void addComponent(GameObject gameobject)
        {
            //_gameObjects[gameobject.ID].mask.set(T::getStaticType());
        }

        template<typename T>
        void onComponentAdded(const GameObject& gameObject, const T& component);

        void loadSampleScene();
        EntityID getNewEntityID() const;
    private:
        std::string _name = "New Scene";
        EntityManager _entityManager;
    };
}
