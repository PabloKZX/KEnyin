#include "KEnyin/Core/Application.hpp"
#include "KEnyin/Core/Log.hpp"
#include "KEnyin/Core/Assert.hpp"
#include "spdlog/spdlog.h"

namespace KEnyin
{
    Application::Application()
    {
    }

    Application::~Application()
    {
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