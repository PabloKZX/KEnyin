#pragma once

#include "KEditor/Drawers/Drawer.hpp"
#include <imgui.h>
#include <imgui_internal.h>
#include <KEnyin.hpp>

namespace KEnyin::KEditor::utils
{
    template<typename T>
    void drawComponent(const std::string& name, Entity entity)
    {
        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
        if(!entity.HasComponent<T>())
        {
            return;
        }

        auto& component = entity.GetComponent<T>();
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {4, 4});
        ImGui::PushFont(boldFont);
        bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
        ImGui::PopFont();
        ImGui::PopStyleVar();

        ImGui::SameLine(ImGui::GetContentRegionAvail().x);
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
            Drawer::onImGuiRender<T>(component);
            ImGui::TreePop();
        }

        if(removeComponent)
        {
            entity.RemoveComponent<T>();
        }
        
        ImGui::NewLine();
        ImGui::Separator();
    }

    void drawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 70.0f);
}
