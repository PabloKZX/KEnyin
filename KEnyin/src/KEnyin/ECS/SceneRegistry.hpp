#pragma once

#include "KEnyin/ECS/ComponentType.hpp"

namespace KEnyin
{
    class Component;
    class GameObject;
}

namespace KEnyin
{
    class SceneRegistry
    {
    public:
        using MComponents = std::unordered_map<unsigned int, Component>;
        using Registry = std::unordered_map<ComponentType, MComponents>;

        template<typename T>
        std::vector<T> getCompontentsOfType(T type);

        template<typename T>
        void addComponent(const GameObject& gameObject, const T& component);
         
    private:
        Registry _registry;
    };
}
