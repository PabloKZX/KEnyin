#include "pch.hpp"
#include "KEnyin/Rendering/Shader.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace KEnyin
{
    namespace shader_utils
    {
        static GLenum shaderTypeFromString(const std::string& type)
        {
            if (type == "vertex")
            {
                return GL_VERTEX_SHADER;
            }
            if (type == "fragment" || type == "pixel")
            {
                return GL_FRAGMENT_SHADER;
            }

            KECheck_Engine(false, "Unknown shader type!");
            return 0;
        }

        static const std::string& shaderTypeToString(GLenum type)
        {
            switch (type)
            {
                case GL_VERTEX_SHADER:
                {
                    return "GL_VERTEX_SHADER";
                }
                case GL_FRAGMENT_SHADER:
                {
                    return "GL_FRAGMENT_SHADER";
                }

            }

            return "";
        }
    }

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        // 1.Retrieve the source code from the files
        std::string vertexSource = readFile(vertexPath);
        std::string fragmentSource = readFile(fragmentPath);

        // 2. Compile shaders
        unsigned int vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
        unsigned int fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

        // 3. Create program
        _shaderID = createProgram(vertexShader, fragmentShader);

        // 4. Once linked, shaders are no longer necessary
        glDetachShader(_shaderID, vertexShader);
        glDetachShader(_shaderID, fragmentShader);
    }

    Shader::Shader(const std::string& shaderPath)
    {
        // 1.Retrieve the source code from the files
        const std::string& fileSource = readFile(shaderPath);
        auto shaderSources = getShaderSources(fileSource);

        // 2. Compile shaders
        unsigned int vertexShader = compileShader(shaderSources[GL_VERTEX_SHADER], GL_VERTEX_SHADER);
        unsigned int fragmentShader = compileShader(shaderSources[GL_FRAGMENT_SHADER], GL_FRAGMENT_SHADER);

        // 3. Create program
        _shaderID = createProgram(vertexShader, fragmentShader);

        // 4. Once linked, shaders are no longer necessary
        glDetachShader(_shaderID, vertexShader);
        glDetachShader(_shaderID, fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(_shaderID);
    }

    void Shader::bind()
    {
        glUseProgram(_shaderID);
    }

    void Shader::unbind()
    {
        glUseProgram(0);
    }

    std::string Shader::readFile(const std::string& filePath)
    {
        std::string result;
        std::ifstream file;

        // Ensure ifstream objects can throw exceptions
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            // Open files
            file.open(filePath);

            // Read files contents 
            std::stringstream fileStream;
            fileStream << file.rdbuf();

            // Close files
            file.close();

            // Convert streams into strings
            result = fileStream.str();
        }
        catch (std::ifstream::failure e)
        {
            KEError_Engine("Shader file read failed!");
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> Shader::getShaderSources(const std::string& source)
    {
        std::unordered_map<GLenum, std::string> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0); //Start of shader type declaration line

        while (pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos); //get first end of line
            KECheck_Engine(eol != std::string::npos, "Syntax error");

            // get type
            size_t begin = pos + typeTokenLength + 1; // start of shader type name (after "#type " keyword)
            std::string type = source.substr(begin, eol - begin);
            KECheck_Engine(shader_utils::shaderTypeFromString(type), "Invalid shader type specified");

            // get source after type declaration line
            size_t nextLinePos = source.find_first_not_of("\r\n", eol); // next line of type declaration
            KECheck_Engine(nextLinePos != std::string::npos, "Syntax error");

            // get next type declaration
            pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

            // substring from current type declaration to next type declaration
            shaderSources[shader_utils::shaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);;
        }

        return shaderSources;
    }

    unsigned int Shader::compileShader(const std::string& source, GLenum shaderType)
    {
        // Create shader
        unsigned int shader;
        shader = glCreateShader(shaderType);

        // Compile shader
        const GLchar* glSource = source.c_str();
        glShaderSource(shader, 1, &glSource, nullptr);
        glCompileShader(shader);

        // Check if shader compiled successfully
        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shader);

            KEError_Engine("{0}", infoLog.data());
            KECheck_Engine(isCompiled == GL_FALSE, "{0} shader compilation failed!", shader_utils::shaderTypeToString(shaderType));
            return -1;
        }

        return shader;
    }

    unsigned int Shader::createProgram(unsigned int vertexShader, unsigned int fragmentShader)
    {
        unsigned int program = glCreateProgram();

        // Link shaders to program
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        // Check if program is linked successfully
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(program);

            KEError_Engine("{0}", infoLog.data());
            KECheck_Engine(isLinked == GL_FALSE, "Program linking failed!");
            return -1;
        }

        return program;
    }

    void Shader::setFloat(const char* name, float value)
    {
        glUniform1f(glGetUniformLocation(_shaderID, name), value);
    }

    void Shader::setInt(const char* name, int value)
    {
        glUniform1i(glGetUniformLocation(_shaderID, name), value);
    }

    void Shader::setVector2f(const char* name, float x, float y)
    {
        glUniform2f(glGetUniformLocation(_shaderID, name), x, y);
    }

    void Shader::setVector2f(const char* name, const glm::vec2& value)
    {
        glUniform2f(glGetUniformLocation(_shaderID, name), value.x, value.y);
    }

    void Shader::setVector3f(const char* name, float x, float y, float z)
    {
        glUniform3f(glGetUniformLocation(_shaderID, name), x, y, z);
    }

    void Shader::setVector3f(const char* name, const glm::vec3& value)
    {
        glUniform3f(glGetUniformLocation(_shaderID, name), value.x, value.y, value.z);
    }

    void Shader::setColor3f(const char* name, const Color& color)
    {
        setVector3f(name, color.r, color.g, color.b);
    }

    void Shader::setColor4f(const char* name, const Color& color)
    {
        setVector4f(name, color.r, color.g, color.b, color.a);
    }


    void Shader::setVector4f(const char* name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(_shaderID, name), x, y, z, w);
    }

    void Shader::setVector4f(const char* name, const glm::vec4& value)
    {
        glUniform4f(glGetUniformLocation(_shaderID, name), value.x, value.y, value.z, value.w);
    }

    void Shader::setMatrix4(const char* name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(_shaderID, name), 1, false, glm::value_ptr(matrix));
    }

}
