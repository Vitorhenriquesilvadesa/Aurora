workspace "Aurora"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "AuroraCore"
	location "AuroraCore"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	cppdialect "C++20"
	staticruntime "On"

	filter "configurations:Debug"
		defines "AUR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AUR_RELEASE"
		optimize "On"

project "AuroraVM"
	location "AuroraVM"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"AuroraCore/src"
	}

	links
	{
		"AuroraCore"
	}

	cppdialect "C++20"
	staticruntime "On"

    postbuildcommands
    {
        ("{COPY}\"%{cfg.buildtarget.relpath}\" \"../bin/" .. outputdir .. "/Aurora/\"")
    }

	defines
	{
		"AURORA_EXPORTS"
	}

	filter "configurations:Debug"
		defines "AUR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AUR_RELEASE"
		optimize "On"

project "AuroraCompiler"
	location "AuroraCompiler"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"AuroraCore/src"
	}

	links
	{
		"AuroraCore"
	}

	cppdialect "C++20"
	staticruntime "On"

    postbuildcommands
    {
        ("{COPY}\"%{cfg.buildtarget.relpath}\" \"../bin/" .. outputdir .. "/Aurora/\"")
    }

	defines
	{
		"AURORA_EXPORTS"
	}

	filter "configurations:Debug"
		defines "AUR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AUR_RELEASE"
		optimize "On"

project "Aurora"
	location "Aurora"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"AuroraCompiler/src",
		"AuroraVM/src",
		"AuroraCore/src"
	}

	links
	{
		"AuroraCompiler",
		"AuroraVM",
		"AuroraCore"
	}

	cppdialect "C++20"
	staticruntime "On"

    postbuildcommands
    {
        ("{COPY}\"%{cfg.buildtarget.relpath}\" \"../bin/" .. outputdir .. "/Aurora/\"")
    }

	defines
	{
		"AURORA_EXPORTS"
	}

	filter "configurations:Debug"
		defines "AUR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AUR_RELEASE"
		optimize "On"
