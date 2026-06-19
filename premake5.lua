workspace "space-invaders"
    configurations { "Debug", "Release" }
    architecture "x86_64"

project "space-invaders"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin/obj/%{cfg.buildcfg}"

    files { "**.cpp", "**.hpp", "**.h" }

    includedirs { "src" }

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