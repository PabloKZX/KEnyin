#pragma once

#include "KEnyin/Components/Component.hpp"
#include "KEnyin/SceneManagement/Transform.hpp"

namespace KEnyin
{
    class GameObject
    {
    public:
        using VComponents = std::vector<std::unique_ptr<Component>>;

        GameObject(const std::string& name = "New GameObject");
        ~GameObject();

        template<typename T>
        T* addComponent()
        {
            T* component = new T(this, &_transform);
            _components.push_back(reinterpret_cast<T*>(component));
            component->start();
            return component;
        }

        template<typename T>
        T* getComponent()
        {
            auto found = std::find_if(_components.begin(), _components.end(), [](Component* ptr)
                {
                    return typeid(*ptr) == typeid(T);
                });

            return found == _components.end() ? nullptr : dynamic_cast<T*>(*found);
        }

        inline bool isEnabled() const { return _enabled; }
        inline void setEnabled(bool enabled) { _enabled = enabled; }

    private:
        std::string _name = "New GameObject";
        bool _enabled = true;
        VComponents _components;
        std::unique_ptr<Transform> _transform;
    };
}

