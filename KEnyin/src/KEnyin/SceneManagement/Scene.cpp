#include "pch.hpp"
#include "KEnyin/SceneManagement/Scene.hpp"
#include "KEnyin/SceneManagement/GameObject.hpp"

namespace KEnyin
{
    void Scene::onUpdate(float timestep)
    {
        for (const auto& gameObject : _gameObjects)
        {
            gameObject->onUpdate(timestep);
        }
    }

    void Scene::onRender()
    {

    }

    void Scene::addGameObject(GameObject&& gameObject)
    {
        _gameObjects.push_back(std::make_unique<GameObject>(std::move(gameObject)));
    }
}
