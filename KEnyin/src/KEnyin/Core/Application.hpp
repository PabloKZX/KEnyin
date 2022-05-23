#pragma once

#include "KEnyin/Core/Window.hpp"
#include "KEnyin/Events/ApplicationEvent.hpp"

namespace KEnyin
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
        void onEvent(Event& event);
    private:
        bool onWindowClosed(WindowCloseEvent e);

        std::unique_ptr<Window> _window;
        bool _running = true;
    };

    //To be defined by KEnyin Applications
    Application* CreateApplication();
}

