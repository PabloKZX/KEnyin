#include "pch.hpp"
#include "KEnyin/Core/Application.hpp"
#include "spdlog/spdlog.h"

namespace KEnyin
{
    Application::Application()
    {
        ServiceLocator::get().loadServices();
    }

    Application::~Application()
    {
        ServiceLocator::get().clearServices();
    }

    void Application::run()
    {
        KELog("Esto es un trace");
        KESuccess_Engine("Esto es un log");
        KEWarn("Esto es un warn");
        KEError_Engine("Esto es un error");
        KECritical("Esto es un error critico");

        KECheck(false, "Esto es un assert");

        while (true);
    }
}