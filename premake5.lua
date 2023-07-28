workspace "Game"
   configurations { "Debug", "Release" }

project "cpp-scenegraph"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++11"
   links { "SDL2", "SDL2_mixer", "SDL2_image", "m", "GL"}
   targetdir "bin/%{cfg.buildcfg}"
   targetname ("main.bin")
   postbuildcommands "{COPYDIR} ./assets ./bin/%{cfg.buildcfg}"

   files { "src/**.h", "src/**.c", "src/**.cpp", "src/**.hpp"  }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

-- Clean Function --
newaction {
	trigger     = "clean",
	description = "clean the software",
	execute     = function ()
	print("clean the build...")
	os.rmdir("./bin/Debug")
	print("done.")
	end
}