//
// Created by matt on 3/30/18.
//

#include "../Entities/Entity.h"
#include "World.h"


using namespace pure;

constexpr uint32_t MAX_MISSILES = 30;
constexpr uint32_t MAX_ALIENS = 50;

World::World():
    m_player(*this)
{
    m_entityManager.resize<Missile>(MAX_MISSILES);
    m_entityManager.resize<Alien>(MAX_ALIENS);
}

PlayerController *World::getPlayer() { return &m_player; }


