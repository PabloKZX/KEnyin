#include "pch.hpp"
#include "KEnyin/ECS/Entity.hpp"
#include "KEnyin/ECS/Transform.hpp"
#include "KEnyin/SceneManagement/SceneManager.hpp"

namespace KEnyin
{
    Entity::Entity()
    : ID(UUID())
    , _scene(ServiceLocator::get().getSceneManager().getActiveScene())
    {
        _scene->_entityManager->onEntityAdded(this);
    }
}
