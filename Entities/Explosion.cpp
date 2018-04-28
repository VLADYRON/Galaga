//
// Created by matt on 4/26/18.
//

#include <iostream>
#include "Explosion.h"


Explosion::Explosion():
    m_anim(*this)
{
    setSize({ 100, 85 });
    setOrigin(getSize() / 2.f);
}

void Explosion::setAnim(uint32_t numAnims, SDL_Rect start, glm::vec2 offset)
{
    m_anim.setAnimOpts(numAnims, start, offset);
    m_anim.setDelay(0.05f);
}

void Explosion::update(float deltaTime)
{
    if (!isDone()) m_anim.timedStep();
}

bool Explosion::isDone() const { return m_anim.hasCompletedCycle(); }
