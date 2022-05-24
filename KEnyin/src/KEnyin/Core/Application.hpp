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

        inline Window& getWindow() const { return *_window; }
    private:
        bool onWindowClosed(WindowCloseEvent e);

        std::unique_ptr<Window> _window;
        bool _running = true;

        unsigned int _vertexArray;
        unsigned int _vertexBuffer;
        unsigned int _indexBuffer;
    };

    //To be defined by KEnyin Applications
    Application* CreateApplication();
}

