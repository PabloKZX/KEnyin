#include "pch.hpp"
#include "KEnyin/Core/ServiceLocator.hpp"
#include "KEnyin/SceneManagement/SceneManager.hpp"
#include "KEnyin/Rendering/Renderer.hpp"

#define SAFE_DELETE(service) \
    if(service)              \
    {                        \
        delete service;      \
        service = nullptr;   \
    }

namespace KEnyin
{
    ServiceLocator::ServiceLocator()
    {
    }

    ServiceLocator& ServiceLocator::get()
    {
        static ServiceLocator locator;
        return locator;
    }

    void ServiceLocator::loadServices(Application* application)
    {
        _application = application;

        _sceneManager = new SceneManager();
    }

    void ServiceLocator::clearServices()
    {
        SAFE_DELETE(_sceneManager);
        
        Renderer::Shutdown();
    }
}
