#include <iostream>
#include "Game/Game.h"
#include "Entities/Alien.h"
#include "Game/ObjectPool.h"
#include <glm/glm.hpp>

int main()
{

    Game g;
    g.createWindow("Galaga", 750, 900);
    g.start();

    return 0;
}