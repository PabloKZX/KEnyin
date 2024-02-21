#include "KEnyin/AssetManagement/AssetManager.hpp"

#include "KEnyin/Rendering/Texture2D.hpp"
#include "KEnyin/Rendering/Shader.hpp"
#include <iostream>

namespace KEnyin
{
    template<>
    std::unique_ptr<Texture2D> AssetManager::LoadAsset<Texture2D>(const std::string& relativeAssetPath)
    {
        return std::make_unique<Texture2D>(getRootAssetsPath(relativeAssetPath));
    }

    template<>
    std::unique_ptr<Shader> AssetManager::LoadAsset<Shader>(const std::string& relativeAssetPath)
    {
        return std::make_unique<Shader>(getRootAssetsPath(relativeAssetPath));
    }

    std::string AssetManager::getAssetsPath()
    {
        //.../KEnyin/bin/Debug-platform-x86_64/KEditor/KEditor" -> .../KEnyin/KEnyinApp/Assets/...

        std::filesystem::path currentPath = std::filesystem::current_path();
        std::filesystem::path rootEnginePath = currentPath.parent_path().parent_path().parent_path();

        //TODO: KEnyinApp here is hardcoded, this should be the name of the project.
        return rootEnginePath / "KEnyinApp" / "Assets";
    }

    std::string AssetManager::getEditorAssetsPath()
    {
        //.../KEnyin/bin/Debug-platform-x86_64/KEditor/KEditor" -> .../KEnyin/KEditor/Assets/...

        std::filesystem::path currentPath = std::filesystem::current_path();
        std::filesystem::path rootEnginePath = currentPath.parent_path().parent_path().parent_path();
        return rootEnginePath / "KEditor" / "Assets";
    }

    std::string AssetManager::getRootAssetsPath(const std::string& relativeAssetPath)
    {
        return getAssetsPath() + "/" + relativeAssetPath;
    }
} // KEnyin