#include "pch.hpp"
#include "KEnyin/Core/Application.hpp"
#include "KEnyin/Input/Input.hpp"
#include "KEnyin/Editor/Editor.hpp"
#include "KEnyin/Input/KeyCodes.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace KEnyin
{
    Application::Application()
    {
        _window = std::unique_ptr<Window>(Window::create());
        _window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

        ServiceLocator::get().loadServices(this);

        glGenVertexArrays(1, &_vertexArray);
        glBindVertexArray(_vertexArray);

        glGenBuffers(1, &_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

        float vertices[3 * 3] =
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

        glGenBuffers(1, &_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);

        unsigned int indices[3] =
        {
            0, 1, 2,
        };

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertexSource = R"(
            #version 440 core
            layout (location = 0) in vec3 aPos;

            out vec3 v_Position;

            void main()
            {
                v_Position = aPos;
                gl_Position = vec4(aPos, 1.0);
            }
        )";

        std::string fragmentSource = R"(
            #version 440 core
            out vec4 fragColor;

            in vec3 v_Position;

            void main()
            {
                fragColor = vec4(v_Position * 0.5 + 0.5, 1.0);
            }
        )";

        _shader = std::make_unique<Shader>(vertexSource, fragmentSource);
    }

    Application::~Application()
    {
        ServiceLocator::get().clearServices();
    }

    void Application::run()
    {
        while (_running)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            if (Input::getKeyDown(KE_KEY_TAB))
            {
                KESuccess_Engine("TAB pressed");
            }

            _shader->bind();

            glBindVertexArray(_vertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            ServiceLocator::get().getEditor().update();

            _window->onUpdate();
        }
    }

    void Application::onEvent(Event& event)
    {
        //KELog_Engine(event.toString());

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClosed, this, std::placeholders::_1));
    }

    bool Application::onWindowClosed(WindowCloseEvent e)
    {
        _running = false;
        return true;
    }
}