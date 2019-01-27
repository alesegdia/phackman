cmake_minimum_required(VERSION 2.6)
project(phakman)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(module/aether)
add_subdirectory(module/secs)

include("module/aether/cmake/Build.cmake")

file(GLOB_RECURSE PHACKMAN_SOURCES src/**/*.cpp src/**/*.h)
file(GLOB_RECURSE HADRON_SOURCES module/hadron/src/lib/**/*.h module/hadron/src/lib/**/*.cpp)

source_group(game FILES ${PHACKMAN_SOURCES})
source_group(hadron FILES ${HADRON_SOURCES})

set(ALL_SOURCES ${PHACKMAN_SOURCES} ${HADRON_SOURCES} src/main.cpp)

ADD_AETHER_TARGET(phackman "${ALL_SOURCES}")

target_link_libraries(phackman secscore)
target_include_directories(phackman PUBLIC module/secs/src/lib)
target_include_directories(phackman PUBLIC module/hadron/src/lib/)


