//
// Created by matt on 3/31/18.
//

#include <iostream>
#include "Defaults.h"
#include "../Entities/Fighter.h"
#include "../Entities/Missile.h"
#include "../Entities/Alien.h"
#include "../Entities/Explosion.h"
#include "TextureManager.h"
#include "../Game/AssetPaths.h"
#include "SpriteMap.h"

Missile& defaults::set(Missile& missile, SpriteType type)
{
    pure::Texture* spritesheet = TextureManager::instance().getTexture(paths::GALAGA_SPRITE_SHEET);
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
    pure::Texture* spritesheet = TextureManager::instance().getTexture(paths::GALAGA_SPRITE_SHEET);
    assert(spritesheet != nullptr);

    spaceship.setTexture(spritesheet);
    if (type == SpriteType::SHIP_WHITE)
        // FIXME: THIS TEXTURE MAPPING IS AIDS FIX DIS
        spaceship.setTextureRect(spritemap::SHIP_WHITE);
    else if (type == SpriteType::SHIP_RED)
        spaceship.setTextureRect(spritemap::SHIP_RED);

    return spaceship;
}

Alien& defaults::set(Alien& alien, SpriteType type)
{
    pure::Texture* spritesheet = TextureManager::instance().getTexture(paths::GALAGA_SPRITE_SHEET);
    assert(spritesheet != nullptr);

    alien.setTexture(spritesheet);
    SDL_Rect textureRect{};
    switch (type)
    {
        case SpriteType::BEE:
            textureRect = spritemap::BEE_OPEN;
            break;
        case SpriteType::MOTH:
            textureRect = spritemap::MOTH_OPEN;
            break;
        case SpriteType::CATCHER:
            textureRect = spritemap::CATCHER_TURQUOISE_OPEN;
            break;
        default:
            std::cout << "Given spritetype not defined for set function of type Alien" << std::endl;
    }


    alien.setTextureRect(textureRect);
    alien.setType(type);

    return alien;
}

Explosion &defaults::set(Explosion &explosion, SpriteType type)
{
    pure::Texture* spritesheet = nullptr;

    if (type == SpriteType::EXPLOSION_ALIEN)
    {
        spritesheet = TextureManager::instance().getTexture(paths::ALIEN_EXPLOSION);
        explosion.setAnim(4, spritemap::ALIEN_EXPLOSION, { spritemap::ALIEN_EXPLOSION_SIZE, 0 });

    }
    else if (type == SpriteType::EXPLOSION_FIGHTER)
    {
        spritesheet = TextureManager::instance().getTexture(paths::GALAGA_SPRITE_SHEET);
        explosion.setAnim(4, spritemap::FIGHTER_EXPLOSION_BEGIN, { spritemap::FIGHTER_EXPLOSION_SIZE, 0 });
    }

    assert(spritesheet != nullptr);
    explosion.setTexture(spritesheet);

    return explosion;
}
