#include "pch.hpp"
#include "KEnyin/Platform/Windows/WindowsWindow.hpp"

namespace KEnyin
{
    Window* Window::create(const WindowData& windowData)
    {
        return new WindowsWindow(windowData);
    }

    WindowsWindow::WindowsWindow(const WindowData& windowData)
    {
        init(windowData);
    }

    WindowsWindow::~WindowsWindow()
    {
        shutdown();
    }

    void WindowsWindow::init(const WindowData& windowData)
    {
        _windowData = windowData;

        KESuccess_Engine("Creating window {0} {1} {2}", _windowData.name, _windowData.width, _windowData.height);

        /* Initialize the library */
        int success = glfwInit();
        KECheck_Engine(success, "Failed to initialize GLFW!");

        /* Create a windowed mode window and its OpenGL context */
        _nativeWindow = glfwCreateWindow(windowData.width, windowData.height, windowData.name.c_str(), nullptr, nullptr);
        if (!_nativeWindow)
        {
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(_nativeWindow);
    }

    void WindowsWindow::shutdown()
    {
        glfwDestroyWindow(_nativeWindow);
    }

    void WindowsWindow::onUpdate()
    {
        glfwSwapBuffers(_nativeWindow);
        glfwPollEvents();
    }
}