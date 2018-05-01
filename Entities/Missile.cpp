//
// Created by matt on 3/30/18.
//

#include <iostream>
#include <cmath>
#include <glm/ext.hpp>
#include "Missile.h"
#include "../Game/World.h"
#include "../Util/Rect.h"
#include "../Util/SpriteMap.h"
#include "../Util/TextureManager.h"
#include "../Game/AssetPaths.h"

Missile::Missile(): m_type(SpriteType::UNKNOWN)
{
    setSize({ 50,50 });
    setOrigin(getSize() / 2.f);
    setVelocity({ 0, 750 });
}

void Missile::update(float deltaTime)
{
    move({ 0.f, -std::round(velocity().y * deltaTime) });
}

Rect Missile::colliderRect() const
{
    return {
        position().x - 3,
        position().y - 15,
        10,
        28
    };
}

void Missile::activate()
{
    SpaceEntity::activate();

    pure::Texture* spritesheet = TextureManager::instance().getTexture(paths::GALAGA_SPRITE_SHEET);
    assert(spritesheet != nullptr);

    setTexture(spritesheet);
    if (type() == SpriteType::MISSLE_PLAYER)
        setTextureRect(spritemap::PLAYER_MISSLE);
    else if (type() == SpriteType::MISSLE_ENEMY)
        setTextureRect(spritemap::ENEMY_MISSLE);
}


