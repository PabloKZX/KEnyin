#include "pch.hpp"
#include "KEnyin/ECS/GameObject.hpp"
#include "KEnyin/SceneManagement/SceneManager.hpp"

namespace KEnyin
{
    GameObject::GameObject(const std::string& name)
        : _name(name)
        , _transform(new Transform())
        , _scene(ServiceLocator::get().getSceneManager().getActiveScene())
    {
    }

    GameObject::~GameObject()
    {
        delete _transform;

        for (const auto& component : _components)
        {
            delete component;
        }
    }

    void GameObject::onStart()
    {
        for (const auto& component : _components)
        {
            component->onStart();
        }
    }

    void GameObject::onUpdate(float timestamp)
    {
        for (const auto& component : _components)
        {
            component->onUpdate(timestamp);
        }
    }

    void GameObject::onRender()
    {
        for (const auto& component : _components)
        {
            component->onRender();
        }
    }
}
