#pragma once

#include "KEnyin/Core/Window.hpp"
#include "KEnyin/Events/ApplicationEvent.hpp"
#include "KEnyin/Rendering/Shader.hpp"
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
    private:
        bool onWindowClosed(WindowCloseEvent e);
        void update(float timestep);
        void render();

        std::unique_ptr<Window> _window;
        std::unique_ptr<Shader> _shader;
        std::unique_ptr<Scene> _activeScene;
        bool _running = true;

        unsigned int _vertexArray;
        unsigned int _vertexBuffer;
        unsigned int _indexBuffer;
    };

    //To be defined by KEnyin Applications
    Application* CreateApplication();
}

