#pragma once

#include "pch.hpp"
#include "KEnyin/Events/Event.hpp"

namespace KEnyin
{
    struct WindowProps
    {
        std::string title = "KEnyin Window";
        int width = 1280;
        int height = 720;
        
    };

    class Window
    {
    public:
        using EventCallback = std::function<void(Event&)>;

        virtual ~Window() {};

        virtual void onUpdate() = 0;
        virtual unsigned int getWidth() const = 0;
        virtual unsigned int getHeight() const = 0;
        virtual void* getNativeWindow() const = 0;
        virtual void setEventCallback(const EventCallback& callback) = 0;

        static Window* create(const WindowProps& data = WindowProps());
    };
}


