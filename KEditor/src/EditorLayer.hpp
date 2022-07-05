#pragma once

#include <KEnyin.hpp>

namespace KEnyin
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
        
        glm::vec2 _viewportSize = {0.0f, 0.0f};
    };
}
