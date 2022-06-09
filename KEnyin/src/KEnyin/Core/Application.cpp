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
#include <stb_image.h>

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

        float vertices[] =
        {
            // positions        // colors         // texture coords
             0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // top left
        };

        unsigned int indices[] =
        {
            0, 1, 3,
            1, 2, 3,
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // uvs attribute
        glGenBuffers(1, &_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        _shader = std::make_unique<Shader>("D:/Dev/KEnyin/KEnyin/src/KEnyin/Shaders/Sample.kes");

        // Textures
     
        // create texture
        unsigned int _texture;
        glGenTextures(1, &_texture);
        glBindTexture(GL_TEXTURE_2D, _texture);

        // set the texture wrapping/filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // load texture
        int width, height, nrChannels;
        unsigned char* data = stbi_load("D:/Dev/KEnyin/KEnyin/assets/container.jpg", &width, &height, &nrChannels, 0);

        // generate texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
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
        glBindTexture(GL_TEXTURE_2D, _texture);
        glBindVertexArray(_vertexArray);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        ServiceLocator::get().getEditor().update();

        _window->onUpdate();
    }

}