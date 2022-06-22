#include "pch.hpp"
#include "KEnyin/ECS/EntityManager.hpp"
#include "KEnyin/ECS/Entity.hpp"

namespace KEnyin
{
    void EntityManager::logRegistry()
    {
        std::string log = "Entity Manager registry: \n";

        for (const auto& entity : _entities)
        {
            log += entity->name + "\n";

            const std::vector<std::string> componentsStrings = GetComponentsStrings(entity->ID);

            for (const auto& component : componentsStrings)
            {
                log += component + "\n";
            }

            log += "\n";
        }

        KELog_Engine(log);
    }

    void EntityManager::onEntityAdded(Entity *gameObject)
    {
        _entities.push_back(std::shared_ptr<Entity>(gameObject));
    }
}
