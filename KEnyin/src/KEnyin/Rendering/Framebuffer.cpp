#include "KEnyin/Rendering/Framebuffer.hpp"
#include <glad/glad.h>

namespace KEnyin
{
    Framebuffer::Framebuffer(const FramebufferData& data)
    : _data(data)
    {
        refresh();
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &_id);
        glDeleteTextures(1, &_colorBuffer);
        glDeleteTextures(1, &_depthBuffer);
    }

    void Framebuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _id);
        glViewport(0, 0, _data.width, _data.height);
    }

    void Framebuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::refresh()
    {
        if(_id)
        {
            glDeleteFramebuffers(1, &_id);
            glDeleteTextures(1, &_colorBuffer);
            glDeleteTextures(1, &_depthBuffer);
        }
        
        glGenFramebuffers(1, &_id);
        glBindFramebuffer(GL_FRAMEBUFFER, _id);
        
        // Color attachement
        glGenTextures(1, &_colorBuffer);
        glBindTexture(GL_TEXTURE_2D, _colorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _data.width, _data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorBuffer, 0);
        
        // Depth - stencil attachement
        glGenTextures(1, &_depthBuffer);
        glBindTexture(GL_TEXTURE_2D, _depthBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _data.width, _data.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depthBuffer, 0);
        
        KECheck_Engine(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::resize(unsigned int width, unsigned int height)
    {
        _data.width = width;
        _data.height = height;
        
        refresh();
    }
}
