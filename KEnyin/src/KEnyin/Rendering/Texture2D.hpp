#pragma once

namespace KEnyin
{
    class Texture2D
    {
    public:
        Texture2D(unsigned int width, unsigned int height);
        Texture2D(const std::string& filePath);
        ~Texture2D();

        void bind(unsigned int textureUnit= 0);
    private:
        unsigned int _textureId;
        unsigned int _width;
        unsigned int _height;
    };
}
