#include "KEditor/Drawers/Drawer.hpp"
#include "KEditor/Utils/KEditorUtils.hpp"

namespace KEnyin::KEditor
{
    template <>
    void Drawer::onImGuiRender<Components::LightComponent>(Components::LightComponent& component)
    {
        std::shared_ptr<Light> light = component.light;
        Light::LightData& lightData = light->getLightData();

        std::vector<std::string> typeStrings = { "Directional", "Point", "Spot" };
        std::string currentTypeString = typeStrings[(int)light->getLightData().type];

        utils::drawEnum("Type", typeStrings, currentTypeString, [light](int selectedIndex)
        {
            light->getLightData().type = (Light::LightType)selectedIndex;
        });

        ImGui::ColorEdit4("Color", (float*)&lightData.lightColor, ImGuiColorEditFlags_NoInputs);

        if(lightData.type == Light::LightType::Point || lightData.type == Light::LightType::Spot)
        {
            ImGui::DragFloat("Range", &lightData.range, 0.3f, 0.1f, FLT_MAX);

            ImGui::Columns(2, "", false);
            ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() * 0.3f);
            ImGui::Text("Attenuation");

            ImGui::NextColumn();
            ImGui::DragFloat("Linear", &lightData.linearAttenuation, 0.1f, 0.0f, FLT_MAX);
            ImGui::DragFloat("Quadratic", &lightData.quadraticAttenuation, 0.01f, 0.0f, FLT_MAX);
            ImGui::Columns(1);
        }

        if(lightData.type == Light::LightType::Spot)
        {
            ImGui::Columns(2, "", false);
            ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() * 0.3f);
            ImGui::Text("Angles");

            ImGui::NextColumn();

            ImGui::SliderAngle("Inner", &lightData.innerAngle, 0.0f, 179.0f);
            ImGui::SliderAngle("Outer", &lightData.outerAngle, 0.0f, 179.0f);
            ImGui::Columns(1);
        }
    }
}
