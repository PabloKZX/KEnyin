#include "pch.hpp"
#include "KEnyin/Core/Application.hpp"

#include <GLFW/glfw3.h>
namespace KEnyin
{
    Application::Application()
    {
        ServiceLocator::get().loadServices();

        _window = std::unique_ptr<Window>(Window::create());
    }

    Application::~Application()
    {
        ServiceLocator::get().clearServices();
    }

    void Application::run()
    {
        while (true)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            _window->onUpdate();
        }
    }
}