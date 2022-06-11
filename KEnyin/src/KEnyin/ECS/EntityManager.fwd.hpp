#pragma once

#include "pch.hpp"

namespace KEnyin
{
    class EntityManager;
    class GameObject;

    constexpr int kMaxComponents = 32;
    constexpr int kMaxEntities = 100;

    using EntityID = std::uint32_t;
    using ComponentID = std::uint8_t;
    using ComponentMask = std::bitset<kMaxComponents>;

    using GameObjectSharedPtr = std::shared_ptr<GameObject>;
    using VGameObjects = std::vector<GameObjectSharedPtr>;
}
