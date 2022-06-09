#include "pch.hpp"
#include "KEnyin/Rendering/Texture2D.hpp"

#include <glad/glad.h>
#include <stb_image.h>

namespace KEnyin
{
    Texture2D::Texture2D(const std::string& filePath)
    {
        // load texture
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

        KECheck_Engine(data, "Texture data could not be loaded from file {0}", filePath);

        _width = width;
        _height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        if (nrChannels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (nrChannels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        KECheck_Engine(internalFormat & dataFormat, "Format not supported!");

        // create texture
        glGenTextures(1, &_textureId);
        glBindTexture(GL_TEXTURE_2D, _textureId);

        // set the texture wrapping/filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // generate texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &_textureId);
    }

    void Texture2D::bind(unsigned int textureUnit)
    {
        glActiveTexture(textureUnit);
        glBindTexture(GL_TEXTURE_2D, _textureId);
    }

}
