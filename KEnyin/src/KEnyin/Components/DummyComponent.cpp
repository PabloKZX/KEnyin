#include "pch.hpp"
#include "KEnyin/Components/DummyComponent.hpp"

namespace KEnyin
{
    void DummyComponent::onUpdate(float timestep)
    {
        KESuccess_Engine("I'm a dummy component {0}", timestep);
    }
}
