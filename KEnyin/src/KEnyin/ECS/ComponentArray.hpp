#pragma once
#include "pch.hpp"
#include "KEnyin/ECS/ECS.fwd.hpp"

namespace KEnyin
{
    class IComponentArray
    {
    public: 
        virtual ~IComponentArray() = default;
        virtual void entityDestroyed(EntityID entityID) = 0;
        virtual bool entityHasAnyComponent(EntityID entityID) = 0;

        std::string componentName;

        IComponentArray() = default;
        IComponentArray(std::string name) : componentName(name) {};
    };

    template <typename T>
    class ComponentArray : public IComponentArray
    {
    public:
        ComponentArray() : IComponentArray(typeid(T).name()) {};

        void insertData(EntityID entityID, T component)
        {
            KECheck_Engine(!_entityToIndexMap.contains(entityID),
                "Component added to same entity more than once");

            size_t newIndex = _size;

            _entityToIndexMap[entityID] = newIndex;
            _indexToEntityMap[newIndex] = entityID;
            _componentArray[newIndex] = component;

            ++_size;
        }

        void removeData(EntityID entityID)
        {
            KECheck_Engine(_entityToIndexMap.contains(entityID),
                "Removing non existent component");

            // Copy element at the end into the deleted element's place
            const size_t indexOfRemovedEntity = _indexToEntityMap[entityID];
            const size_t indexOfLastElement = _size - 1;
            _componentArray[indexOfRemovedEntity] = _componentArray[indexOfLastElement];

            // Update map to point to moved spor
            EntityID entityOfLastElement = _indexToEntityMap[indexOfLastElement];
            _entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            _indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            _entityToIndexMap.erase(entityID);
            _indexToEntityMap.erase(indexOfLastElement);

            --_size;
        }

        T& getData(EntityID entityID)
        {
            KECheck_Engine(_entityToIndexMap.contains(entityID),
                "Retrieving non existent component");

            return _componentArray[_entityToIndexMap[entityID]];
        }

        void entityDestroyed(EntityID entityID) override
        {
            if (_entityToIndexMap.contains(entityID))
            {
                removeData(entityID);
            }
        }

        bool entityHasAnyComponent(EntityID entityID) override
        {
            return _entityToIndexMap.contains(entityID);
        }

    private:
        // Packed array of components T. Each entity is reserved
        // a unique spot
        std::array<T, kMaxEntities> _componentArray;

        std::unordered_map<EntityID, size_t> _entityToIndexMap;

        std::unordered_map<size_t, EntityID> _indexToEntityMap;

        size_t _size = 0;
    };
}


