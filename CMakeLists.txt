# Stolen from https://github.com/aminosbh/falling-brick-game

cmake_minimum_required(VERSION 3.0.0)

project(cpp-blocks)

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# add_executable(tetris main.cpp)
# Add all c source files under the src directory
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Make CMake look for find_package scripts in ./cmake/sdl2
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Add all headers files under the include directory
# target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add compiler errors/warnings flags
# target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
# target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>)


# Add SDL2 library
# find_package(SDL2 REQUIRED)
# target_link_libraries(${PROJECT_NAME} SDL2::Main)

# Add SDL2_image library
#find_package(SDL2_image REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Image)

# Add SDL2_ttf library
#find_package(SDL2_ttf REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# Add SDL2_net library
#find_package(SDL2_net REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Net)

# Add SDL2_mixer library
#find_package(SDL2_mixer REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

# Add SDL2_gfx library
# find_package(SDL2_gfx REQUIRED)
# target_link_libraries(${PROJECT_NAME} SDL2::GFX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
