cmake_minimum_required(VERSION 2.6)
project(phakman)

add_subdirectory(module/alligator/)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -g -ftest-coverage -fprofile-arcs")

file(GLOB_RECURSE CPPs src/**/*.cpp)
file(GLOB_RECURSE HPPs src/**/*.h)
file(GLOB_RECURSE SECS module/secs/src/lib/**/*.h module/secs/src/lib/**/*.cpp)

include_directories(module/alligator/src)
include_directories(module/secs/src/lib)

set(SOURCES ${CPPs} ${HPPs} ${SECS})

# add a new target with allegro, alligator and core sources. uses monolith for win32
function(add_alleg_target EXEC-NAME SRCS)
	add_executable(${EXEC-NAME} ${SOURCES} ${SRCS})
	target_link_libraries(${EXEC-NAME} alligator)
	target_include_directories(${EXEC-NAME} PUBLIC module/enet/include)
	target_include_directories(${EXEC-NAME} PUBLIC module/alligator/src)
	set_target_properties(${EXEC-NAME} PROPERTIES
		COMPILE_FLAGS "-std=c++11"
		LINK_FLAGS "-g -ftest-coverage -fprofile-arcs"
		)
	if(WIN32)
		target_link_libraries(${EXEC-NAME} allegro_monolith)
	elseif(UNIX)
		target_link_libraries(${EXEC-NAME} allegro)
		target_link_libraries(${EXEC-NAME} allegro_image)
		target_link_libraries(${EXEC-NAME} allegro_primitives)
		target_link_libraries(${EXEC-NAME} allegro_font)
		target_link_libraries(${EXEC-NAME} allegro_ttf)
		target_link_libraries(${EXEC-NAME} allegro_audio)
		target_link_libraries(${EXEC-NAME} allegro_acodec)
	else()
		message(SEND_FATAL "Unknown platform")
	endif()
endfunction(add_alleg_target)

add_alleg_target(game src/main.cpp)
