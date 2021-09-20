workspace "Keg"
    architecture "x86_64"
    startproject "Sandbox"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Keg"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Keg/src/**.h",
        "Keg/src/**.cpp"
    }

    includedirs
    {
        "Keg/Vendor/spdlog/include",
        "Keg/Vendor/glad/include",
        "Keg/Vendor/glfw/include",
    }

project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

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
    }

    links
    {
        "Keg",
        "GLAD",
        "GLFW",
        "opengl32.lib",
    }

group "Dependencies"
	include "Keg/Vendor/GLFW"
    include "Keg/Vendor/glad"
group ""