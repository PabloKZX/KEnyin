#pragma once
#include <KEnyin.hpp>

namespace KEnyin::KEditor::Panels
{
    class Inspector
    {
    public:
        Inspector() = default;
        Inspector(Entity* entity);

        void setContext(Entity* entity);
        void onImGuiRender();
    private:
        Entity* _entity;
    };
}
