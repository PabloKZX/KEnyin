#pragma once

#include "KEnyin/ECS/ECS.fwd.hpp"

namespace KEnyin
{
    class Component
    {
    public:
        virtual ~Component() = default;

    protected:
        Component() = default;
        Component(const Component&) = default;
    };
}
