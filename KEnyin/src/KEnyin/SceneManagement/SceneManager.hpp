#pragma once

#include "KEnyin/SceneManagement/Scene.hpp"

namespace KEnyin::SceneManagement
{
    class SceneManager
    {
    public:
        SceneManager() = default;
        ~SceneManager() = default;

        inline void setActiveScene(std::shared_ptr<Scene> scene)
        {
            _activeScene = scene;
        };

        inline const Scene& const getActiveScene()
        {
            return *_activeScene;
        };

    private:
        std::shared_ptr<Scene> _activeScene;
    };
}

