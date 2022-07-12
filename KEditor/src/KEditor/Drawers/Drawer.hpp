#pragma once

#include <KEnyin.hpp>

namespace KEnyin::KEditor
{
    class Drawer
    {
    public:
        template <typename T>
        static void onImGuiRender(T& component);
    };
}
