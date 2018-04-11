//
// Created by matt on 3/30/18.
//

#include "Fighter.h"
#include "../Game/World.h"

#include "Missile.h"
#include "../Util/Defaults.h"
#include <Pure2D/Util/Convert.h>

Fighter::Fighter(World &world)
    : SpaceEntity(world)
{
    setSize({ 50, 50 });
    setOrigin(getSize() / 2.f);
    setVelocity({ 250, 0 });
}

void Fighter::fireMissile()
{
    glm::vec2 shipPos = getPosition();
    glm::vec2 firePos = { shipPos.x, shipPos.y - getSize().y / 2.f };
    auto& m = m_world->instantiate<Missile>(firePos);
    defaults::set(m, SpriteType::MISSLE_PLAYER);
}





