#include "Inspector.hpp"
#include <imgui/imgui.h>

namespace KEnyin::KEditor::Panels
{
    Inspector::Inspector(Entity* entity)
    {
        setContext(entity);
    }

    void Inspector::setContext(Entity* entity)
    {
        _entity = entity;
    }

    void Inspector::onImGuiRender()
    {
        ImGui::Begin("Inspector");

        ImGui::End();
    }
}
