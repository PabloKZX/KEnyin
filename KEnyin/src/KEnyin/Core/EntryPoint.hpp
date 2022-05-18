#pragma once

#include "KEnyin/Core/Base.hpp"

extern KEnyin::Application* KEnyin::CreateApplication();

int main(int argc, char** argv)
{
    KEnyin::Log::init();

    auto app = KEnyin::CreateApplication();
    app->run();
    delete app;
}
