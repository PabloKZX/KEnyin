#pragma once

#include "KEnyin/ECS/ComponentType.hpp"

namespace KEnyin
{
    class Component
    {
        friend class GameObject;
    public:
        virtual ~Component() = default;

        inline ComponentType getType() const { return _type; }
    protected:
        Component(ComponentType type) : _type(type) {};
        Component(const Component&) = default;

        virtual void onStart() {};
        virtual void onUpdate(float timestep) {};
        virtual void onRender() {};

        bool _enabled = true;
        ComponentType _type = ComponentType::None;
    };
}
