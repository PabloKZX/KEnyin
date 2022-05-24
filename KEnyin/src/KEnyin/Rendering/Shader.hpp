#pragma once

namespace KEnyin
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();

        void bind();
        void unbind();

    private:
        unsigned int _rendererID;
    };
}

