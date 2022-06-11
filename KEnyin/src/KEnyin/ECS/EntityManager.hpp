#pragma once

#include "KEnyin/ECS/EntityManager.fwd.hpp"
#include "KEnyin/ECS/GameObject.hpp"

namespace KEnyin
{
    class EntityManager
    {
    public:
        EntityManager() = default;

        template <class T>
        ComponentID GetId()
        {
            static int _componentId = _componentCounter++;
            return _componentId;
        }

        template <class T>
        void AddComponent(const GameObjectSharedPtr& entity)
        {
            int componentId = GetId<T>();
            _gameObjects[entity->getId()]->getMask().set(componentId);
        }

        inline const VGameObjects& getGameObjects() const { return _gameObjects; }
        void push(const GameObjectSharedPtr& gameObject);
    private:
        int _componentCounter = 0;
        VGameObjects _gameObjects;
    };
}
