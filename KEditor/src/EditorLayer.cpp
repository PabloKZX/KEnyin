#include "EditorLayer.hpp"

namespace KEnyin
{
    EditorLayer::EditorLayer()
        : ApplicationLayer("EditorLayer")
    {
    }

    void EditorLayer::onAttach()
    {
        _activeScene = std::make_shared<Scene>();
        _activeScene->loadAsSampleScene();
    }

    void EditorLayer::onDetach()
    {
        
    }

    void EditorLayer::onUpdate(Timestep ts)
    {
        _activeScene->onUpdate(ts);
    }

    void EditorLayer::onImGuiRender()
    {
        
    }

    void EditorLayer::onEvent(Event& event)
    {
        
    }

    void EditorLayer::onRender()
    {
        _activeScene->renderScene();
    }
}
