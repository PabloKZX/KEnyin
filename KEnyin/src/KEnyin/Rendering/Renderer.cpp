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
    std::unique_ptr<Renderer::SceneData> Renderer::_sceneData = std::make_unique<Renderer::SceneData>();

    void Renderer::Init() 
    {

    }

    void Renderer::Shutdown()
    {

    }

    void Renderer::BeginScene(Camera* camera, const Renderer::VLights& lights)
    {
        Clear();
        _sceneData->viewProjectionMatrix = camera->getViewProjectionMatrix();
        _sceneData->cameraPosition = camera->getPosition();
        _sceneData->lights = lights;
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::DrawMesh(const glm::mat4& transform, const Components::MeshRenderer& meshComponent)
    {
        Mesh& mesh = *meshComponent.mesh;
        Material& material = *meshComponent.material;
        Shader& shader = *material.shader;

        Light& light = *_sceneData->lights[0];

        shader.bind();  
        shader.setMatrix4("uViewProjection", _sceneData->viewProjectionMatrix);
        shader.setMatrix4("uModel", transform);
        shader.setVector3f("material.color", material.color);
        shader.setFloat("material.shininess", material.shininess);
        shader.setColor3f("light.color", light.getLightData().lightColor);
        shader.setVector3f("light.direction", light.getDirection());
        shader.setVector3f("light.position", light.getPosition());
        shader.setFloat("light.range", light.getLightData().range);
        shader.setFloat("light.linearAttenuation", light.getLightData().linearAttenuation);
        shader.setFloat("light.quadraticAttenuation", light.getLightData().quadraticAttenuation);
        shader.setFloat("light.innerAngle", glm::cos(light.getLightData().innerAngle));
        shader.setFloat("light.outerAngle", glm::cos(light.getLightData().outerAngle));
        shader.setVector3f("uViewPos", _sceneData->cameraPosition);

        shader.setInt("lightType", light.getLightData().type);

        for (size_t i = 0; i < material.textures.size(); i++)
        {
            material.textures[i]->bind(GL_TEXTURE0 + i);
        }

        mesh.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void Renderer::SetClearColor(Color color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
