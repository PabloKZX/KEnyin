#pragma once

#include "KEnyin/SceneManagement/Scene.hpp"

namespace KEnyin
{
    class Entity
    {
    public:
        std::string name = "New Game Object";
        EntityID ID;

        Entity();
        ~Entity() = default;

        template<typename T>  
        T& AddComponent()
        {
            T& component = _scene->_entityManager->AddComponent<T>(ID);
            ComponentTypeID componentTypeID = _scene->_entityManager->GetComponentTypeID<T>();

            //TODO: check that the id is less than the max amount of components
            _mask.set(componentTypeID);
            return component;
        }

    private:
        std::shared_ptr<Scene> _scene;
        ComponentMask _mask;
    };
}

