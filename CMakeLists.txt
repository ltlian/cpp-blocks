# Stolen from https://github.com/aminosbh/falling-brick-game

cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
find_package(SDL2_gfx REQUIRED)


### Now set up your actual target(s)
add_executable(${PROJECT_NAME} "src/cpp-blocks.cpp")
add_library(ShapeRender src/shaperender.cpp include/ShapeRender.h)
target_link_libraries(ShapeRender SDL2::Core SDL2::GFX)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS} PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} SDL2::Core SDL2::GFX ShapeRender)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
