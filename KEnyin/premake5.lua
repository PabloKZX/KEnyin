project "KEnyin"
    kind "StaticLib"
    staticruntime "off"
    language "C++"
    cppdialect "c++17"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

-- Precompiled headers for different actions
	filter "action:vs*"
		pchheader "pch.hpp"
		pchsource "src/pch.cpp"

	filter "action:xcode4"
	    pchheader "src/pch.hpp"
		pchsource "src/pch.cpp"

	filter {}

    files
    {
        "src/**.h",
        "src/**.hpp",
        "src/**.cpp",
        "vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "src",
        "vendor/spdlog/include",
        "%{includeDirs.GLFW}",
        "%{includeDirs.glad}",
        "%{includeDirs.ImGui}",
        "%{includeDirs.glm}",
        "%{includeDirs.stb_image}",
        "%{includeDirs.entt}",
    }

    links
    {
        "GLFW",
        "glad",
        "ImGui",
    }

    filter "action:xcode4"
        sysincludedirs
        {
            "src",
            "vendor/spdlog/include",
            "vendor/GLFW/include",
            "vendor/Glad/include",
            "vendor/glm",
            "vendor/ImGui",
            "vendor/stb_image",
            "vendor/entt/include",
        }

    filter "system:macosx"
        links
        {
            "Cocoa.framework",
            "IOKit.framework",
            "CoreFoundation.framework",
            "OpenGL.framework",
        }

    filter {}

    -- PLATFORM FILTERS

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "KE_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

    filter "system:macosx"
        staticruntime "On"
        systemversion "11.3"
        buildoptions "-std=c++17"

        defines
        {
            "KE_PLATFORM_MACOS",
            "GLFW_INCLUDE_NONE",
            "__APPLE__"
        }

    -- CONFIGURATION FILTERS

    filter "configurations:Debug"
        defines {"KE_DEBUG"}
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines {"KE_RELEASE"}
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines {"KE_DIST"}
        runtime "Release"
        optimize "on"
