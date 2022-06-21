#include "pch.hpp"
#include "KEnyin/Core/Application.hpp"
#include "KEnyin/Core/Window.hpp"
#include "KEnyin/Editor/Editor.hpp"
#include "KEnyin/Events/ApplicationEvent.hpp"
#include "KEnyin/Input/Input.hpp"
#include "KEnyin/Input/KeyCodes.hpp"

#include "KEnyin/Rendering/Shader.hpp"
#include "KEnyin/Rendering/Texture2D.hpp"

#include "KEnyin/SceneManagement/SceneManager.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace KEnyin
{
    namespace application_constants
    {
        constexpr unsigned int kApplicationWidth = 1280;
        constexpr unsigned int kApplicationHeight = 720;
        constexpr int kMsPerUpdate = 40;
    }

    Application::Application()
    {
        using namespace application_constants;
        
        WindowProps props;
        props.title = "KEnyin";
        props.width = kApplicationWidth;
        props.height = kApplicationHeight;

        //TODO: move props instead on copying
        _window = std::unique_ptr<Window>(Window::create(props));
        _window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

        ServiceLocator::get().loadServices(this);

        glGenVertexArrays(1, &_vertexArray);
        glBindVertexArray(_vertexArray);

        glGenBuffers(1, &_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

        float vertices[] = 
        {   // positions          // uvs
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        _cubePositions = 
        {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        // color attribute
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
        //glEnableVertexAttribArray(1);

        // uvs attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


        //TODO: Local Paths
#ifdef KE_PLATFORM_WINDOWS
        _shader = std::make_unique<Shader>("D:/Dev/KEnyin/KEnyin/src/KEnyin/Shaders/Sample.kesh");

        // Textures
        _texture = std::make_unique<Texture2D>("D:/Dev/KEnyin/KEnyin/assets/container.jpg");
        _texture2 = std::make_unique<Texture2D>("D:/Dev/KEnyin/KEnyin/assets/awesomeface.png");
#endif

#ifdef KE_PLATFORM_MACOS
        _shader = std::make_unique<Shader>("/Users/pablo.martinez/dev/KEnyin/KEnyin/src/KEnyin/Shaders/Sample.kesh");

        // Textures
        _texture = std::make_unique<Texture2D>("/Users/pablo.martinez/dev/KEnyin/KEnyin/assets/container.jpg");
        _texture2 = std::make_unique<Texture2D>("/Users/pablo.martinez/dev/KEnyin/KEnyin/assets/awesomeface.png");
#endif
        
        _shader->bind();
        _shader->setInt("uTexture1", 0);
        _shader->setInt("uTexture2", 1);

        std::shared_ptr<Scene> scene = std::make_shared<Scene>();
        ServiceLocator::get().getSceneManager().setActiveScene(scene);
        scene->loadSampleScene();
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
            long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();

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

    void Application::update(long long timestep)
    {

    }

    void Application::render()
    {
        using namespace application_constants;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (Input::getKeyDown(KE_KEY_TAB))
        {
            KESuccess_Engine("TAB pressed");
        }

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, { 0.0f, 0.0f, -3.0f });

        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)kApplicationWidth / (float)kApplicationHeight, 0.1f, 100.0f);


        _shader->setMatrix4("uView", view);
        _shader->setMatrix4("uProjection", proj);

        _texture->bind(GL_TEXTURE0);
        _texture2->bind(GL_TEXTURE1);

        _shader->bind();

        int index = 0;
        for (const glm::vec3& cubePos : _cubePositions)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePos);

            float angle = 20.0f * index++;
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), { 1.0f, 0.3f, 0.5f });

            _shader->setMatrix4("uModel", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
            
        glBindVertexArray(_vertexArray);

        ServiceLocator::get().getEditor().update();

        _window->onUpdate();
    }

}
