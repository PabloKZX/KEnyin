#include "pch.hpp"
#include "KEnyin/SceneManagement/Scene.hpp"
#include "KEnyin/ECS/GameObject.hpp"
#include "KEnyin/ECS/Transform.hpp"
#include "KEnyin/Rendering/Camera.hpp"
#include "KEnyin/Rendering/Renderer.hpp"
#include "KEnyin/ECS/EntityManager.hpp"

namespace KEnyin
{

    Scene::Scene()
        : _entityManager(EntityManager())
    {

    }

    GameObjectSharedPtr Scene::newGameObject()
    {
        _entityManager.push(std::make_shared<GameObject>());
        return _entityManager.getGameObjects().back();
    }

    template<typename T>
    void Scene::onComponentAdded(const GameObject& gameObject, const T& component)
    {

    }

    void Scene::loadSampleScene()
    {
        KELog_Engine("Transform component ID: {0}", _entityManager.GetId<Transform>());
        KELog_Engine("Transform component ID: {0}", _entityManager.GetId<Transform>());
        KELog_Engine("Renderer component ID: {0}", _entityManager.GetId<Renderer>());
        KELog_Engine("Transform component ID: {0}", _entityManager.GetId<Transform>());
        KELog_Engine("Camera component ID: {0}", _entityManager.GetId<Camera>());

        GameObjectSharedPtr object = newGameObject();
        _entityManager.AddComponent<Transform>(object);
    }

    EntityID Scene::getNewEntityID() const
    {
        return _entityManager.getGameObjects().size();
    }

}
