cmake_minimum_required(VERSION 2.6)
project(phakman)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(module/alligator)
add_subdirectory(module/hadron)

if(NOT MSVC)
	find_package(Allegro REQUIRED)
endif()

file(GLOB_RECURSE PHACKMAN_SOURCES src/**/*.cpp src/**/*.h)
file(GLOB_RECURSE SECS_SOURCES module/secs/src/lib/**/*.h module/secs/src/lib/**/*.cpp)

source_group(secs FILES ${SECS_SOURCES})
source_group(game FILES ${PHACKMAN_SOURCES})

include_directories(module/alligator/src)
include_directories(module/secs/src/lib)

# add a new target with allegro, alligator and core sources. uses monolith for win32
function(add_alleg_target EXEC-NAME SRCS)
	add_executable(${EXEC-NAME} ${PHACKMAN_SOURCES} ${SECS_SOURCES} ${SRCS})
        target_link_libraries(${EXEC-NAME} alligator)
        target_link_libraries(${EXEC-NAME} hadron)
        target_include_directories(${EXEC-NAME} PUBLIC module/alligator/src)

	if(NOT MSVC)
	target_include_directories(${EXEC-NAME} PUBLIC ${ALLEGRO_INCLUDE_DIR})
	set_target_properties(${EXEC-NAME} PROPERTIES
		COMPILE_FLAGS "-std=c++11"
		LINK_FLAGS "-g -ftest-coverage -fprofile-arcs"
		)
	target_link_libraries(${EXEC-NAME} ${ALLEGRO_LIBRARIES})
	endif()
endfunction(add_alleg_target)

add_alleg_target(phackman src/main.cpp)
