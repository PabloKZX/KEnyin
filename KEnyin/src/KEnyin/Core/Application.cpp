#include "pch.hpp"
#include "KEnyin/Core/Application.hpp"
#include "KEnyin/Core/Timestep.hpp"
#include "KEnyin/Core/Window.hpp"
#include "KEnyin/Events/ApplicationEvent.hpp"
#include "KEnyin/Input/Input.hpp"
#include "KEnyin/Input/KeyCodes.hpp"
#include "KEnyin/Rendering/Renderer.hpp"
#include "KEnyin/Utils/PlatformUtils.hpp"

#include "KEnyin/SceneManagement/SceneManager.hpp"

namespace KEnyin
{
    namespace application_constants
    {
        constexpr float kMsPerUpdate = 40.0f;
    }

    Application::Application(const std::string& name)
    {
        using namespace application_constants;
        
        WindowProps props;
        props.title = name;
        props.width = kApplicationWidth;
        props.height = kApplicationHeight;

        //TODO: move props instead on copying
        _window = std::unique_ptr<Window>(Window::create(props));
        _window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

        ServiceLocator::get().loadServices(this);
        
        _imGuiLayer = std::make_unique<ImGuiLayer>();
        pushOverlay(_imGuiLayer.get());
        
        Renderer::Init();
    }
    
    Application::~Application()
    {
        ServiceLocator::get().clearServices();
    }

    void Application::run()
    {
        double previousTime = Time::getTime();
        double lag = 0.0f;
        while (_running)
        {
            double currentTime = Time::getTime();
            double elapsed = currentTime - previousTime;
            previousTime = currentTime;

            lag += elapsed;

            while (lag >= application_constants::kMsPerUpdate)
            {
                update(elapsed / 1000.0f);
                
                lag -= application_constants::kMsPerUpdate;
            }

            render();
        }
    }

    void Application::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClosed, this, std::placeholders::_1));
        
        for (auto it = _applicationLayerStack.rbegin(); it != _applicationLayerStack.rend(); ++it)
        {
            if (event.handled)
            {
                break;
            }
            
            (*it)->onEvent(event);
        }
    }

    bool Application::onWindowClosed(WindowCloseEvent e)
    {
        _running = false;
        return true;
    }

    void Application::update(Timestep timestep)
    {
        for (ApplicationLayer* layer : _applicationLayerStack)
        {
            layer->onUpdate(timestep);
        }
        
    }

    void Application::render()
    {
        for (ApplicationLayer* layer : _applicationLayerStack)
        {
            layer->onRender();
        }

        _imGuiLayer->begin();
        for (ApplicationLayer* layer : _applicationLayerStack)
        {
            layer->onImGuiRender();
        }
        _imGuiLayer->end();

        _window->onUpdate();
    }

    void Application::pushLayer(ApplicationLayer* layer)
    {
        _applicationLayerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(ApplicationLayer* layer)
    {
        _applicationLayerStack.pushOverlay(layer);
        layer->onAttach();
    }
}
