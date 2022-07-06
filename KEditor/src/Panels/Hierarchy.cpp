#include "Hierarchy.hpp"
#include <imgui/imgui.h>

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

        KECheck(_context, "No valid context to render!");

        _context->_registry.each([&](auto entityId)
            {
                Entity entity{ entityId , _context.get() };
                drawEntity(entity);
            });

        ImGui::End();
    }

    void Hierarchy::drawEntity(Entity entity)
    {
        auto& tag = entity.GetComponent<Components::Tag>().tag;
        ImGui::TreeNodeEx(tag.c_str());
    }
}
