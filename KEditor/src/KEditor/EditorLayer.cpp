#include "EditorLayer.hpp"

#include <imgui.h>
#include <imgui_internal.h>

namespace KEnyin::KEditor
{
    EditorLayer::EditorLayer()
        : ApplicationLayer("EditorLayer")
    {
    }

    void EditorLayer::onAttach()
    {
        Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        _activeScene = std::make_shared<Scene>();
        _hierarchyPanel.setContext(_activeScene);
        _hierarchyPanel.setOnEntitySelectedChangedCallback([=](Entity entity){_inspectorPanel.setContext(entity);});


        FramebufferData data;
        data.width = 1280,
            data.height = 720,
            data.samples = 1,

            _framebuffer = std::make_shared<Framebuffer>(data);

        glm::vec3 cubePositions[] =
        {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        std::shared_ptr<Material> material = std::make_shared<Material>();
        std::shared_ptr<Mesh> mesh = std::shared_ptr<Mesh>(Primitives::CreateCube());

#ifdef KE_PLATFORM_WINDOWS
        material->shader = std::make_unique<Shader>("assets/Shaders/Sample.kesh");

        material->textures.push_back(std::make_unique<Texture2D>("assets/Textures/container.jpg"));
        material->textures.push_back(std::make_unique<Texture2D>("assets/Textures/awesomeface.png"));
#endif

#ifdef KE_PLATFORM_MACOS
        material->shader = std::make_unique<Shader>("/Users/pablo.martinez/dev/KEnyin/KEnyinApp/assets/Shaders/Sample.kesh");

        material->textures.push_back(std::make_unique<Texture2D>("/Users/pablo.martinez/dev/KEnyin/KEnyinApp/assets/Textures/container.jpg"));
        material->textures.push_back(std::make_unique<Texture2D>("/Users/pablo.martinez/dev/KEnyin/KEnyinApp/assets/Textures/awesomeface.png"));
#endif

        material->shader->bind();
        material->shader->setInt("uTexture1", 0);
        material->shader->setInt("uTexture2", 1);

        class CameraController : public ScriptableEntity
        {
        public:
            float radius = 10;

            void onCreate()
            {

            }

            void onUpdate(Timestep ts)
            {
                auto& position = GetComponent<Components::Transform>().position;

                float speed = 5.0f;

                if (Input::getKeyDown(Key::A))
                    position.x -= speed * ts;
                if (Input::getKeyDown(Key::D))
                    position.x += speed * ts;
                if (Input::getKeyDown(Key::W))
                    position.y += speed * ts;
                if (Input::getKeyDown(Key::S))
                    position.y -= speed * ts;
            }

            void onDestroy()
            {

            }
        };

        class Rotator : public ScriptableEntity
        {
        public:
            void onCreate()
            {

            }

            void onUpdate(Timestep ts)
            {
                auto& transform = GetComponent<Components::Transform>();
                transform.rotation += 0.05f;
            }

            void onDestroy()
            {

            }
        };

        Entity camera = _activeScene->createEntity("Main Camera");
        camera.getTransform().position = { 0, 0, 3 };
        Components::CameraComponent& cameraComponent = camera.AddComponent<Components::CameraComponent>();
        _mainCamera = cameraComponent.camera;
        camera.AddScript<CameraController>();

        int index = 0;
        for (const auto& position : cubePositions)
        {
            Entity cube = _activeScene->createEntity("Cube" + std::to_string(index++));

            cube.getTransform().position = position;

            Components::MeshRenderer& meshRenderer = cube.AddComponent<Components::MeshRenderer>();
            meshRenderer.mesh = mesh;
            meshRenderer.material = material;

            cube.AddScript<Rotator>();
        }
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
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_NoWindowMenuButton;
        
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
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec2 minWinSize = style.WindowMinSize;
        style.WindowMinSize.x = 100.0f;
        style.WindowMinSize.y = 100.0f;
        if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        
        style.WindowMinSize = minWinSize;

        // Panels
        _hierarchyPanel.onImGuiRender();
        _inspectorPanel.onImGuiRender();
        _consolePanel.onImGuiRender();
        _projectPanel.onImGuiRender();

        // Windows
        static bool showDemoWindow = false;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Panels"))
            {
                if (ImGui::MenuItem("Demo Window"))
                    showDemoWindow = true;

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();

            if (showDemoWindow)
            {
                ImGui::ShowDemoWindow(&showDemoWindow);
            }

            // Viewport
            {
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
                ImGui::Begin("Viewport");
                ImVec2 viewPortPanelSize = ImGui::GetContentRegionAvail();
                if (_viewportSize != glm::vec2(viewPortPanelSize.x, viewPortPanelSize.y))
                {
                    //_framebuffer->resize((unsigned int)viewPortPanelSize.x, (unsigned int)viewPortPanelSize.y);
                    _viewportSize = { viewPortPanelSize.x, viewPortPanelSize.y };
                    _mainCamera->resize(viewPortPanelSize.x, viewPortPanelSize.y);
                }
                unsigned int textureID = _framebuffer->getColorBufferId();
                ImGui::Image((ImTextureID)textureID, ImVec2{ _viewportSize.x, _viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
                ImGui::End();
                ImGui::PopStyleVar();
            }

            ImGui::End();
        }
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
