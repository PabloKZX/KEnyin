#pragma once

#include "KEnyin/Core/Timestep.hpp"
#include "KEnyin/Events/Event.hpp"

namespace KEnyin
{
    class ApplicationLayer
    {
    public:
        ApplicationLayer(const std::string& name = "Layer");
        virtual ~ApplicationLayer() = default;
        
        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(Timestep ts) {}
        virtual void onRender() {}
        virtual void onImGuiRender() {}
        virtual void onEvent(Event& event) {}
        
        const std::string& getName() const { return _debugName; }
    protected:
        std::string _debugName;
    };
}
