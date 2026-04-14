workspace "space-invaders"
    configurations { "Debug", "Release" }
    architecture "x86_64"

project "arkanoid"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin/obj/%{cfg.buildcfg}"

    files { "**.cpp", "**.hpp", "**.h" }

    includedirs { "." }

    links { "raylib" }

    filter "system:macosx"
        links {
            "IOKit.framework",
            "Cocoa.framework",
            "OpenGL.framework"
        }

    filter "system:linux"
        links { "m", "pthread", "dl" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"