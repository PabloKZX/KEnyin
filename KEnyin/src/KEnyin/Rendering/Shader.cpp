#include "pch.hpp"
#include "KEnyin/Rendering/Shader.hpp"
#include <glad/glad.h>

namespace KEnyin
{
    Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
    {
        // Create vertex shader
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Compile vertex shader
        const GLchar* source = vertexSource.c_str();
        glShaderSource(vertexShader, 1, &source, nullptr);
        glCompileShader(vertexShader);

        // Check if shader compiled successfully
        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertexShader);

            KEError_Engine("{0}", infoLog.data());
            KECheck_Engine(isCompiled == GL_FALSE, "Vertex shader compilation failed!");
            return;
        }
        
        // Create fragment shader
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Compile fragment shader
        source = fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &source, nullptr);
        glCompileShader(fragmentShader);

        // Check if shader compiled successfully
        isCompiled = 0;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            KEError_Engine("{0}", infoLog.data());
            KECheck_Engine(isCompiled == GL_FALSE, "Fragment shader compilation failed!");
            return;
        }

        // Create program
        _rendererID = glCreateProgram();

        // Link shaders to program
        glAttachShader(_rendererID, vertexShader);
        glAttachShader(_rendererID, fragmentShader);
        glLinkProgram(_rendererID);

        // Check if program is linked successfully
        GLint isLinked = 0;
        glGetProgramiv(_rendererID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(_rendererID);

            KEError_Engine("{0}", infoLog.data());
            KECheck_Engine(isCompiled == GL_FALSE, "Program linking failed!");
            return;
        }

        // Once linked shaders are no longer necessary
        glDetachShader(_rendererID, vertexShader);
        glDetachShader(_rendererID, fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(_rendererID);
    }

    void Shader::bind()
    {
        glUseProgram(_rendererID);
    }

    void Shader::unbind()
    {
        glUseProgram(0);
    }
}
