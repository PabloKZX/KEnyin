#pragma once

#include "KEnyin/SceneManagement/GameObject.hpp"

namespace KEnyin
{
    class Scene
    {
    public:
        using VGameObjects = std::vector<std::unique_ptr<GameObject>>;

        Scene() {};
        Scene(const std::string& name) : _name(name) {};
        ~Scene() = default;

        void onUpdate(float timestep);
        void onRender();

        void addGameObject(GameObject&& gameObject);
    private:
        std::string _name = "New Scene";
        VGameObjects _gameObjects;
    };
}
