cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Game)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(Game src/main.cpp src/game.cpp src/keyboard.cpp src/renderer.cpp src/snake.cpp src/texture.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} src)
target_link_libraries(Game ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})