//
// Created by matt on 3/31/18.
//

#ifndef GALAGA_DEFAULTS_H
#define GALAGA_DEFAULTS_H

enum class SpriteType
{
    SHIP_WHITE,
    SHIP_RED,
    MISSLE_ENEMY,
    MISSLE_PLAYER
};

class Spaceship;
class Missile;

namespace defaults
{
    Missile& set(Missile& missile, SpriteType type);
    Spaceship& set(Spaceship& spaceship, SpriteType type);
}

#endif //GALAGA_DEFAULTS_H
