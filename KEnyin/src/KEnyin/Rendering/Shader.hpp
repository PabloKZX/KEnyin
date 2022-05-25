#pragma once

namespace KEnyin
{
    class Shader
    {
    public:
        Shader(const std::string& vertxPath, const std::string& fragmentPath);
        ~Shader();

        void bind();
        void unbind();

    private:
        unsigned int _rendererID;
    };
}

