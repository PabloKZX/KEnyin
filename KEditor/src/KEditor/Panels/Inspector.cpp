#include "KEditor/Panels/Inspector.hpp"
#include "KEditor/Utils/KEditorUtils.hpp"
#include "KEditor/Drawers/Drawer.hpp"
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
        ImGui::Separator();

        utils::drawComponent<Components::Transform>("Transform", entity);
        utils::drawComponent<Components::CameraComponent>("Camera", entity);
        utils::drawComponent<Components::MeshRenderer>("Mesh Renderer", entity);
        utils::drawComponent<Components::NativeScript>("Native Script", entity);
        utils::drawComponent<Components::LightComponent>("Light", entity);
        
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
