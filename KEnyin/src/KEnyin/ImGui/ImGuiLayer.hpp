#pragma once

#include "KEnyin/Core/ApplicationLayer.hpp"
#include "KEnyin/Events/ApplicationEvent.hpp"
#include "KEnyin/Events/KeyEvent.hpp"
#include "KEnyin/Events/MouseEvent.hpp"

namespace KEnyin
{
    class ImGuiLayer : public ApplicationLayer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onEvent(Event& event) override;
        
        void begin();
        void end();
        
        inline void setBlockEvents(bool block) { _blockEvents = block; }
    private:
        void setDarkThemeColors();
        
        bool _blockEvents = false;
    };
}
