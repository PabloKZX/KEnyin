#include "pch.hpp"
#include "KEnyin/Core/Application.hpp"
#include "KEnyin/Core/Window.hpp"
#include "KEnyin/Editor/Editor.hpp"
#include "KEnyin/Events/ApplicationEvent.hpp"
#include "KEnyin/Input/Input.hpp"
#include "KEnyin/Input/KeyCodes.hpp"
#include "KEnyin/Rendering/Shader.hpp"

#include "KEnyin/SceneManagement/GameObject.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace KEnyin
{
    namespace application_constants
    {
        constexpr float kApplicationWidth = 700;
        constexpr float kApplicationHeight = 700;
        constexpr int kMsPerUpdate = 40;
    }

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

        //_shader = std::make_unique<Shader>("D:/Dev/KEnyin/KEnyin/src/KEnyin/Shaders/Sample.vs", "D:/Dev/KEnyin/KEnyin/src/KEnyin/Shaders/Sample.fs");
        _shader = std::make_unique<Shader>("D:/Dev/KEnyin/KEnyin/src/KEnyin/Shaders/Sample.kes");

        _activeScene = std::make_unique<Scene>("Sample scene");
        GameObject go;

        _activeScene->addGameObject(std::move(go));
    }
    
    Application::~Application()
    {
        ServiceLocator::get().clearServices();
    }

    void Application::run()
    {
        auto previousTime = std::chrono::system_clock::now();
        double lag = 0.0;

        while (_running)
        {
            auto currentTime = std::chrono::system_clock::now();
            double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();

            previousTime = currentTime;
            lag += elapsed;

            while (lag >= application_constants::kMsPerUpdate)
            {
                update(elapsed);
                lag -= application_constants::kMsPerUpdate;
            }

            render();
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

    void Application::update(float timestep)
    {
        _activeScene->onUpdate(timestep);
    }

    void Application::render()
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