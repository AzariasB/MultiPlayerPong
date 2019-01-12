-- Box2D premake5 script.
-- https://premake.github.io/

workspace 'Box2D'
	configurations { 'Release' }
	startproject 'Testbed'
	location 'Build'
	symbols 'On'
	warnings 'Extra'
    cppdialect 'C++11'

    filter 'system:linux'
        platforms { 'x86_64' }
    filter 'system:macosx'
        platforms { 'x86_64' }
    filter 'system:windows'
        platforms { 'x86', 'x86_64' }
        defaultplatform 'x86_64'
		defines { '_CRT_SECURE_NO_WARNINGS' }
	filter {}

	filter 'configurations:Release'
		defines { 'NDEBUG' }
		optimize 'On'
	filter {}

project 'Box2D'
	kind 'StaticLib'
	files { 'Box2D/**' }
	includedirs { '.' }