cmake_minimum_required(VERSION 3.9)
project(Galaga)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

configure_file("${CMAKE_SOURCE_DIR}/Assets/abduction-anim.png" "${CMAKE_CURRENT_BINARY_DIR}/abduction-anim.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/Assets/galaga-sprite-sheet.png" "${CMAKE_CURRENT_BINARY_DIR}/galaga-sprite-sheet.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/Assets/galaga-sprite-sheet-spread.png" "${CMAKE_CURRENT_BINARY_DIR}/galaga-sprite-sheet-spread.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/Assets/alien-explosion.png" "${CMAKE_CURRENT_BINARY_DIR}/alien-explosion.png" COPYONLY)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Pure2D REQUIRED)


add_executable(Galaga main.cpp Game/Game.cpp Game/Game.h Game/AssetPaths.h Background/StarBackground.cpp Background/StarBackground.h Components/Transform.h Components/Transform.cpp Player/PlayerController.cpp Player/PlayerController.h Entities/Entity.cpp Entities/Entity.h Entities/Fighter.cpp Entities/Fighter.h Components/Sprite.h Components/Sprite.cpp Util/Rect.h Entities/Missile.cpp Entities/Missile.h Util/SpriteMap.h Game/World.cpp Game/World.h Game/EntityManager.h typedefs.h Util/TextureManager.cpp Util/TextureManager.h Util/Rect.cpp Splines/Spline.cpp Splines/Spline.h Entities/SpaceEntity.cpp Entities/SpaceEntity.h Entities/Alien.cpp Entities/Alien.h Splines/SplinePath.cpp Splines/SplinePath.h States/PlayState.cpp States/PlayState.h States/GameState.h Game/ObjectPool.h Splines/SplinePaths.h Splines/SplinePaths.cpp Scripts/Formation.cpp Scripts/Formation.h Interface/LifeCycle.h Components/FormationPosition.h Scripts/AlienSpawner.cpp Scripts/AlienSpawner.h Scripts/CollisionSystem.cpp Scripts/CollisionSystem.h Entities/Explosion.cpp Entities/Explosion.h Entities/SpriteType.h Components/Health.h Components/Health.cpp Entities/Catcher.cpp Entities/Catcher.h Entities/Soldier.cpp Entities/Soldier.h)
include_directories(Galaga ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} ${PURE2D_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

target_link_libraries(Galaga ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} ${PURE2D_LIBRARIES} ${Boost_LIBRARIES})