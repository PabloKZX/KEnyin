#include "Hierarchy.hpp"
#include "imgui/imgui.h"

namespace KEnyin::KEditor::Panels
{
    Hierarchy::Hierarchy(const std::shared_ptr<Scene>& context)
    {
        setContext(context);
    }

    void Hierarchy::setContext(const std::shared_ptr<Scene>& context)
    {
        _context = context;
    }

    void Hierarchy::onImGuiRender()
    {
        ImGui::Begin("Hierarchy");
        ImGui::End();
    }
}
