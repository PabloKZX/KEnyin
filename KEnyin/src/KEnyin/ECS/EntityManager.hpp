#pragma once

#include "KEnyin/ECS/EntityManager.fwd.hpp"

namespace KEnyin
{
    class Component;

    class EntityManager
    {
    public:
        using MComponents = std::unordered_map<EntityID, ComponentPtr>;
        using Registry = std::unordered_map<ComponentID, MComponents>;

        EntityManager() = default;

        template <class T>
        ComponentID GetID()
        {
            static int _componentId = _componentCounter++;
            return _componentId;
        }

        template <class T>
        void onComponentAdded(EntityID entityID, GameObject* entity, std::shared_ptr<T> component)
        {
            const ComponentID componentID = GetID<T>();

            ComponentPtr componentPtr = static_cast<ComponentPtr>(component);

            if (!componentPtr)
            {
                KEError_Engine("Trying to add an invalid component");
            }

            _registry[componentID].insert(std::make_pair(entityID, componentPtr));
        }

        inline void onGameObjectAdded(GameObject* gameObject)
        {
            _gameObjects.push_back(std::shared_ptr<GameObject>(gameObject));
        }

        inline const VGameObjects& getGameObjects() { return _gameObjects; }

        void logRegistry();

    private:
        Registry _registry;
        VGameObjects _gameObjects;
        int _componentCounter = 0;
    };
}
