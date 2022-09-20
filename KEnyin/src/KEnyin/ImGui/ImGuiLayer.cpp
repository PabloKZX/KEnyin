#include "pch.hpp"
#include "KEnyin/Core/Application.hpp"
#include "KEnyin/Core/ServiceLocator.hpp"
#include "KEnyin/ImGui/ImGuiLayer.hpp"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace KEnyin
{
    ImGuiLayer::ImGuiLayer() : ApplicationLayer("ImGuiLayer")
    {
    }

    void ImGuiLayer::onAttach()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;
        
        //TODO: Local Paths
        io.Fonts->AddFontFromFileTTF("D:/Dev/KEnyin/KEditor/assets/Fonts/Arial/ARIALBD.TTF", 14.0f);
        io.FontDefault = io.Fonts->AddFontFromFileTTF("D:/Dev/KEnyin/KEditor/assets/Fonts/Arial/ARIAL.TTF", 14.0f);

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();
        
        setDarkThemeColors();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        const Application& app = ServiceLocator::get().getApplication();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow().getNativeWindow());
        
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::onDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::onEvent(Event& event)
    {
        if (_blockEvents)
        {
            ImGuiIO& io = ImGui::GetIO();
            event.handled |= event.isInCategory(EventCategoryMouse) & io.WantCaptureMouse;
            event.handled |= event.isInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
        }
    }

    void ImGuiLayer::begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::end()
    {
        ImGuiIO& io = ImGui::GetIO();
        const Application& app = ServiceLocator::get().getApplication();
        io.DisplaySize = ImVec2((float)app.getWindow().getWidth(), (float)app.getWindow().getHeight());

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::setDarkThemeColors()
    {
        auto& colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4{ 0.2196f, 0.2196f, 0.2196f, 1.0f };
        
        // Headers
        colors[ImGuiCol_Header] = ImVec4{ 0.1960f, 0.1960f, 0.1960f, 1.0f };
        colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3019f, 0.3019f, 0.3019f, 1.0f };
        colors[ImGuiCol_HeaderActive] = ImVec4{ 0.1686f, 0.3647f, 0.5254f, 1.0f };
        
        // Buttons
        colors[ImGuiCol_Button] = ImVec4{ 0.3450f, 0.3450f, 0.3450f, 1.0f };
        colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.4039f, 0.4039f, 0.4039f, 1.0f };
        colors[ImGuiCol_ButtonActive] = ImVec4{ 0.2705f, 0.3686f, 0.4784f, 1.0f };
        
        // Frame BG
        // Background of checkbox, radio button, plot, slider, text input
        colors[ImGuiCol_FrameBg] = ImVec4{ 0.1647f, 0.1647f, 0.1647f, 1.0f };
        colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3176f, 0.3176f, 0.3176f, 1.0f };
        colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.1803f, 0.3803f, 0.5882f, 1.0f };
        
        // Tabs
        colors[ImGuiCol_Tab] = ImVec4{ 0.1882f, 0.1882f, 0.1882f, 1.0f };
        colors[ImGuiCol_TabHovered] = ImVec4{ 0.1882f, 0.1882f, 0.1882f, 1.0f  };
        colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
        colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.1882f, 0.1882f, 0.1882f, 1.0f  };
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.1882f, 0.1882f, 0.1882f, 1.0f  };
        
        // Title
        colors[ImGuiCol_TitleBg] = ImVec4{ 0.1254f, 0.1254f, 0.1254f, 1.0f };
        colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.1254f, 0.1254f, 0.1254f, 1.0f };
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.1254f, 0.1254f, 0.1254f, 1.0f };
        
        // Separators
        colors[ImGuiCol_Separator] = ImVec4{ 0.0784f, 0.0784f, 0.0784f, 1.0f };
        colors[ImGuiCol_SeparatorHovered] = ImVec4{ 0.0784f, 0.0784f, 0.0784f, 1.0f };
        colors[ImGuiCol_SeparatorActive] = ImVec4{ 0.0784f, 0.0784f, 0.0784f, 1.0f };
        
        // Docking
        // Preview overlay color when about to docking something
        colors[ImGuiCol_DockingPreview] = ImVec4{ 0.2196f, 0.2196f, 0.2196f, 1.0f };
        // Background color for empty node (e.g. CentralNode with no window docked into it)
        colors[ImGuiCol_DockingEmptyBg] = ImVec4{ 0.2196f, 0.2196f, 0.2196f, 1.0f };

        // Checkmark
        colors[ImGuiCol_CheckMark] = ImVec4{ 0.8196f, 0.8196f, 0.8196f, 1.0f };
    }
}
