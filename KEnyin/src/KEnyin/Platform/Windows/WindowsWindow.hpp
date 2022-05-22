#pragma once

#include "KEnyin/Core/Window.hpp"
#include <GLFW/glfw3.h>

namespace KEnyin
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowData& windowData);
        virtual ~WindowsWindow();

        void onUpdate() override;

        inline unsigned int getWidth() const override { return _windowData.width; }
        inline unsigned int getHeight() const override { return _windowData.height; }

        inline virtual void* getNativeWindow() const { return _nativeWindow; };

    private:
        GLFWwindow* _nativeWindow;
        WindowData _windowData; 

        void init(const WindowData& windowData);
        void shutdown();
    };
}

