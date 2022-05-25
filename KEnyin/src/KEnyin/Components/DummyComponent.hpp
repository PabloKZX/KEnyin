#pragma once

#include "KEnyin/Components/Component.hpp"

namespace KEnyin
{
    class DummyComponent : public Component
    {
    protected:
        virtual void onUpdate(float timestep);
    };

}
