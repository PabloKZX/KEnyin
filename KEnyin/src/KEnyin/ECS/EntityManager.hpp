#pragma once

#include "KEnyin/ECS/EntityManager.fwd.hpp"
#include "KEnyin/ECS/ECSUtils.hpp"

namespace KEnyin
{
    class EntityManager
    {
    public:
        using MComponents = std::unordered_map<EntityID, ComponentPtr>;
        using Registry = std::unordered_map<ComponentTypeID, MComponents>;

        EntityManager() = default;

        template <typename T>
        void onComponentAdded(EntityID entityID, GameObject* entity, std::shared_ptr<T> component)
        {
            const ComponentTypeID componentID = ECSUtils::GetComponentTypeID<T>();

            ComponentPtr componentPtr = static_cast<ComponentPtr>(component);

            if (!componentPtr)
            {
                KEError_Engine("Trying to add an invalid component");
            }

            _registry[componentID].insert(std::make_pair(entityID, componentPtr));
        }

        void onGameObjectAdded(GameObject* gameObject);

        inline const VGameObjects& getGameObjects() { return _gameObjects; }

        void logRegistry();

    private:
        Registry _registry;
        VGameObjects _gameObjects;
    };
}
