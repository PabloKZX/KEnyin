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
        float vertexData[180];

        for (size_t i = 0, vertexIndex = 0; vertexIndex < 36; i+=5, vertexIndex++)
        {
            vertexData[i]   = vertices[vertexIndex].x;
            vertexData[i+1] = vertices[vertexIndex].y;
            vertexData[i+2] = vertices[vertexIndex].z;

            vertexData[i+3] = uvs[vertexIndex].x;
            vertexData[i+4] = uvs[vertexIndex].y;
        }

        glBindVertexArray(_vao);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

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