#include "pch.hpp"
#include "KEnyin/SceneManagement/Scene.hpp"
#include "KEnyin/ECS/GameObject.hpp"

namespace KEnyin
{
    template<typename T>
    void Scene::onComponentAdded(const GameObject& gameObject, const T& component)
    {
        _registry.addComponent(gameObject, component);
    }
}
