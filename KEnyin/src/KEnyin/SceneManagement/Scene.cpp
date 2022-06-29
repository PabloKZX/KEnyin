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

    void Scene::loadAsSampleScene()
    {
        glm::vec3 cubePositions[] =
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

        std::shared_ptr<Material> material = std::make_shared<Material>();
        std::shared_ptr<Mesh> mesh = std::shared_ptr<Mesh>(Primitives::CreateCube());

        material->shader = std::make_unique<Shader>("assets/Shaders/Sample.kesh");

        material->textures.push_back(std::make_unique<Texture2D>("assets/Textures/container.jpg"));
        material->textures.push_back(std::make_unique<Texture2D>("assets/Textures/awesomeface.png"));

        material->shader->bind();
        material->shader->setInt("uTexture1", 0);
        material->shader->setInt("uTexture2", 1);

        class CameraController : public ScriptableEntity
        {
        public:
            float radius = 10;

            void onCreate()
            {

            }

            void onUpdate(Timestep ts)
            {
                auto& position = GetComponent<Components::Transform>().position;

                float speed = 5.0f;

                if (Input::getKeyDown(Key::A))
                    position.x -= speed * ts;
                if (Input::getKeyDown(Key::D))
                    position.x += speed * ts;
                if (Input::getKeyDown(Key::W))
                    position.y += speed * ts;
                if (Input::getKeyDown(Key::S))
                    position.y -= speed * ts;
            }

            void onDestroy()
            {

            }
        };

        class Rotator : public ScriptableEntity
        {
        public:
            void onCreate()
            {

            }

            void onUpdate(Timestep ts)
            {
                auto& transform = GetComponent<Components::Transform>();
                transform.rotation.y += 0.05f;
            }

            void onDestroy()
            {

            }
        };

        Entity camera = createEntity("Camera");
        camera.getTransform().position = { 0, 0, 3 };
        camera.AddComponent<Components::CameraComponent>();
        camera.AddScript<CameraController>();

        int index = 0;
        for (const auto& position : cubePositions)
        {
            Entity cube = createEntity("Cube" + std::to_string(index++));

            cube.getTransform().position = position;

            Components::MeshRenderer& meshRenderer = cube.AddComponent<Components::MeshRenderer>();
            meshRenderer.mesh = mesh;
            meshRenderer.material = material;

            cube.AddScript<Rotator>();
        }
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
