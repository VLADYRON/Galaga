cmake_minimum_required(VERSION 3.9)
project(Galaga)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

configure_file("${CMAKE_SOURCE_DIR}/Assets/abduction-anim.png" "${CMAKE_CURRENT_BINARY_DIR}/abduction-anim.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/Assets/galaga-sprite-sheet.png" "${CMAKE_CURRENT_BINARY_DIR}/galaga-sprite-sheet.png" COPYONLY)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Pure2D REQUIRED)


add_executable(Galaga main.cpp Game/Game.cpp Game/Game.h Game/AssetPaths.h Background/StarBackground.cpp Background/StarBackground.h)
include_directories(Galaga ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} ${PURE2D_INCLUDE_DIRS})

target_link_libraries(Galaga ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} ${PURE2D_LIBRARIES})