#include "Hierarchy.hpp"
#include "imgui/imgui.h"

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

        // Right-click on blank space
        if (ImGui::BeginPopupContextWindow(0, 1, false))
        {
            if (ImGui::MenuItem("Create Empty Entity"))
            {
                _context->createEntity("New Entity");
            }

            ImGui::EndPopup();
        }

        ImGui::End();
    }

    void Hierarchy::drawEntity(Entity entity)
    {
        ImGuiTreeNodeFlags flags = ((_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

        auto& tag = entity.GetComponent<Components::Tag>().tag;
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
        if(ImGui::IsItemClicked())
        {
            _selectedEntity = entity;
            _onEntitySelectedChanged(_selectedEntity);
        }

        // Open entities
        if(opened)
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
            bool opened = false;
            if (opened)
            {
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

        // Delete entities
        bool entityDeleted = false;
        if(ImGui::BeginPopupContextItem())
        {
            if(ImGui::MenuItem("Delete entity"))
            {
                entityDeleted = true;
            }

            ImGui::EndPopup();
        }

        if(entityDeleted)
        {
            _context->destroyEntity(entity);
            if(_selectedEntity == entity)
            {
                _selectedEntity = {};
            }
        }
    }

    void Hierarchy::setOnEntitySelectedChangedCallback(OnEntitySelectedChangeCallback onEntitySelectedChanged)
    {
        _onEntitySelectedChanged = onEntitySelectedChanged;
    }
}
