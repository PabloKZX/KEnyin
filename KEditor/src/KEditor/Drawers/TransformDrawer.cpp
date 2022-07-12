#include "KEditor/Drawers/Drawer.hpp"
#include "KEditor/Utils/KEditorUtils.hpp"

namespace KEnyin::KEditor
{
    template <>
    void Drawer::onImGuiRender<Components::Transform>(Components::Transform& component)
    {
        utils::drawVec3Control("Position", component.position);
        glm::vec3 rotation = component.eulerAngles();
        utils::drawVec3Control("Rotation", rotation);
        component.setEulerAngles(rotation);
        utils::drawVec3Control("Scale", component.scale, 1.0f);
    }
}
