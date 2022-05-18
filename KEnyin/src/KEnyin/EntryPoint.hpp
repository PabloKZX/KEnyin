#pragma once

extern KEnyin::Application* KEnyin::CreateApplication();

int main(int argc, char** argv)
{
    auto app = KEnyin::CreateApplication();
    app->run();
    delete app;
}
