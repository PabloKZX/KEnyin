#pragma once

#include <glm/glm.hpp>

namespace KEnyin
{
    class Mesh
    {
    public:
        using Vertex = glm::vec3;
        using UV = glm::vec2;
        using Triangle = int;
        using Normal = glm::vec3;

        Mesh();
        ~Mesh();

        std::string name;
        std::vector<Vertex> vertices;
        std::vector<UV> uvs;
        std::vector<Normal> normals;
        std::vector<Triangle> triangles;

        void refresh();
        void bind();

    private:
        unsigned int _vao;
        unsigned int _vbo;

        //TODO: delete
        friend class Renderer;
    };
}
