#pragma once

#include "Panels/Hierarchy.hpp"
#include "Panels/Inspector.hpp"
#include "Panels/Console.hpp"
#include "Panels/Project.hpp"
#include <KEnyin.hpp>

namespace KEnyin::KEditor
{
    class EditorLayer : public ApplicationLayer
    {
    public:
        EditorLayer();
        virtual ~EditorLayer() = default;
        
        virtual void onAttach() override;
        virtual void onDetach() override;
        
        virtual void onUpdate(Timestep ts) override;
        virtual void onImGuiRender() override;
        virtual void onEvent(Event& event) override;
        virtual void onRender() override;
    private:
        std::shared_ptr<Scene> _activeScene;
        std::shared_ptr<Texture2D> _texture;
        std::shared_ptr<Framebuffer> _framebuffer;
        std::shared_ptr<Camera> _mainCamera;

        glm::vec2 _viewportSize = {0.0f, 0.0f};

        // Panels
        Panels::Hierarchy _hierarchyPanel;
        Panels::Inspector _inspectorPanel;
        Panels::Console _consolePanel;
        Panels::Project _projectPanel;
    };
}
