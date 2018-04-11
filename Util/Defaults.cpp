//
// Created by matt on 3/31/18.
//

#include "Defaults.h"
#include "../Entities/Fighter.h"
#include "../Entities/Missile.h"
#include "../Entities/Alien.h"
#include "TextureManager.h"
#include "../Game/AssetPaths.h"
#include "SpriteMap.h"

Missile& defaults::set(Missile& missile, SpriteType type)
{
    pure::Texture* spritesheet = TextureManager::instance().getTexture(paths::GalagaSpriteSheet);
    assert(spritesheet != nullptr);

    missile.setTexture(spritesheet);
    if (type == SpriteType::MISSLE_PLAYER)
        missile.setTextureRect(spritemap::PLAYER_MISSLE);
    else if (type == SpriteType::MISSLE_ENEMY)
        missile.setTextureRect(spritemap::ENEMY_MISSLE);

    return missile;
}

Fighter& defaults::set(Fighter& spaceship, SpriteType type)
{
    pure::Texture* spritesheet = TextureManager::instance().getTexture(paths::GalagaSpriteSheet);
    assert(spritesheet != nullptr);

    spaceship.setTexture(spritesheet);
    if (type == SpriteType::SHIP_WHITE)
        spaceship.setTextureRect(spritemap::SHIP_WHITE);
    else if (type == SpriteType::SHIP_RED)
        spaceship.setTextureRect(spritemap::SHIP_RED);

    return spaceship;
}

Alien& defaults::set(Alien& alien, SpriteType type)
{
    pure::Texture* spritesheet = TextureManager::instance().getTexture(paths::GalagaSpriteSheet);
    assert(spritesheet != nullptr);

    alien.setTexture(spritesheet);
    if (type == SpriteType::BEE)
        alien.setTextureRect(spritemap::BEE_CLOSED);

    return alien;
}