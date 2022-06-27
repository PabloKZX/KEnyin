#pragma once

#include "KEnyin/SceneManagement/Components.hpp"
#include <glm/glm.hpp>

namespace KEnyin
{
    class Renderer
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene();
        static void EndScene();

        static void DrawMesh(const glm::mat4& transform, const MeshRendererComponent& meshComponent);

    //private:
    //    unsigned int _vao;
    //    unsigned int _vbo;
    //    std::shared_ptr<Material> _material;
    //    std::shared_ptr<Mesh> _mesh;
    };
}
