//
// Created by matt on 4/14/18.
//

#include "AlienGroup.h"
#include "../Game/World.h"
#include "../Splines/SplinePaths.h"
#include "../Entities/Alien.h"


AlienGroup::AlienGroup(World &world, glm::vec2 cellSize):
    m_world(world)
{
    setGroupPositions(cellSize);
}

void AlienGroup::update(float deltaTime)
{
    startSpawnDives();

    for (auto alien : m_aliens)
        alien->update(deltaTime);
}

void AlienGroup::spawnAliens(size_t count, SpriteType type)
{

    m_divingAliens.clear();
    m_divingAliens.reserve(count);

    for (size_t i = 0; i < count; i++)
    {
        // TODO: need to find a way to figure out where spawn locations will be
        Alien* alien = &m_world.instantiate<Alien>({ -107,787 });
        defaults::set(*alien, type);
        alien->setDivePath(splinePaths::doubleLoopLeft({-107, 787}), false);
        m_aliens.push_back(alien);
        m_divingAliens.push_back(alien);
    }

    m_timer.restart();
    m_diveIndx = 0;
}

void AlienGroup::startSpawnDives()
{
    if (m_diveIndx >= m_divingAliens.size())
        return;

    if (m_timer.getElapsedTime() >= 0.095f)
    {
        m_timer.restart();
        m_divingAliens[m_diveIndx]->startDivePath();
        m_diveIndx++;
    }
}

// TODO: Find a way to set positions in grid for each alien.
void AlienGroup::setGroupPositions(const glm::vec2& cellSize)
{
    for (size_t i = 0; i < m_alienPositions.size(); i++)
    {

    }
}
