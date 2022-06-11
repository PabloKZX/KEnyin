#include "pch.hpp"
#include "KEnyin/ECS/GameObject.hpp"
#include "KEnyin/ECS/Transform.hpp"
#include "KEnyin/SceneManagement/SceneManager.hpp"

namespace KEnyin
{

    GameObject::GameObject()
        : _scene(ServiceLocator::get().getSceneManager().getActiveScene())
    {
        _id = _scene.getNewEntityID();
    }

}
