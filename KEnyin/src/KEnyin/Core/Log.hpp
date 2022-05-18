#pragma once

#include "spdlog/spdlog.h"

namespace KEnyin
{
    class Log
    {
    public:
        using spdLogger = std::shared_ptr<spdlog::logger>;

        static void init();

        inline static spdLogger getAppLogger() { return _appLogger; }
        inline static spdLogger getEngineLogger() { return _engineLogger; }

    private:
        static spdLogger _appLogger;
        static spdLogger _engineLogger;
    };

    // Core log macros
    #define KELog_Engine(...)       ::KEnyin::Log::getEngineLogger()->trace(__VA_ARGS__)
    #define KESuccess_Engine(...)   ::KEnyin::Log::getEngineLogger()->info(__VA_ARGS__)
    #define KEWarn_Engine(...)      ::KEnyin::Log::getEngineLogger()->warn(__VA_ARGS__)
    #define KEError_Engine(...)     ::KEnyin::Log::getEngineLogger()->error(__VA_ARGS__)
    #define KECritical_Engine(...)  ::KEnyin::Log::getEngineLogger()->critical(__VA_ARGS__)

    // Client log macros
    #define KELog(...)              ::KEnyin::Log::getAppLogger()->trace(__VA_ARGS__)
    #define KESuccess(...)          ::KEnyin::Log::getAppLogger()->info(__VA_ARGS__)
    #define KEWarn(...)             ::KEnyin::Log::getAppLogger()->warn(__VA_ARGS__)
    #define KEError(...)            ::KEnyin::Log::getAppLogger()->error(__VA_ARGS__)
    #define KECritical(...)         ::KEnyin::Log::getAppLogger()->critical(__VA_ARGS__)
}
