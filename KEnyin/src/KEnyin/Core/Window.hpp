#pragma once

#include "pch.hpp"

namespace KEnyin
{
    struct WindowData
    {
        std::string name = "KEnyin Window";
        int width = 1280;
        int height = 720;
    };

    class Window
    {
    public:
        virtual ~Window() {};

        virtual void onUpdate() = 0;
        virtual unsigned int getWidth() const = 0;
        virtual unsigned int getHeight() const = 0;
        virtual void* getNativeWindow() const = 0;

        static Window* create(const WindowData& data = WindowData());
    };
}


