cmake_minimum_required(VERSION 3.9)
project(Galaga)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Pure2D REQUIRED)


add_executable(Galaga main.cpp Game.cpp Game.h)
include_directories(Galaga ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} ${PURE2D_INCLUDE_DIRS})

target_link_libraries(Galaga ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} ${PURE2D_LIBRARIES})