#pragma once

namespace KEnyin
{
    class AssetManager
    {
    public:
        template<typename T>
        static std::unique_ptr<T> LoadAsset(const std::string& relativeAssetPath);
        static std::string getAssetsPath();
        static std::string getEditorAssetsPath();
    private:
        inline static std::string getRootAssetsPath(const std::string& relativeAssetPath);
    };

} // KEnyin

