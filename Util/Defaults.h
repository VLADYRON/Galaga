//
// Created by matt on 3/31/18.
//

#ifndef GALAGA_DEFAULTS_H
#define GALAGA_DEFAULTS_H

enum class SpriteType
{
    SHIP_WHITE = 0,
    SHIP_RED,
    MISSLE_ENEMY,
    MISSLE_PLAYER,
    // TODO: Add more sprite types?
    BEE,
    MOTH,
    CATCHER
};

class Fighter;
class Missile;
class Alien;

namespace defaults
{
    Missile& set(Missile& missile, SpriteType type);
    Fighter& set(Fighter& spaceship, SpriteType type);
    Alien& set(Alien& alien, SpriteType type);
}

#endif //GALAGA_DEFAULTS_H
