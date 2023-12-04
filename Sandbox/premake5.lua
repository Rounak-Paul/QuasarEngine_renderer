project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
		"QS_PLATFORM_WINDOWS",
	}

	includedirs
	{
		"%{wks.location}/QuasarEngine/vendor/spdlog/include",
		"%{wks.location}/QuasarEngine/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.VulkanSDK}",
	}

	links
	{
		"QuasarEngine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "QS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "QS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "QS_DIST"
		runtime "Release"
		optimize "on"
	
	
