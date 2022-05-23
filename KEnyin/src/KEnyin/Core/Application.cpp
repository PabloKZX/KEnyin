#include "pch.hpp"
#include "KEnyin/Core/Application.hpp"

#include <GLFW/glfw3.h>
namespace KEnyin
{
    Application::Application()
    {
        ServiceLocator::get().loadServices();

        _window = std::unique_ptr<Window>(Window::create());
        _window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
    }

    Application::~Application()
    {
        ServiceLocator::get().clearServices();
    }

    void Application::run()
    {
        while (_running)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            _window->onUpdate();
        }
    }

    void Application::onEvent(Event& event)
    {
        KELog_Engine(event.toString());

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClosed, this, std::placeholders::_1));
    }

    bool Application::onWindowClosed(WindowCloseEvent e)
    {
        _running = false;
        return true;
    }
}