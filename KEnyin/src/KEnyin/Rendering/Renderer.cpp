#include "pch.hpp"
#include "KEnyin/Rendering/Renderer.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "KEnyin/Core/Application.hpp"

namespace KEnyin
{
    void Renderer::Init() 
    {
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

    }

    void Renderer::Shutdown()
    {

    }

    void Renderer::BeginScene()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, { 0.0f, 0.0f, -3.0f });

        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)Application::kApplicationWidth / (float)Application::kApplicationHeight, 0.1f, 100.0f);

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
    }

    void Renderer::EndScene()
    {

    }
}
