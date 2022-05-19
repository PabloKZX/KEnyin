#include "pch.hpp"
#include "KEnyin/Core/ServiceLocator.hpp"

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

    void ServiceLocator::loadServices()
    {

    }

    void ServiceLocator::clearServices()
    {
        
    }
}
