#pragma once

#include "KEnyin/ECS/Component.hpp"

namespace KEnyin
{
    class MeshRenderer : public Component
    {
    public:
        virtual void onRender();
    };
}


