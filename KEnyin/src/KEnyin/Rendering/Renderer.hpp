#pragma once

#include "KEnyin/SceneManagement/Components/Components.hpp"
#include "KEnyin/Rendering/Camera.hpp"
#include "KEnyin/Rendering/Color.hpp"
#include <glm/glm.hpp>

namespace KEnyin
{
    class Renderer
    {
    public:
        using VLights = std::vector<Light*>;
        
        static void Init();
        static void Shutdown();

        static void BeginScene(Camera* camera, const VLights& lights);
        static void EndScene();

        static void DrawMesh(const glm::mat4& transform, const Components::MeshRenderer& meshComponent);
        static void SetClearColor(Color color);
        static void Clear();

    private:
        struct SceneData
        {
            glm::mat4 viewProjectionMatrix;
            glm::vec3 cameraPosition;
            VLights lights;
        };

        static std::unique_ptr<SceneData> _sceneData;
    };
}
