cmake_minimum_required(VERSION 2.6)
project(phakman)

add_subdirectory(module/alligator/)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -g -ftest-coverage -fprofile-arcs")

file(GLOB_RECURSE CPPs src/**/*.cpp)
file(GLOB_RECURSE HPPs src/**/*.h)

include_directories(module/alligator/src)

if(WIN32)
	# i686-w64-mingw32-g++ -o phakman-w32.exe -static-libstdc++ -static-libgcc src/*/**.cpp --std=c++11 -lallegro-5.0.10-monolith-mt -lwinpthread
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/win32)
	list(APPEND CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")
	add_executable(phakman-w32 ${CPPs} ${HPPs} src/main.cpp)
	target_link_libraries(phakman-w32 allegro-5.0.10-monolith-mt)
elseif(UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/linux)
	add_executable(phakman ${CPPs} ${HPPs} src/main.cpp)
	include_directories(phakman ${ALLIGATOR_INCLUDES})
	target_link_libraries(phakman alligator)
	target_link_libraries(phakman allegro)
	target_link_libraries(phakman allegro_image)
	target_link_libraries(phakman allegro_primitives)
	target_link_libraries(phakman allegro_font)
	target_link_libraries(phakman allegro_ttf)
	target_link_libraries(phakman allegro_audio)
	target_link_libraries(phakman allegro_acodec)
endif()


