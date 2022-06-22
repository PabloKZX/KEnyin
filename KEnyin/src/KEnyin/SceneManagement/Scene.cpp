#include "pch.hpp"
#include "KEnyin/SceneManagement/Scene.hpp"
#include "KEnyin/ECS/Entity.hpp"
#include "KEnyin/ECS/Transform.hpp"
#include "KEnyin/Rendering/Camera.hpp"
#include "KEnyin/Rendering/Renderer.hpp"
#include "KEnyin/ECS/CustomBehaviour.hpp"

namespace KEnyin
{
    Scene::Scene()
        : _entityManager(std::make_unique<EntityManager>())
    {

    }

    void Scene::loadSampleScene()
    {
        KELog_Engine("Camera component ID: {0}", _entityManager->GetComponentTypeID<Camera>());
        KELog_Engine("Renderer component ID: {0}", _entityManager->GetComponentTypeID<Renderer>());
        KELog_Engine("Renderer component ID: {0}", _entityManager->GetComponentTypeID<CustomBehaviour>());

        Entity gameObject;
        gameObject.name = "Objeto 1";
        gameObject.AddComponent<Camera>();
        gameObject.AddComponent<Renderer>();

        Entity gameObject2;
        gameObject2.name = "Objeto 2";
        gameObject2.AddComponent<Renderer>();

        Entity gameObject3;
        gameObject3.name = "Objeto 3";
        gameObject3.AddComponent<Camera>();
        gameObject3.AddComponent<Renderer>();
        gameObject3.AddComponent<CustomBehaviour>();

        _entityManager->logRegistry();
    }
}
