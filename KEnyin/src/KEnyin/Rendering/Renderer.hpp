#pragma once

#include "KEnyin/Rendering/Texture2D.hpp"
#include "KEnyin/Rendering/Shader.hpp"
#include <glm/glm.hpp>

namespace KEnyin
{
    class Renderer
    {
    public:
        void Init();
        void Shutdown();

        void BeginScene();
        void EndScene();

    private:
        std::unique_ptr<Shader> _shader;

        unsigned int _vertexArray;
        unsigned int _vertexBuffer;
        unsigned int _indexBuffer;

        std::unique_ptr<Texture2D> _texture;
        std::unique_ptr<Texture2D> _texture2;

        std::vector<glm::vec3> _cubePositions;
        // Primitives
    };
}
