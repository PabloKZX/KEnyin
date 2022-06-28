#pragma once

#include "KEnyin/Core/Window.hpp"
#include "KEnyin/Events/ApplicationEvent.hpp"
#include "KEnyin/SceneManagement/Scene.hpp"

#include "KEnyin/Rendering/Renderer.hpp"

namespace KEnyin
{
    class Application
    {
    public:
        static constexpr unsigned int kApplicationWidth = 1280;
        static constexpr unsigned int kApplicationHeight = 720;

        Application();
        virtual ~Application();

        void run();
        void onEvent(Event& event);

        inline Window& getWindow() const { return *_window; }
        inline Scene& getActiveScene() const { return *_activeScene; }

        
    private:
        bool onWindowClosed(WindowCloseEvent e);
        void update(Timestep timestep);
        void render();

        std::unique_ptr<Window> _window;
        std::shared_ptr<Scene> _activeScene;
        bool _running = true;
    };

    //To be defined by KEnyin Applications
    Application* CreateApplication();
}

