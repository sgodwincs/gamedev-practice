---- Workspace: Game ----

workspace("Game")
configurations({
    "Debug32",
    "Release32",
    "Debug64",
    "Release64"
})
platforms({
    "Windows"
})

characterset("Unicode")
language("C++")
location("generated")
targetdir("build/bin/%{prj.name}/%{cfg.platform}/%{cfg.buildcfg}")
objdir("build/obj/%{prj.name}/%{cfg.platform}/%{cfg.buildcfg}")

filter("configurations:Debug*")
defines("PRJ_DEBUG")
symbols("On")

filter("configurations:Release*")
defines({
    "PRJ_RELEASE",
    "NDEBUG"
})
flags("LinkTimeOptimization")
optimize("On")

filter("configurations:*32")
defines("PRJ_X86")
architecture("x86")

filter("configurations:*64")
defines("PRJ_X86_64")
architecture("x86_64")

filter("platforms:Windows")
defines("PRJ_WINDOWS")
system("windows")

filter({})

---- Project: Game ----

-- Settings

project("Game")
kind("ConsoleApp")

debugdir("projects/game")

includedirs("projects/game/header")
files("projects/game/source/**.cpp")

pchheader("pch.hpp")
pchsource("projects/game/source/pch.cpp")

-- Configurations/Flags

flags("C++14")

filter("platforms:Windows")
buildoptions("/std:c++latest")
forceincludes("pch.hpp")

filter({})

-- Dependencies

includedirs("../dependencies/anax/include")
libdirs("../dependencies/anax/lib")
links("anax_d")

includedirs("../dependencies/SFML/include")
libdirs("../dependencies/SFML/lib")
links({
    "sfml-audio-d",
    "sfml-graphics-d",
    "sfml-network-d",
    "sfml-system-d",
    "sfml-window-d"
})
