#pragma once

#include "KEnyin/Events/Event.hpp"

namespace KEnyin
{
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Closing Window";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : _width(width), _height(height)
        {
        }

        inline unsigned int getWidth() const { return _width; }
        inline unsigned int getHeight() const { return _height; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << _width << ", " << _height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        unsigned int _width;
        unsigned int _height;
    };
}
