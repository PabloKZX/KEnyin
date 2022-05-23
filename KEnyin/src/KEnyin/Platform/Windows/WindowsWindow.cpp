#include "pch.hpp"
#include "KEnyin/Platform/Windows/WindowsWindow.hpp"
#include "KEnyin/Events/ApplicationEvent.hpp"
#include "KEnyin/Events/KeyEvent.hpp"
#include "KEnyin/Events/MouseEvent.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace KEnyin
{
    static bool glfwInitialized = false;

    Window* Window::create(const WindowProps& windowData)
    {
        return new WindowsWindow(windowData);
    }

    WindowsWindow::WindowsWindow(const WindowProps& windowData)
    {
        init(windowData);
    }

    WindowsWindow::~WindowsWindow()
    {
        shutdown();
    }

    void WindowsWindow::init(const WindowProps& windowProps)
    {
        _windowData.title = windowProps.title;
        _windowData.width = windowProps.width;
        _windowData.height = windowProps.height;

        KESuccess_Engine("Creating window {0} {1} {2}", _windowData.title, _windowData.width, _windowData.height);

        if (!glfwInitialized)
        {
            int success = glfwInit();
            KECheck_Engine(success, "Failed to initialize GLFW!");
            glfwSetErrorCallback([](int error, const char* desc)
            {
                KEError_Engine("GLFW Error: ({0}) {1}", error, desc);
            });
            glfwInitialized = true;
        }

        _nativeWindow = glfwCreateWindow(_windowData.width, _windowData.height, _windowData.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(_nativeWindow);

        int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        KECheck_Engine(success, "Failed to initialize glad!");

        KELog_Engine("OpenGL Info");
        KELog_Engine("  Vendor:   {0}", glGetString(GL_VENDOR));
        KELog_Engine("  Renderer: {0}", glGetString(GL_RENDERER));
        KELog_Engine("  Version:  {0}", glGetString(GL_VERSION));

        glfwSetWindowUserPointer(_nativeWindow, &_windowData);

        glfwSetWindowCloseCallback(_nativeWindow, [](GLFWwindow* window)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                WindowCloseEvent event;
                data.eventCallback(event);
            });

        glfwSetWindowSizeCallback(_nativeWindow, [](GLFWwindow* window, int width, int height)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                WindowResizeEvent event(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
                data.eventCallback(event);
            });

        glfwSetMouseButtonCallback(_nativeWindow, [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        MouseButtonPressedEvent event(button);
                        data.eventCallback(event);
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        MouseButtonReleasedEvent event(button);
                        data.eventCallback(event);
                        break;
                    }
                }
            });

        glfwSetScrollCallback(_nativeWindow, [](GLFWwindow* window, double xOffset, double yOffset)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
                data.eventCallback(event);
            });

        glfwSetCursorPosCallback(_nativeWindow, [](GLFWwindow* window, double xPos, double yPos)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
                data.eventCallback(event);
            });

        glfwSetKeyCallback(_nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        KeyPressedEvent event(key, 0);
                        data.eventCallback(event);
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        KeyReleasedEvent event(key);
                        data.eventCallback(event);
                        break;
                    }
                    case GLFW_REPEAT:
                    {
                        KeyPressedEvent event(key, 1);
                        data.eventCallback(event);
                        break;
                    }
                }
            });

        glfwSetCharCallback(_nativeWindow, [](GLFWwindow* window, unsigned int keyCode)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                KeyTypedEvent event(keyCode);
                data.eventCallback(event);
            });

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