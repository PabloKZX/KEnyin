#pragma once

namespace KEnyin
{
    struct FramebufferData
    {
        unsigned int width;
        unsigned int height;
        unsigned int samples;
    };

    class Framebuffer
    {
    public:
        using Data = FramebufferData;
        
        Framebuffer(const FramebufferData& data);
        ~Framebuffer();
        
        void bind();
        void unbind();
        void refresh();
        void resize(unsigned int width, unsigned int height);
        
        inline unsigned int getColorBufferId() const { return _colorBuffer; };
        const Data& getData() const { return _data; };
    private:
        Data _data;
        
        unsigned int _id;
        unsigned int _colorBuffer;
        unsigned int _depthBuffer;
    };
}
