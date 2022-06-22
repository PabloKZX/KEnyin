#pragma once

#include "KEnyin/SceneManagement/Scene.hpp"
#include <entt.hpp>

namespace KEnyin
{
    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);
        Entity(const Entity& other) = default;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            KECheck_Engine(!HasComponent<T>(), "Entity already has component!");
            T& component = _scene->_registry.emplace<T>(_entityHandle, std::forward<Args>(args)...);
            return component;
        }

        template<typename T>
        T& GetComponent()
        {
            KECheck_Engine(HasComponent<T>(), "Entity does not have component!");
            return _scene->_registry.get<T>(_entityHandle);
        }

        template<typename T>
        bool HasComponent()
        {
            return _scene->_registry.all_of<T>(_entityHandle);
        }

        template<typename T>
        void RemoveComponent()
        {
            KECheck_Engine(HasComponent<T>(), "Trying to remove unexisting component!");
            _scene->_registry.remove<T>(_entityHandle);
        }
    private:
        entt::entity _entityHandle = entt::null;
        Scene* _scene;
    };
}
