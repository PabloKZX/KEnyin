#pragma once

#include "KEnyin/ECS/EntityManager.fwd.hpp"

namespace KEnyin
{
    class Scene;
}

namespace KEnyin
{
    class GameObject
    {
    public:
        GameObject();
        ~GameObject() = default;

        template<typename T>  
        T& AddComponent()
        {
            //HZ_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
            T& component = T();
            _scene->onComponentAdded<T>(*this, component);
            return component;
        }

        inline EntityID getId() const { return _id; }
        inline ComponentMask getMask() const { return _componentMask; }
    private:
        ComponentMask _componentMask;
        EntityID _id;
        const Scene& _scene;
    };
}

