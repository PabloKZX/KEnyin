#pragma once

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

    private:
        std::string readFile(const std::string& filePath);
        std::unordered_map<GLenum, std::string> getShaderSources(const std::string& source);
        unsigned int compileShader(const std::string& source, GLenum shaderType);
        unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader);

        unsigned int _rendererID;
    };
}

