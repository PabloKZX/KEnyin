#include "KEditor/Panels/Inspector.hpp"
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

    template<typename T, typename UIFunction>
    static void drawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
    {
        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
        if(!entity.HasComponent<T>())
        {
            return;
        }

        auto& component = entity.GetComponent<T>();
        ImVec2 contentRegionAvail = ImGui::GetContentRegionAvail();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {4, 4});
        ImGui::Separator();
        bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
        ImGui::PopStyleVar();

        ImGui::SameLine();
        if(ImGui::Button("+"))
        {
            ImGui::OpenPopup("ComponentSettings");
        }

        bool removeComponent = false;
        if(ImGui::BeginPopup("ComponentSettings"))
        {
            if(ImGui::MenuItem("Remove Component"))
            {
                removeComponent = true;
            }

            ImGui::EndPopup();
        }

        if(open)
        {
            uiFunction(component);
            ImGui::TreePop();
        }

        if(removeComponent)
        {
            entity.RemoveComponent<T>();
        }
        
        ImGui::NewLine();
        ImGui::Separator();
    }

    static void drawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 50.0f)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();
        
        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0, 0});
        
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(boldFont);
        
        if (ImGui::Button("X"))
        {
            values.x = resetValue;
        }
        
        ImGui::PopFont();
        ImGui::PopStyleColor(3);
        
        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();
        
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y"))
        {
            values.y = resetValue;
        }
        ImGui::PopFont();
        ImGui::PopStyleColor(3);
        
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Z"))
        {
            values.z = resetValue;
        }
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();
    }

    void Inspector::drawComponents(Entity entity)
    {
        if (entity.HasComponent<Components::Tag>())
        {
            auto& tag = entity.GetComponent<Components::Tag>().tag;

            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            std::strncpy(buffer, tag.c_str(), sizeof(buffer));
            if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
            {
                tag = std::string(buffer);
            }
        }

        drawComponent<Components::Transform>("Transform", entity, [](auto& component)
        {
            drawVec3Control("Position", component.position);
            glm::vec3 rotation = glm::degrees(component.rotation);
            drawVec3Control("Rotation", rotation);
            component.rotation = glm::radians(rotation);
            drawVec3Control("Scale", component.scale, 1.0f);
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
