#pragma once

#include "KEnyin/Core/Window.hpp"
#include <GLFW/glfw3.h>

namespace KEnyin
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& windowProps);
        virtual ~WindowsWindow();

        void onUpdate() override;

        inline unsigned int getWidth() const override { return _windowData.width; }
        inline unsigned int getHeight() const override { return _windowData.height; }

        inline virtual void* getNativeWindow() const { return _nativeWindow; };
        inline void setEventCallback(const EventCallback& callback) override { _windowData.eventCallback = callback; }

    private:
        struct WindowData
        {
            std::string title;
            unsigned int width;
            unsigned int height;
            EventCallback eventCallback;
        };

        GLFWwindow* _nativeWindow;
        WindowData _windowData;

        void init(const WindowProps& windowData);
        void shutdown();
    };
}

