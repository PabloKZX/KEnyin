#include "KEditor/Drawers/Drawer.hpp"
#include "KEditor/Utils/KEditorUtils.hpp"

namespace KEnyin::KEditor
{
    template <>
    void Drawer::onImGuiRender<Components::CameraComponent>(Components::CameraComponent& component)
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
        ImGui::Columns(1);

        ImGui::PopItemWidth();
        ImGui::Unindent();
    }
}
