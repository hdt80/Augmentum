-- Box2D premake5 script.
-- https://premake.github.io/

workspace "Box2D"
	location ( "build/%{_ACTION}" )
	architecture "x86_64"
	configurations { "debug", "release" }

	configuration "vs*"
		defines { "_CRT_SECURE_NO_WARNINGS" }	

	filter "configurations:debug"
		targetdir ( "build/%{_ACTION}/bin/debug" )
	 	defines { "DEBUG" }
		symbols "On"

	filter "configurations:delease"
		targetdir ( "build/%{_ACTION}/bin/release" )
		defines { "NDEBUG" }
		optimize "On"

	filter { "language:C++", "toolset:gcc" }
		buildoptions { "-std=c++11" }

project "Box2D"
	kind "StaticLib"
	language "C++"
	files { "Box2D/**.h", "Box2D/**.cpp" }
	includedirs { "." }
