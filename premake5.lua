workspace "QuasarEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "QuasarEngine"
	location "QuasarEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "c++20"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"QS_PLATFORM_WINDOWS",
			"QS_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "QS_DEBUG"
		symbols "On"

	filter "configurations:Debug"
		defines "QS_RELEASE"
		symbols "On"

	filter "configurations:Debug"
		defines "QS_DIST"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"QuasarEngine/vendor/spdlog/include",
		"QuasarEngine/src"
	}

	links 
	{
		"QuasarEngine"
	}

	filter "system:windows"
		cppdialect "c++20"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"QS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "QS_DEBUG"
		symbols "On"

	filter "configurations:Debug"
		defines "QS_RELEASE"
		symbols "On"

	filter "configurations:Debug"
		defines "QS_DIST"
		symbols "On"