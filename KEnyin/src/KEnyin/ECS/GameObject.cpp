#include "pch.hpp"
#include "KEnyin/ECS/GameObject.hpp"
#include "KEnyin/ECS/Transform.hpp"
#include "KEnyin/SceneManagement/SceneManager.hpp"

namespace KEnyin
{
    GameObject::GameObject()
    : ID(UUID())
    , _scene(ServiceLocator::get().getSceneManager().getActiveScene())
    {
        _scene->_entityManager->onGameObjectAdded(this);
    }
}
