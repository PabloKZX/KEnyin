project "KEditor"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"
    cppdialect "c++17"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.hpp",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "%{wks.location}/KEnyin/src",
        "%{wks.location}/KEnyin/vendor",
        "%{wks.location}/KEnyin/vendor/spdlog/include",
        "%{includeDirs.glm}",
        "%{includeDirs.entt}",
        "%{includeDirs.ImGui}",
    }
    
    links
    {
        "KEnyin",
        "ImGui",
    }

    filter "action:xcode4"
        sysincludedirs
        {
            "src",
            "%{wks.location}/KEnyin/src",
            "%{wks.location}/KEnyin/vendor/glm",
            "%{wks.location}/KEnyin/vendor/spdlog/include",
            "%{wks.location}/KEnyin/vendor/ImGui",
        }

    filter {}


    filter "system:windows"
        systemversion "latest"

        defines
        {
            "KE_PLATFORM_WINDOWS",
        }

    filter "system:macosx"
        systemversion "11.3"
        buildoptions "-std=c++17"

        defines
        {
            "KE_PLATFORM_MACOS"
        }

        links
        {
            "Cocoa.framework",
            "IOKit.framework",
            "CoreFoundation.framework"
        }

    filter "configurations:Debug"
        defines "KE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "KE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "KE_DIST"
        runtime "Release"
        optimize "on"
