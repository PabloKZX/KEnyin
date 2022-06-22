#pragma once

#include "pch.hpp"
#include "KEnyin/ECS/UUID.hpp"

namespace KEnyin
{
    class EntityManager;
    class Entity;
    class Component;

    constexpr int kMaxComponents = 32;
    constexpr int kMaxEntities = 10000;

    using EntityID = uint64_t;
    using ComponentMask = std::bitset<kMaxComponents>;
    using ComponentTypeID = std::uint8_t;

    using EntityPtr = std::shared_ptr<Entity>;
    using VEntities = std::vector<EntityPtr>;

    using ComponentPtr = std::shared_ptr<Component>;
}
