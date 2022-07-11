workspace "KEnyin"
    architecture "x86_64"
    startproject "KEditor"

    configurations
    {
        "Debug",
        "Release",
        "Dist",
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
includeDirs = {}
includeDirs["entt"] = "%{wks.location}/KEnyin/vendor/entt/include"
includeDirs["glad"] = "%{wks.location}/KEnyin/vendor/glad/include"
includeDirs["glm"] = "%{wks.location}/KEnyin/vendor/glm"
includeDirs["GLFW"] = "%{wks.location}/KEnyin/vendor/GLFW/include"
includeDirs["ImGui"] = "%{wks.location}/KEnyin/vendor/ImGui"
includeDirs["stb_image"] = "%{wks.location}/KEnyin/vendor/stb_image"

group "Dependencies"
include "KEnyin/vendor/GLFW"
include "KEnyin/vendor/glad"
include "KEnyin/vendor/imgui"
group ""

include "KEnyin"
include "KEnyinApp"
include "KEditor"