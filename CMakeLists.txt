cmake_minimum_required(VERSION 2.6)
project(phakman)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(module/alligator)

if(NOT MSVC)
    find_package(Allegro REQUIRED)
    if(NOT ALLEGRO_FOUND)
        message(FATAL_ERROR "NO ALLEGRO DETECTED!")
    else()
        message("ALLEGRO INCLUDE: ${ALLEGRO_INCLUDE_DIR}")
    endif(NOT ALLEGRO_FOUND)
endif()


file(GLOB_RECURSE PHACKMAN_SOURCES src/**/*.cpp src/**/*.h)
file(GLOB_RECURSE SECS_SOURCES module/secs/src/lib/**/*.h module/secs/src/lib/**/*.cpp)
file(GLOB_RECURSE HADRON_SOURCES module/hadron/src/lib/**/*.h module/hadron/src/lib/**/*.cpp)

source_group(secs FILES ${SECS_SOURCES})
source_group(game FILES ${PHACKMAN_SOURCES})
source_group(hadron FILES ${HADRON_SOURCES})

# add a new target with allegro, alligator and core sources. uses monolith for win32
function(add_alleg_target EXEC-NAME SRCS)
	add_executable(${EXEC-NAME} ${PHACKMAN_SOURCES} ${SECS_SOURCES} ${HADRON_SOURCES} ${SRCS})
	target_link_libraries(${EXEC-NAME} alligator)

        target_include_directories(${EXEC-NAME} PUBLIC module/alligator/src)
	target_include_directories(${EXEC-NAME} PUBLIC module/hadron/src/lib/)
        target_include_directories(${EXEC-NAME} PUBLIC module/secs/src/lib)

        message("DENTRO: ${ALLEGRO_INCLUDE_DIR}")
        target_include_directories(${EXEC-NAME} PUBLIC "${ALLEGRO_INCLUDE_DIR}")
        include_directories("${ALLEGRO_INCLUDE_DIR}")

        if(NOT MSVC)
                target_include_directories(${EXEC-NAME} PUBLIC "${ALLEGRO_INCLUDE_DIR}")
                set_target_properties(${EXEC-NAME} PROPERTIES
                        COMPILE_FLAGS "-g -std=gnu++11  -Wall -Wextra"
                        LINK_FLAGS "-g -ftest-coverage -fprofile-arcs"
			)
                target_link_libraries(${EXEC-NAME} ${ALLEGRO_LIBRARIES})
	endif()
endfunction(add_alleg_target)

add_alleg_target(phackman src/main.cpp)

