#include "pch.hpp"
#include "KEnyin/Input/Input.hpp"
#include "KEnyin/Rendering/Primitives.hpp"
#include "KEnyin/Rendering/Renderer.hpp"
#include "KEnyin/SceneManagement/Components/Components.hpp"
#include "KEnyin/SceneManagement/Entity.hpp"
#include "KEnyin/SceneManagement/Scene.hpp"
#include "KEnyin/SceneManagement/ScriptableEntity.hpp"

#include <glm/glm.hpp>
#include <glfw/glfw3.h>

namespace KEnyin
{
    Entity Scene::createEntity(const std::string& name)
    {
        Entity entity = { _registry.create(), this };
        entity.AddComponent<Components::Transform>();
        entity.AddComponent<Components::Tag>(name);
        return entity;
    }

    void Scene::destroyEntity(Entity entity)
    {
        _registry.destroy(entity);
    }

    void Scene::onUpdate(Timestep timestep)
    {
        // Update scripts
        {
            _registry.view<Components::NativeScript>().each([=](auto entity, auto& nativeScript)
            {
                    //TODO:: Move to Scene::OnScenePlay
                    if (!nativeScript.instance)
                    {
                        nativeScript.instance = nativeScript.instantiateScript();
                        nativeScript.instance->_entity = Entity{ entity, this };
                        nativeScript.instance->onCreate();
                    }

                    nativeScript.instance->onUpdate(timestep);
            });
        }
    }

    void Scene::renderScene()
    {
        if (!_mainCamera)
        {
            KEError_Engine("No camera found!");
            return;
        }

        Renderer::BeginScene(_mainCamera->camera.get());
        auto view = _registry.view<Components::Transform, Components::MeshRenderer>();

        for (auto entity : view)
        {
            auto [transform, mesh] = view.get<Components::Transform, Components::MeshRenderer>(entity);

            Renderer::DrawMesh(transform.getTransformationMatrix(), mesh);
        }

        Renderer::EndScene();
    }

    template<>
    void Scene::onComponentAdded<Components::CameraComponent>(Entity entity, Components::CameraComponent& component)
    {
        if (!component.camera)
        {
            component.camera = std::make_unique<Camera>(entity.getTransform());
        }

        if (!_mainCamera)
        {
            _mainCamera = std::make_shared<Components::CameraComponent>(component);
        }
    }    
    
    template<>
    void Scene::onComponentAdded<Components::Transform>(Entity entity, Components::Transform& component)
    {
    }

    template<>
    void Scene::onComponentAdded<Components::MeshRenderer>(Entity entity, Components::MeshRenderer& component)
    {
    }

    template<>
    void Scene::onComponentAdded<Components::NativeScript>(Entity entity, Components::NativeScript& component)
    {
    }

    template<>
    void Scene::onComponentAdded<Components::Tag>(Entity entity, Components::Tag& component)
    {
    }
}
