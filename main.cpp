#include <iostream>
#include "Game.h"

int main()
{
    Game g;
    g.createWindow("Galaga", 1366, 768);
    g.start();
    return 0;
}