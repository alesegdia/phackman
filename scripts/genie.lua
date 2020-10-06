AETHER_DIR = path.getabsolute("../module/aether")

dofile(path.join(AETHER_DIR, "scripts/util/util.lua"))

aetherConfig()

solution "phackman"
	startproject("phackman-game")
	location "../build/"
	configurations { "debug", "release" }
	platforms { "x32", "x64" }
	language "C++"
	
	aetherBuild()

	aetherProject("phackman-game")
		debugdir ("..")
		targetdir ("../build")
		files {
			"../src/**.cpp",
			"../src/**.h"
		}

