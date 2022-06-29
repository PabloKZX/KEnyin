#pragma once

#include "KEnyin/SceneManagement/Components/Components.hpp"
#include "KEnyin/Rendering/Camera.hpp"
#include <glm/glm.hpp>

namespace KEnyin
{
    class Renderer
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(Camera* camera);
        static void EndScene();

        static void DrawMesh(const glm::mat4& transform, const Components::MeshRenderer& meshComponent);

    private:
        struct SceneData
        {
            glm::mat4 viewProjectionMatrix;
        };

        static std::unique_ptr<SceneData> _sceneData;
    };
}
