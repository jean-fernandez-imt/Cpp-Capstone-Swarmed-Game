project(Swarmed)

cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++17")
set(CMAKE_BUILD_TYPE "Debug")

add_executable(
    ${PROJECT_NAME} 
    src/main.cpp 
    src/renderer.cpp 
    src/texture.cpp
    src/aim.cpp
    src/player.cpp
    src/gun.cpp
    src/army.cpp
    src/enemy.cpp
    src/bullet.cpp 
    src/timer.cpp
    src/game.cpp)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})