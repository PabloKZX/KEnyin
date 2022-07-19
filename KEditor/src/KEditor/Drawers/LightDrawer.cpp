#include "KEditor/Drawers/Drawer.hpp"
#include "KEditor/Utils/KEditorUtils.hpp"

namespace KEnyin::KEditor
{
    template <>
    void Drawer::onImGuiRender<Components::LightComponent>(Components::LightComponent& component)
    {
        std::shared_ptr<Light> light = component.light;

        Color color = light->getColor();

        ImGui::ColorEdit4("Color", (float*)&light->getColor(), ImGuiColorEditFlags_NoInputs);
    }
}
