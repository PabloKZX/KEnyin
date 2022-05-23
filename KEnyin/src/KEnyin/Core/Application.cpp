#include "pch.hpp"
#include "KEnyin/Core/Application.hpp"
#include "KEnyin/Input/Input.hpp"

#include "KEnyin/Input/KeyCodes.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace KEnyin
{
    Application::Application()
    {
        ServiceLocator::get().loadServices(this);

        _window = std::unique_ptr<Window>(Window::create());
        _window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

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

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(getWindow().getNativeWindow()), true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    Application::~Application()
    {
        ServiceLocator::get().clearServices();
    }

    void Application::run()
    {
        while (_running)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            if (Input::getKeyDown(KE_KEY_TAB))
            {
                KESuccess_Engine("TAB pressed");
            }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::ShowDemoWindow();

            ImGuiIO& io = ImGui::GetIO();
            io.DisplaySize = ImVec2(static_cast<float>(getWindow().getWidth()), static_cast<float>(getWindow().getHeight()));

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }

            _window->onUpdate();
        }
    }

    void Application::onEvent(Event& event)
    {
        //KELog_Engine(event.toString());

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClosed, this, std::placeholders::_1));
    }

    bool Application::onWindowClosed(WindowCloseEvent e)
    {
        _running = false;
        return true;
    }
}