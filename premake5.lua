workspace "Keg"
    architecture "x86_64"
    startproject "Sandbox"
    configurations { "Debug", "Release", "Distribution" }
    linkoptions { "/NODEFAULTLIB:msvcrt.lib", "/NODEFAULTLIB:libcmtd.lib" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
assetdir = "%{wks.location}/bin/" .. outputdir .. "/assets"

project "Keg"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    defines { "GLFW_INCLUDE_NONE", 'KEG_ASSETS="%{assetdir}"'}

    postbuildcommands
    {
        "{COPY} %{prj.name}/assets %{assetdir}"
    }

    files
    {
        "Keg/src/**.h",
        "Keg/src/**.cpp",
    }

    includedirs
    {
        "Keg/Vendor/spdlog/include",
        "Keg/Vendor/glad/include",
        "Keg/Vendor/glfw/include",
        "Keg/Vendor/glm/include",
        "Keg/Vendor/stb_image", 
        "Keg/Vendor/imgui", 
        "Keg/Vendor/entt",
        "Keg/src"
    }

    links
    {
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib",
    }

    filter "configurations:Debug"
		defines "KEG_DEBUG"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		defines "KEG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "KEG_DISTRIBUTION"
		runtime "Release"
		optimize "on"



project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    defines { 'KEG_ASSETS="%{assetdir}"' }

    files
    {
        "Sandbox/src/**.h",
        "Sandbox/src/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/Keg/src",
        "%{wks.location}/Keg/Vendor/spdlog/include",
        "%{wks.location}/Keg/Vendor/glfw/include",
        "%{wks.location}/Keg/Vendor/glad/include",
        "%{wks.location}/Keg/Vendor/glm/include",
        "%{wks.location}/Keg/Vendor/stb_image",
        "%{wks.location}/Keg/Vendor/imgui",
    }

    links
    {
        "Keg",
    }

    
    filter "configurations:Debug"
		defines "KEG_DEBUG"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		defines "KEG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "KEG_DISTRIBUTION"
		runtime "Release"
		optimize "on"


group "Dependencies"
	include "Keg/Vendor/GLFW"
    include "Keg/Vendor/glad"
    include "Keg/Vendor/imgui"
group ""