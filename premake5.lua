include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "QuasarEngine"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
group ""

group "Core"
	include "QuasarEngine"
group ""

group "Misc"
	include "Sandbox"
group ""
