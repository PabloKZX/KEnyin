#include "pch.hpp"
#include "KEnyin/Rendering/Renderer.hpp"
#include "KEnyin/Rendering/Texture2D.hpp"
#include "KEnyin/Rendering/Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "KEnyin/Core/Application.hpp"
#include "KEnyin/Rendering/Primitives.hpp"

namespace KEnyin
{
    void Renderer::Init() 
    {
//        _material = std::make_shared<Material>();
//        _mesh = std::shared_ptr<Mesh>(Primitives::CreateCube());
//
//        //TODO: Local Paths
//#ifdef KE_PLATFORM_WINDOWS
//        _material->shader = std::make_unique<Shader>("D:/Dev/KEnyin/KEnyin/src/KEnyin/Shaders/Sample.kesh");
//
//        // Textures
//        _material->textures.push_back(std::make_unique<Texture2D>("D:/Dev/KEnyin/KEnyin/assets/container.jpg"));
//        _material->textures.push_back(std::make_unique<Texture2D>("D:/Dev/KEnyin/KEnyin/assets/awesomeface.png"));
//#endif
//
//#ifdef KE_PLATFORM_MACOS
//        material->shader = std::make_unique<Shader>("/Users/pablo.martinez/dev/KEnyin/KEnyin/src/KEnyin/Shaders/Sample.kesh");
//
//        // Textures
//        material->textures.push_back(std::make_unique<Texture2D>("/Users/pablo.martinez/dev/KEnyin/KEnyin/assets/container.jpg"));
//        material->textures.push_back(std::make_unique<Texture2D>("/Users/pablo.martinez/dev/KEnyin/KEnyin/assets/awesomeface.png"));
//#endif
    }

    void Renderer::Shutdown()
    {

    }

    void Renderer::BeginScene()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //_material->shader->bind();
        //_mesh->bind(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::DrawMesh(const glm::mat4& transform, const Components::MeshRenderer& meshComponent)
    {
        Mesh& mesh = *meshComponent.mesh;
        Material& material = *meshComponent.material;
        Shader& shader = *material.shader;

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, { 0.0f, 0.0f, -3.0f });

        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)Application::kApplicationWidth / (float)Application::kApplicationHeight, 0.1f, 100.0f);

        shader.bind();  
        shader.setMatrix4("uView", view);
        shader.setMatrix4("uProjection", proj);
        shader.setMatrix4("uModel", transform);

        for (size_t i = 0; i < material.textures.size(); i++)
        {
            material.textures[i]->bind(GL_TEXTURE0 + i);
        }

        mesh.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
