#pragma once

#include "pch.hpp"
#include "KEnyin/ECS/UUID.hpp"

namespace KEnyin
{
    class EntityManager;
    class GameObject;
    class Component;

    constexpr int kMaxComponents = 32;
    constexpr int kMaxEntities = 100;

    using EntityID = uint64_t;
    using ComponentMask = std::bitset<kMaxComponents>;
    using ComponentTypeID = std::uint8_t;

    using GameObjectPtr = std::shared_ptr<GameObject>;
    using VGameObjects = std::vector<GameObjectPtr>;

    using ComponentPtr = std::shared_ptr<Component>;
}
