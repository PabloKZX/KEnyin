#include "EditorLayer.hpp"

#include "imgui/imgui.h"

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
        
        _texture = std::make_shared<Texture2D>("/Users/pablo.martinez/dev/KEnyin/KEnyinApp/assets/Textures/container.jpg");
        FramebufferData data =
        {
            .width = 1280,
            .height = 720,
            .samples = 1,
        };
        _framebuffer = std::make_shared<Framebuffer>(data);
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
        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        
        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }
        
        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;
        
        if (opt_fullscreen)
            ImGui::PopStyleVar(2);
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
        ImGui::Begin("KEditor", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();
        
        // Dockspace
        ImGuiIO& io = ImGui::GetIO();
        if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        
        
        // Windows
        static bool showDemoWindow = false;
        static bool showAnotherWindow = false;

        if(showDemoWindow)
            ImGui::ShowDemoWindow(&showDemoWindow);

        {
            static float f = 0.0f;
            static int counter = 0;
            static float* clearColor = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &showDemoWindow);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &showAnotherWindow);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        
        // 3. Show another simple window.
        if (showAnotherWindow)
        {
            ImGui::Begin("Another Window", &showAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                showAnotherWindow = false;
            ImGui::End();
        }
        
        // Viewport
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
            ImGui::Begin("Viewport");
            ImVec2 viewPortPanelSize = ImGui::GetContentRegionAvail();
            if(_viewportSize != glm::vec2(viewPortPanelSize.x, viewPortPanelSize.y))
            {
                //_framebuffer->resize((unsigned int)viewPortPanelSize.x, (unsigned int)viewPortPanelSize.y);
                _viewportSize = {viewPortPanelSize.x, viewPortPanelSize.y};
            }
            unsigned int textureID = _framebuffer->getColorBufferId();
            ImGui::Image((void*)textureID, ImVec2{_viewportSize.x, _viewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});
            ImGui::End();
            ImGui::PopStyleVar();
        }
        
        ImGui::End();
    }

    void EditorLayer::onEvent(Event& event)
    {
        
    }

    void EditorLayer::onRender()
    {
        _framebuffer->bind();
        _activeScene->renderScene();
        _framebuffer->unbind();
    }
}
