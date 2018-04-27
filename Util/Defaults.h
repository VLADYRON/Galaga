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
    BEE,
    MOTH,
    CATCHER,
    EXPLOSION_ALIEN,
    EXPLOSION_FIGHTER
};

class Fighter;
class Missile;
class Alien;
class Explosion;

namespace defaults
{
    Missile& set(Missile& missile, SpriteType type);
    Fighter& set(Fighter& spaceship, SpriteType type);
    Alien& set(Alien& alien, SpriteType type);
    Explosion& set(Explosion& explosion, SpriteType type);
}

#endif //GALAGA_DEFAULTS_H
