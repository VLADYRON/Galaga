//
// Created by matt on 4/26/18.
//

#include "Explosion.h"


Explosion::Explosion():
    m_anim(*this)
{ }

void Explosion::activate()
{
    SpaceEntity::activate();
}

void Explosion::deactivate()
{
    SpaceEntity::deactivate();
}

void Explosion::setAnim(uint32_t numAnims, SDL_Rect start, glm::vec2 offset)
{
    m_anim.setAnimOpts(numAnims, start, offset);
}
