#pragma once

#include "KEnyin/Rendering/Color.hpp"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace KEnyin
{
    class Shader
    {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        Shader(const std::string& shaderPath);
        ~Shader();

        void bind();
        void unbind();

        void  setFloat(const char* name, float value);
        void  setInt(const char* name, int value);
        void  setVector2f(const char* name, float x, float y);
        void  setVector2f(const char* name, const glm::vec2& value);
        void  setVector3f(const char* name, float x, float y, float z);
        void  setVector3f(const char* name, const glm::vec3& value);
        void  setVector4f(const char* name, float x, float y, float z, float w);
        void  setVector4f(const char* name, const glm::vec4& value);
        void  setColor3f(const char* name, const Color& color);
        void  setColor4f(const char* name, const Color& color);
        void  setMatrix4(const char* name, const glm::mat4& matrix);

    private:
        std::string readFile(const std::string& filePath);
        std::unordered_map<GLenum, std::string> getShaderSources(const std::string& source);
        unsigned int compileShader(const std::string& source, GLenum shaderType);
        unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader);

        unsigned int _shaderID;
    };
}

