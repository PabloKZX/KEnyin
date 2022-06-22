#include "pch.hpp"
#include "KEnyin/SceneManagement/Entity.hpp"

namespace KEnyin
{
    Entity::Entity(entt::entity handle, Scene* scene)
    : _entityHandle(handle)
    , _scene(scene)
    {

    }
}