workspace "plutonium-sdk-example"
    -- set build location
    location "build"
    targetdir "%{wks.location}/bin/%{cfg.buildcfg:lower()}"

    -- specify configurations and platforms
    configurations {
        "Debug",
        "Release"
    }

    platforms {
        "Win32"
    }

    -- set good defaults for a few common options
    symbols "On"
    editandcontinue "Off"
    warnings "Extra"
    buildoptions {
        "/std:c++latest"
    }

    flags {
        "MultiProcessorCompile",
        "NoIncrementalLink"
    }

    -- enable static runtime
    -- this means no separate C++ runtime has to be installed on the machine executing the code
    staticruntime "On"
    system "windows"
    systemversion "latest"

    defines {
        "_WINDOWS",
        "WIN32"
    }

    -- set configuration-specific options
    filter "configurations:Debug"
        optimize "Debug"

        defines {
            "DEBUG",
            "_DEBUG"
        }
    filter "configurations:Release"
        optimize "Full"

        defines {
            "NDEBUG"
        }

        flags {
            "FatalCompileWarnings"
        }
    filter {}

    -- set system architecture (only x86 is supported)
    architecture "x86"

    -- the plugin project itself
    project "plugin"
        kind "SharedLib"
        language "C++"

        files {
            "src/**.cpp",
            "src/**.hpp"
        }

        includedirs {
            "src",
            "vendor/plutonium-sdk" -- plutonium sdk headers from git submodule
        }

        pchheader "std_include.hpp"
        pchsource "src/std_include.cpp"
