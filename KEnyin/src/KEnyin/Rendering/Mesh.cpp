#include "pch.hpp"
#include "KEnyin/Rendering/Mesh.hpp"
#include <glad/glad.h>

namespace KEnyin
{
    Mesh::Mesh()
    {
        glGenVertexArrays(1, &_vao);
        glGenBuffers(1, &_vbo);
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vbo);
    }

    void Mesh::refresh()
    {
        std::vector<float> vertexData;
        vertexData.reserve(vertices.size() * 3 + uvs.size() * 2);

        for (size_t i = 0; i < vertices.size(); i++)
        {
            vertexData.push_back(vertices[i].x);
            vertexData.push_back(vertices[i].y);
            vertexData.push_back(vertices[i].z);

            vertexData.push_back(uvs[i].x);
            vertexData.push_back(uvs[i].y);
        }

        glBindVertexArray(_vao);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        // uvs attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    void Mesh::bind()
    {
        glBindVertexArray(_vao);
    }
}