#include "pch.hpp"
#include "KEnyin/Core/Application.hpp"
#include "KEnyin/Core/Timestep.hpp"
#include "KEnyin/Core/Window.hpp"
#include "KEnyin/Editor/Editor.hpp"
#include "KEnyin/Events/ApplicationEvent.hpp"
#include "KEnyin/Input/Input.hpp"
#include "KEnyin/Input/KeyCodes.hpp"

#include "KEnyin/Rendering/Renderer.hpp"
#include "KEnyin/SceneManagement/SceneManager.hpp"
#include "KEnyin/SceneManagement/Components.hpp"
#include "KEnyin/SceneManagement/Entity.hpp"

namespace KEnyin
{
    namespace application_constants
    {
        constexpr int kMsPerUpdate = 40;
    }

    Application::Application()
    {
        using namespace application_constants;
        
        WindowProps props;
        props.title = "KEnyin";
        props.width = kApplicationWidth;
        props.height = kApplicationHeight;

        //TODO: move props instead on copying
        _window = std::unique_ptr<Window>(Window::create(props));
        _window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

        ServiceLocator::get().loadServices(this);

        Renderer::Init();

        _activeScene = std::make_shared<Scene>();
        _activeScene->loadAsSampleScene();
    }
    
    Application::~Application()
    {
        ServiceLocator::get().clearServices();
    }

    void Application::run()
    {
        auto previousTime = std::chrono::system_clock::now();
        double lag = 0.0;

        while (_running)
        {
            auto currentTime = std::chrono::system_clock::now();
            Timestep timestep = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();

            previousTime = currentTime;
            lag += timestep;

            while (lag >= application_constants::kMsPerUpdate)
            {
                update(timestep);
                lag -= application_constants::kMsPerUpdate;
            }

            render();
        }
    }

    void Application::onEvent(Event& event)
    {
        //KELog_Engine(event.toString());

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClosed, this, std::placeholders::_1));
    }

    bool Application::onWindowClosed(WindowCloseEvent e)
    {
        _running = false;
        return true;
    }

    void Application::update(Timestep timestep)
    {
        _activeScene->onUpdate(timestep);
    }

    void Application::render()
    {
        using namespace application_constants;

        Renderer::BeginScene();
        _activeScene->renderScene();
        Renderer::EndScene();

        ServiceLocator::get().getEditor().update();
        _window->onUpdate();
    }
}
