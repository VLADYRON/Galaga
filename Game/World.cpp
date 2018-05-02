//
// Created by matt on 3/30/18.
//

#include "../Entities/Entity.h"
#include "World.h"


using namespace pure;

// TODO: Re-evaluate the size of these constants...
constexpr uint32_t MAX_MISSILES = 30;
constexpr uint32_t MAX_CATCHERS = 4;
constexpr uint32_t MAX_SOLDIERS = 36;
constexpr uint32_t MAX_EXPLOSIONS = 20;

World::World():
    m_player(*this)
{
    m_entityManager.resize<Missile>(MAX_MISSILES);
    m_entityManager.resize<Catcher>(MAX_CATCHERS);
    m_entityManager.resize<Soldier>(MAX_SOLDIERS);
    m_entityManager.resize<Explosion>(MAX_EXPLOSIONS);

}

PlayerController *World::getPlayer() { return &m_player; }


