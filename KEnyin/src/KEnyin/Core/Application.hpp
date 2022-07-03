#pragma once

#include "KEnyin/Core/ApplicationLayerStack.hpp"
#include "KEnyin/Core/Window.hpp"
#include "KEnyin/Events/ApplicationEvent.hpp"
#include "KEnyin/SceneManagement/Scene.hpp"

namespace KEnyin
{
    class Application
    {
    public:
        static constexpr unsigned int kApplicationWidth = 1280;
        static constexpr unsigned int kApplicationHeight = 720;

        Application(const std::string& name = "KEnyin App");
        virtual ~Application();

        void run();
        void onEvent(Event& event);
        
        void pushLayer(ApplicationLayer* layer);
        void pushOverlay(ApplicationLayer* layer);

        inline Window& getWindow() const { return *_window; }

    private:
        bool onWindowClosed(WindowCloseEvent e);
        void update(Timestep timestep);
        void render();

        std::unique_ptr<Window> _window;
        bool _running = true;
        ApplicationLayerStack _applicationLayerStack;
    };

    //To be defined by KEnyin Applications
    Application* CreateApplication();
}

