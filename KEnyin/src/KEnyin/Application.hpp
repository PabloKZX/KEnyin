#pragma once

namespace KEnyin
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
    };

    //To be defined by KEnyin Applications
    Application* CreateApplication();
}

