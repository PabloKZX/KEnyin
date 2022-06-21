#pragma once
 
#include "KEnyin/ECS/EntityManager.hpp"
#include "KEnyin/SceneManagement/Scene.hpp"

namespace KEnyin
{
    class GameObject
    {
    public:
        std::string name = "New Game Object";
        EntityID ID;

        GameObject();
        ~GameObject() = default;

        template<typename T>  
        std::shared_ptr<T> AddComponent()
        {
            std::shared_ptr<T> component = std::make_shared<T>();
            _scene->_entityManager->onComponentAdded<T>(ID, this, component);
            return component;
        }

    private:
        std::shared_ptr<Scene> _scene;
    };
}

