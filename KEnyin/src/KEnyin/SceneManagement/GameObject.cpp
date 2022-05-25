#include "pch.hpp"
#include "KEnyin/SceneManagement/GameObject.hpp"


namespace KEnyin
{
    GameObject::GameObject(const std::string& name)
    : _name(name)
    , _transform(std::make_unique<Transform>())
    {
    }

    GameObject::~GameObject()
    {
    }
}
