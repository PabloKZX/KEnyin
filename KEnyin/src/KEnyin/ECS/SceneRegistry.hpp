#pragma once

namespace KEnyin
{
    class Component;
}

namespace KEnyin
{
    enum class ComponentType
    {
        Camera,
        Renderer,
        CustomBehaviour,
    };
    
    class SceneRegistry
    {
    public:
        using MComponents = std::unordered_map<unsigned int, Component>;
        using Registry = std::unordered_map<ComponentType, MComponents>;

        template<typename T>
        std::vector<T> getCompontentsOfType(T type);
         
    private:
        Registry _registry;
    };
}
