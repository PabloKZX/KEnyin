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
    };
}
