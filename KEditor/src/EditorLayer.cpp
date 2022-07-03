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
    }

    void EditorLayer::onEvent(Event& event)
    {
        
    }

    void EditorLayer::onRender()
    {
        _activeScene->renderScene();
    }
}
