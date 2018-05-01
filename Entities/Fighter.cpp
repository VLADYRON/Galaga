//
// Created by matt on 3/30/18.
//

#include "Fighter.h"
#include "../Game/World.h"
#include "../Util/Rect.h"
#include "Missile.h"
#include "SpriteType.h"
#include "../Util/TextureManager.h"
#include "../Util/SpriteMap.h"
#include "../Game/AssetPaths.h"
#include <Pure2D/Util/Convert.h>

Fighter::Fighter()
{
    setSize({ 50, 50 });
    setOrigin(getSize() / 2.f);
    setVelocity({ 250, 0 });
}

void Fighter::fireMissile()
{
    glm::vec2 shipPos = position();
    glm::vec2 firePos = { shipPos.x, shipPos.y - (getSize().y / 2.f) };
    auto& m = m_world->instantiate<Missile>(firePos, SpriteType::MISSLE_PLAYER);
}

void Fighter::setWorld(World &world)
{
    m_world = &world;
}

Rect Fighter::collilderRect() const
{
    Rect rect = getBoundingRect();

    return {
        rect.x + 3,
        rect.y + 2,
        rect.w - 3,
        rect.h - 2
    };
}

void Fighter::activate()
{
    SpaceEntity::activate();

    pure::Texture* spritesheet = TextureManager::instance().getTexture(paths::GALAGA_SPRITE_SHEET);
    assert(spritesheet != nullptr);

    setTexture(spritesheet);
    if (type() == SpriteType::SHIP_WHITE)
        setTextureRect(spritemap::SHIP_WHITE);
    else if (type() == SpriteType::SHIP_RED)
        setTextureRect(spritemap::SHIP_RED);
}




