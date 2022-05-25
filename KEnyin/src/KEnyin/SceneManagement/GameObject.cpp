#include "pch.hpp"
#include "KEnyin/SceneManagement/GameObject.hpp"

namespace KEnyin
{
    GameObject::GameObject(const std::string& name)
        : _name(name)
        , _transform(new Transform())
    {
    }

    GameObject::GameObject(const GameObject& other)
    {
        KEWarn_Engine("{0} copied", _name);
    }

    GameObject::GameObject(GameObject&& other) noexcept
    {
        KEWarn_Engine("{0} moved", _name);

        _name = other._name;
        _enabled = other._enabled;
        _transform = other._transform;

        other._transform = nullptr;

        for (size_t i = 0; i < other._components.size(); i++)
        {
            _components.push_back(other._components[i]);
            other._components[i] = nullptr;
        }
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
