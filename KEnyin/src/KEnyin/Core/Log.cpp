#include "KEnyin/Core/Log.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace KEnyin
{
    Log::spdLogger Log::_appLogger;
    Log::spdLogger Log::_engineLogger;

    void Log::init()
    {
        spdlog::set_pattern("[%T] %^[%n %l]%$ %v");

        _engineLogger = spdlog::stdout_color_mt("KENYIN");
        _engineLogger->set_level(spdlog::level::trace);

        _appLogger = spdlog::stdout_color_mt("APP");
        _appLogger->set_level(spdlog::level::trace);
    }
}