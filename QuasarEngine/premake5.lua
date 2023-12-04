project "QuasarEngine"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "qspch.h"
	pchsource "src/qspch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",

		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
	}

	defines
	{
		"QS_BUILD_DLL"
		
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.glm}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.GLFW}",
	}

	links
	{
		"%{Library.Vulkan}",
		"%{Library.GLFW}",
	}

	libdirs
	{
		"%{LibraryDir.VulkanSDK}",
		"%{LibraryDir.GLFWSDK}",
	}

	SHADER_TARGET = "%{wks.location}bin/" .. outputdir .. "/Sandbox/Shader"

	prebuildcommands 
	{
		(SHADER_COMPILER_SCRIPT .. " " .. VULKAN_SDK .. " " .. SHADER_TARGET)
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"QS_PLATFORM_WINDOWS",
		}

		links
		{
			
		}

	filter "configurations:Debug"
		defines "QS_DEBUG"
		runtime "Debug"
		symbols "on"

		links
		{
			
		}

	filter "configurations:Release"
		defines "QS_RELEASE"
		runtime "Release"
		optimize "on"

		links
		{
			
		}

	filter "configurations:Dist"
		defines "QS_DIST"
		runtime "Release"
		optimize "on"

		links
		{
			
		}
