#pragma once

#include "KEnyin/Core/Window.hpp"
#include "KEnyin/Events/ApplicationEvent.hpp"

//TODO: Delete
#include "KEnyin/Rendering/Shader.hpp"
#include "KEnyin/Rendering/Texture2D.hpp"
#include "KEnyin/SceneManagement/Scene.hpp"

namespace KEnyin
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
        void onEvent(Event& event);

        inline Window& getWindow() const { return *_window; }
        inline Scene& getActiveScene() const { return *_activeScene; }
    private:
        bool onWindowClosed(WindowCloseEvent e);
        void update(long long timestep);
        void render();

        std::unique_ptr<Window> _window;
        std::unique_ptr<Shader> _shader;
        std::unique_ptr<Scene> _activeScene;
        bool _running = true;

        unsigned int _vertexArray;
        unsigned int _vertexBuffer;
        unsigned int _indexBuffer;

        std::unique_ptr<Texture2D> _texture;
        std::unique_ptr<Texture2D> _texture2;

        std::vector<glm::vec3> _cubePositions;
    };

    //To be defined by KEnyin Applications
    Application* CreateApplication();
}

