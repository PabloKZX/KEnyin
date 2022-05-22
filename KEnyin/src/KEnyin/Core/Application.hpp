#pragma once

#include "KEnyin/Core/Window.hpp"

namespace KEnyin
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
    private:
        std::unique_ptr<Window> _window;
    };

    //To be defined by KEnyin Applications
    Application* CreateApplication();
}

