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
        ImGui::Separator();

        utils::drawComponent<Components::Transform>("Transform", entity, [](auto& component)
        {
            utils::drawVec3Control("Position", component.position);
            glm::vec3 rotation = component.eulerAngles();
            utils::drawVec3Control("Rotation", rotation);
            component.setEulerAngles(rotation);
            utils::drawVec3Control("Scale", component.scale, 1.0f);
        });

        utils::drawComponent<Components::CameraComponent>("Camera", entity, [](auto& component)
        {
            std::shared_ptr<Camera> camera = component.camera;
            const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
            const char* currentProjectionTypeString = projectionTypeStrings[(int)camera->getProjectionType()];

            if(ImGui::BeginCombo("Projection", currentProjectionTypeString))
            {
                for (int i = 0; i < 2; i++)
                {
                    bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
                    if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
                    {
                        currentProjectionTypeString = projectionTypeStrings[i];
                        camera->setProjectionType((Camera::ProjectionType)i);
                    }

                    if (isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }

            ImGui::Indent();
            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.7f);
            if(camera->getProjectionType() == Camera::ProjectionType::Perspective)
            {
                float fov = glm::degrees(camera->getPerspectiveFOV());
                if(ImGui::SliderFloat("Field of View", &fov, 1, 179, "%.2f"))
                {
                    camera->setPerspectiveFOV(glm::radians(fov));
                }
            }

            if(camera->getProjectionType() == Camera::ProjectionType::Orthographic)
            {
                float size = camera->getOrthographicSize();
                if(ImGui::DragFloat("Size", &size))
                {
                    camera->setOrthographicSize(size);
                }
            }

            ImGui::Columns(2, "", false);
            ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() * 0.3f);
            ImGui::Text("Clipping planes");
            ImGui::NextColumn();

            //ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
            float nearPlane = camera->getNearPlane();
            if (ImGui::DragFloat("Near", &nearPlane, 0.3f, 0.1f, FLT_MAX))
            {
                camera->setNearPlane(nearPlane);
            }

            float farPlane = camera->getFarPlane();
            if (ImGui::DragFloat("Far", &farPlane, 0.3f, 0.1f, FLT_MAX))
            {
                camera->setFarPlane(farPlane);
            }

            //ImGui::PopItemWidth();
            ImGui::PopItemWidth();
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
