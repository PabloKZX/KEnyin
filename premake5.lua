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

-- Include directories relative to root folder (solution directory)
includeDirs = {}
includeDirs["glad"] = "KEnyin/vendor/glad/include"
includeDirs["glm"] = "KEnyin/vendor/glm"
includeDirs["GLFW"] = "KEnyin/vendor/GLFW/include"
includeDirs["ImGui"] = "KEnyin/vendor/ImGui"
includeDirs["stb_image"] = "KEnyin/vendor/stb_image"

include "KEnyin/vendor/GLFW"
include "KEnyin/vendor/glad"
include "KEnyin/vendor/ImGui"

project "KEnyin"
    location "KEnyin"
    kind "StaticLib"
    staticruntime "On"
    language "C++"
    cppdialect "c++latest"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

-- Precompiled headers for different actions
	filter "action:vs*"
		pchheader "pch.hpp"
		pchsource "KEnyin/src/pch.cpp"

	filter "action:xcode4"
	    pchheader "src/pch.hpp"
		pchsource "KEnyin/src/pch.cpp"

	filter {}

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",

        "%{includeDirs.stb_image}/**.h",
        "%{includeDirs.stb_image}/**.cpp",
        
        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{includeDirs.GLFW}",
        "%{includeDirs.glad}",
        "%{includeDirs.ImGui}",
        "%{includeDirs.glm}",
        "%{includeDirs.stb_image}",
    }

    filter "action:xcode4"
        sysincludedirs
        {
            "${PROJECT_DIR}/src",
            "${PROJECT_DIR}/vendor/spdlog/include",
            "${PROJECT_DIR}/vendor/GLFW/include",
            "${PROJECT_DIR}/vendor/Glad/include",
            "${PROJECT_DIR}/vendor/glm",
            "${PROJECT_DIR}/vendor/ImGui",
            "${PROJECT_DIR}/vendor/stb_image",
        }

    filter "system:macosx"
        links
        {
            "OpenGL.framework",
            "Cocoa.framework",
            "OpenGL.framework",
            "IOKit.framework",
            "CoreFoundation.framework",
            "QuartzCore.framework",
        }

    filter {}

    links
    {
        "GLFW",
        "opengl32.lib",
        "glad",
        "ImGui",
    }

    -- PLATFORM FILTERS

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "KE_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

    filter "system:macosx"
        staticruntime "On"
        systemversion "latest"
        buildoptions { "-std=c++11", "-lgdi32" }

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
        "%{includeDirs.glm}",
    }

    filter "action:xcode4"
        sysincludedirs
        {
            "${PROJECT_DIR} /../KEnyin/vendor/glm",
            "${PROJECT_DIR} /../KEnyin/vendor/spdlog/include",
            "${PROJECT_DIR} /../KEnyin/src"
        }

    filter {}

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

    filter "system:macosx"
        systemversion "latest"
        buildoptions { "-std=c++11", "-lgdi32" }

        defines
        {
            "HZ_PLATFORM_MACOS"
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
