#include "KEditor/Panels/Inspector.hpp"
#include "KEditor/Utils/KEditorUtils.hpp"
#include <imgui.h>
#include <imgui_internal.h>

namespace KEnyin::KEditor::Panels
{
    Inspector::Inspector(Entity entity)
    {
        setContext(entity);
    }

    void Inspector::setContext(Entity entity)
    {
        _entity = entity;
    }

    void Inspector::onImGuiRender()
    {
        ImGui::Begin("Inspector");

        if(!_entity)
        {
            ImGui::End();
            return;
        }

        drawComponents(_entity);

        ImGui::End();
    }

    void Inspector::drawComponents(Entity entity)
    {
        if (!entity.HasComponent<Components::Tag>())
        {
            return;
        }
        
        //TODO: Enable and disable entities
        static bool enabled = true;
        ImGui::Checkbox("##enabled", &enabled);
        ImGui::SameLine();
        
        auto& tag = entity.GetComponent<Components::Tag>().tag;

        char buffer[256];
        memset(buffer, 0, sizeof(buffer));
        std::strncpy(buffer, tag.c_str(), sizeof(buffer));
        ImGui::PushItemWidth(ImGui::GetWindowWidth() - 50.0f);
        if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
        {
            tag = std::string(buffer);
        }
        ImGui::PopItemWidth();

        utils::drawComponent<Components::Transform>("Transform", entity, [](auto& component)
        {
            utils::drawVec3Control("Position", component.position);
            glm::vec3 rotation = component.eulerAngles();
            utils::drawVec3Control("Rotation", rotation);
            component.setEulerAngles(rotation);
            utils::drawVec3Control("Scale", component.scale, 1.0f);
        });
        
        if (ImGui::Button("Add Component", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
        {
            ImGui::OpenPopup("AddComponent");
        }

        if (ImGui::BeginPopup("AddComponent"))
        {
            ImGui::EndPopup();
        }
    }
}
