#pragma once

#include "KEnyin/Core/Window.hpp"
#include <GLFW/glfw3.h>

#ifdef KE_PLATFORM_MACOS
namespace KEnyin
{
    class MacOsWindow : public Window
    {
    public:
        MacOsWindow(const WindowProps& windowProps);
        virtual ~MacOsWindow();

        void onUpdate() override;

        inline unsigned int getWidth() const override { return _windowData.width; }
        inline unsigned int getHeight() const override { return _windowData.height; }

        inline virtual void* getNativeWindow() const override { return _nativeWindow; }
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

#endif
