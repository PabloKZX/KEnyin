#pragma once

#include "KEnyin/SceneManagement/Scene.hpp"

namespace KEnyin::SceneManagement
{
    class SceneManager
    {
    public:
        SceneManager() = default;
        ~SceneManager() = default;

        inline Scene& getActiveScene() const { return *_activeScene; }

    private:
        std::unique_ptr<Scene> _activeScene;
    };
}

