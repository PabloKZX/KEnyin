#pragma once

#include "KEnyin/SceneManagement/GameObject.hpp"

namespace KEnyin
{
    class Scene
    {
    public:
        using VGameObjects = std::vector<std::unique_ptr<GameObject>>;

        Scene();
        Scene(const std::string& name);
        ~Scene() {};

        void addGameObject(GameObject gameObject);

    private:
        std::string _name = "New Scene";
        VGameObjects _gameObjects;
    };
}
