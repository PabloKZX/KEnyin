#pragma once

#include "KEnyin/ECS/ComponentArray.hpp"
#include "KEnyin/ECS/ECS.fwd.hpp"

namespace KEnyin
{
    class EntityManager
    {
    public:
        EntityManager() = default;

        template <class T>
        ComponentTypeID GetComponentTypeID()
        {
            static int _componentId = _componentCounter++;
            return _componentId;
        }

        template<typename T>
        T& AddComponent(EntityID entityID)
        {
            T component = T();
            const ComponentTypeID componentID = GetComponentTypeID<T>();

            if (!_componentArrays.contains(componentID))
            {
                _componentArrays[componentID] = std::make_shared<ComponentArray<T>>();
            }

            std::shared_ptr<ComponentArray<T>> componentsArray = GetComponentsOfType<T>();
            componentsArray->insertData(entityID, component);
            return componentsArray->getData(entityID);
        }

        template<typename T>
        T& GetComponent(EntityID entityID)
        {
            return getComponentsOfType<T>()->getData(entityID);
        }

        std::vector<std::string> GetComponentsStrings(EntityID entityID)
        {
            std::vector<std::string> componentsNames;
            for (const auto& [componentType, componentArray] : _componentArrays)
            {
                if (componentArray->entityHasAnyComponent(entityID))
                {
                    componentsNames.push_back(componentArray->componentName);
                }
            }

            return componentsNames;
        }

        template<typename T>
        void RemoveComponent(EntityID entityID)
        {
            getComponentsOfType<T>()->removeData(entityID);
        }

        template <typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentsOfType()
        {
            return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[GetComponentTypeID<T>()]);
        }

        void EntityDestroyed(EntityID entityID)
        {
            for (const auto& pair : _componentArrays)
            {
                auto const& componentArray = pair.second;
                componentArray->entityDestroyed(entityID);
            }
        }

        void onEntityAdded(Entity* entity);
        inline const VEntities& getEntities() const { return _entities; }
        void logRegistry();

    private:
        std::unordered_map<ComponentTypeID, std::shared_ptr<IComponentArray>> _componentArrays{};
        VEntities _entities;
        int _componentCounter = 0;
    };
}
