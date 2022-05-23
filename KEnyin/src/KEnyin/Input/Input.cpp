#include "pch.hpp"
#include "KEnyin/Input/Input.hpp"
#include "KEnyin/Core/Application.hpp"
#include "KEnyin/Core/ServiceLocator.hpp"
#include <GLFW/glfw3.h>

namespace KEnyin
{
    bool Input::getKeyDown(int keyCode)
    {
        auto window = static_cast<GLFWwindow*>(ServiceLocator::get().getApplication().getWindow().getNativeWindow());
        int state = glfwGetKey(window, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::getMouseButtonDown(int button)
    {
        auto window = static_cast<GLFWwindow*>(ServiceLocator::get().getApplication().getWindow().getNativeWindow());
        int state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::getMousePosition()
    {
        auto window = static_cast<GLFWwindow*>(ServiceLocator::get().getApplication().getWindow().getNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { static_cast<float>(xPos),  static_cast<float>(yPos) };
    }
}
