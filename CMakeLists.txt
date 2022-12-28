# Stolen from https://github.com/aminosbh/falling-brick-game

cmake_minimum_required(VERSION 3.0.0)

project(cpp-blocks)

include(CTest)
enable_testing()

# Generates a compile_commands.json file describing exactly how each source file is compiled
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Make CMake look for find_package scripts in ./cmake/sdl2
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)


# Add compiler errors/warnings flags
# target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
# target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>)


# Detect all required libraries before defining your own targets
find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_net REQUIRED)
#find_package(SDL2_mixer REQUIRED)
#find_package(SDL2_gfx REQUIRED)

### Now set up your actual target(s)

# JALF: I prefer to avoid GLOB  stuff because it doesn't automatically detect if you add files, unless you manually rerun cmake
# file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
# JALF: Just explicitly list the source files you want
add_executable(${PROJECT_NAME} "src/tetris.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} SDL2::Core)
# JALF: If multiple libs you can just list them all
#target_link_libraries(${PROJECT_NAME} SDL2::Core SDL2::Net SDL2::GFX whateverelse)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
