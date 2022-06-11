#include "pch.hpp"
#include "KEnyin/ECS/EntityManager.hpp"

namespace KEnyin
{
    void EntityManager::push(const GameObjectSharedPtr& gameObject)
    {
        _gameObjects.push_back(gameObject);
    }
}
