#pragma once

#include "KEnyin/ECS/Component.hpp"
#include "KEnyin/ECS/Transform.hpp"

namespace KEnyin
{
    class GameObject
    {
        friend class Scene;

    public:
        using VComponents = std::vector<Component*>;

        GameObject(const std::string& name = "New GameObject");
        ~GameObject();

        template<typename T>
        T& addComponent()
        {
            T* component = new T();
            _components.push_back(reinterpret_cast<T*>(component));
            component->onStart();
            return component;
        }

        template<typename T>
        T& getComponent()
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
        void onStart();
        void onUpdate(float timestamp);
        void onRender();

        std::string _name = "New GameObject";
        bool _enabled = true;
        VComponents _components;
        Transform* _transform;
        Scene& _scene;
    };
}

