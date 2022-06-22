#include "pch.hpp"
#include "KEnyin/SceneManagement/Scene.hpp"
#include "KEnyin/SceneManagement/Components.hpp"
#include "KEnyin/SceneManagement/Entity.hpp"

namespace KEnyin
{
    Scene::Scene()
    {

    }

    Scene::~Scene()
    {

    }

    Entity Scene::createEntity(const std::string& name)
    {
        Entity entity = { _registry.create(), this };
        entity.AddComponent<TransformComponent>();
        entity.AddComponent<TagComponent>(name);
        return entity;
    }

    void Scene::onUpdate(long long timestep)
    {
        auto group = _registry.group<TransformComponent>(entt::get<MeshRendererComponent>);
        for (const auto& entity : group)
        {

        }
    }
}
