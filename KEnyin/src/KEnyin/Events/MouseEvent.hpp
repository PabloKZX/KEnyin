#pragma once

#include "KEnyin/Events/Event.hpp"

namespace KEnyin
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
            :_mouseX(x), _mouseY(y)
        {
        }

        inline float getX() const { return _mouseX; }
        inline float getY() const { return _mouseY; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << _mouseX << ", " << _mouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float _mouseX;
        float _mouseY;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
            :_xOffset(xOffset), _yOffset(yOffset)
        {
        }

        inline float getXOffset() const { return _xOffset; }
        inline float getYOffset() const { return _yOffset; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << _xOffset << ", " << _yOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float _xOffset;
        float _yOffset;
    };

    class MouseButtonEvent : public Event
    {
    public:
        inline int getMouseButton() const { return _button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    protected:
        MouseButtonEvent(int button)
            : _button(button)
        {
        }

        int _button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button)
        {
        }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << _button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button)
        {
        }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << _button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}