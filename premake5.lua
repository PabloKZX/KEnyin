workspace "KEnyin"
    architecture "x64"
    startproject "KEnyinApp"

    configurations
    {
        "Debug",
        "Release",
        "Dist",
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "KEnyin"
    location "KEnyin"
    kind "StaticLib"
    staticruntime "On"
    language "C++"
    cppdialect "c++latest"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.hpp"
    pchsource "KEnyin/src/pch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
    }

    -- PLATFORM FILTERS

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "KE_PLATFORM_WINDOWS",
        }

    filter "system:macosx"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "KE_PLATFORM_MACOS",
        }

    -- CONFIGURATION FILTERS

    filter "configurations:Debug"
        defines {"KE_DEBUG"}
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines {"KE_RELEASE"}
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines {"KE_DIST"}
        runtime "Release"
        optimize "On"


project "KEnyinApp"
    location "KEnyinApp"
    kind "ConsoleApp"
    language "C++"
    staticruntime "On"
    language "C++"
    cppdialect "c++latest"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "KEnyin/src",
        "KEnyin/vendor",
        "KEnyin/vendor/spdlog/include",
    }

    links
    {
        "KEnyin"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "KE_PLATFORM_WINDOWS",
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
