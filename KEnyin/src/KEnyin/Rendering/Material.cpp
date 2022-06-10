#include "pch.hpp"
#include "KEnyin/Rendering/Material.hpp"
#include "KEnyin/Rendering/Shader.hpp"

namespace KEnyin
{
    Material::Material()
    : _shader(Shader("D:/Dev/KEnyin/KEnyin/src/KEnyin/Shaders/Sample.vs", "D:/Dev/KEnyin/KEnyin/src/KEnyin/Shaders/Sample.fs"))
    , _color(Color())
    {

    }

    Material::Material(const Shader& shader)
    : _shader(shader)
    , _color(Color())
    {

    }

    Material::Material(const Shader& shader, const Color& color)
    : _shader(shader)
    , _color(color)
    {

    }

    Material::~Material()
    {
    }
}
