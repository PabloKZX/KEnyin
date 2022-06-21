#include "pch.hpp"
#include "KEnyin/ECS/EntityManager.hpp"

namespace KEnyin
{
    void EntityManager::logRegistry()
    {
        std::string log = "Entity Manager registry: \n";

        for (const auto& [componentId, entityComponentPair] : _registry)
        {
            log += "Component ID: " + std::to_string(componentId) + "\n";
            for (const auto& [entityID, component] : entityComponentPair)
            {
                log += "Entity ID: " + std::to_string(entityID) + "\n";
            }

            log += "\n";
        }

        KELog_Engine(log);
    }
}
