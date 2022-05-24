#pragma once

#include "imgui.h"

namespace KEnyin
{
    class Window;
}

namespace KEnyin::Editor
{
    class Editor
    {
    public:
        Editor();
        ~Editor();

        void init();
        void update();
        void shutdown();

    private:
        Window* _window;

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    };
}