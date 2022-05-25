#pragma once

namespace KEnyin
{
    class Component
    {
        friend class GameObject;
    public:
        virtual ~Component() = default;
    protected:
        Component() = default;
        Component(const Component&) = default;

        virtual void onStart() {};
        virtual void onUpdate(float timestep) {};
        virtual void onRender() {};

        bool _enabled;
    };
}
