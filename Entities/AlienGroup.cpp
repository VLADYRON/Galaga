//
// Created by matt on 4/14/18.
//

#include <Pure2D/Util/Convert.h>
#include "AlienGroup.h"

#include "../Splines/SplinePaths.h"
#include "../Util/Rect.h"

constexpr float moveTickDir = 0.5f;
const glm::vec2 AlienGroup::m_size = { 10, 5 };

AlienGroup::AlienGroup(World &world, glm::vec2 cellSize, glm::vec2 boundary):
    m_world(world),
    m_rect({ 50, 50 }),
    m_moveDir(20.f),
    m_boundary(boundary),
    m_cellSize(cellSize)
{
    setGroupPositions();
}

void AlienGroup::update(float deltaTime)
{
    startSpawnDives();

    for (auto alien : m_aliens)
    {
        if (!alien->isActive()) continue;

        alien->update(deltaTime);

        switch (alien->type())
        {
            case SpriteType::CATCHER:
                updateGroupPos(m_catcherPos, alien);
                break;
            case SpriteType::MOTH:
                updateGroupPos(m_mothPos, alien);
                break;
            case SpriteType::BEE:
                updateGroupPos(m_beePos, alien);
                break;
            default:
                std::cout << "Invalid Alien SpriteType. Given: " << static_cast<int>(alien->type())
                    << " Expected 4, 5 or 6" << std::endl;
        }
    }

   if (m_tickTimer.getElapsedTime() >= moveTickDir)
    {
        const glm::vec2 newPos = { m_rect.x  + m_moveDir, m_rect.y };
        Rect boundaryBox = { 0, 0, m_boundary.x, m_boundary.y };

        // if next movement will be outside boundary, switch directions
        glm::vec2 nextPos;
        if (m_moveDir <= 0.f)
        {
            nextPos = { newPos.x + m_moveDir, m_rect.y };
            // left side position does not account for size of sprites,
            // so we have to add that to nextPos check so sprites don't got off screen.
            if (boundaryBox.isOutside({ nextPos.x -  m_cellSize.x * 0.5f, nextPos.y }))
                m_moveDir = -m_moveDir;
        }
        else
        {
            nextPos = { newPos.x + m_rect.w, m_rect.y };

            if (boundaryBox.isOutside(nextPos))
                m_moveDir = -m_moveDir;
        }

        setPosition(newPos);

        m_tickTimer.restart();
    }

}

// TODO: Stop using this and use start()
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
        alien->setGroupCell({ m_beePos[i], i });
        alien->deactivate();
        m_aliens.push_back(alien);
        m_divingAliens.push_back(alien);
    }

    m_spawnTimer.restart();
    m_diveIndx = 0;
}

void AlienGroup::startSpawnDives()
{
    if (m_diveIndx >= m_divingAliens.size())
        return;

    if (m_spawnTimer.getElapsedTime() >= 0.095f)
    {
        m_spawnTimer.restart();
        m_divingAliens[m_diveIndx]->startDivePath();
        m_divingAliens[m_diveIndx]->activate();
        m_diveIndx++;
    }
}

void AlienGroup::setGroupPositions()
{
    {
        float offset = 3;
        for (auto &catcherPos : m_catcherPos)
        {
            catcherPos = glm::vec2(
                m_cellSize.x * offset, 0
            );
            offset++;
        }
    }

    m_rect.w = m_cellSize.x * AlienGroup::m_size.x;
    m_rect.h = m_cellSize.y * AlienGroup::m_size.y;

    assignPositions(m_cellSize, { 1, 1 }, m_mothPos);
    assignPositions(m_cellSize, { 0, 3 }, m_beePos);
}


void AlienGroup::reset()
{
    for (auto alien : m_aliens)
        m_world.destroy<Alien>(*alien);
    m_aliens.clear();
}

// TODO: Use this and not spawnAliens()
void AlienGroup::start()
{
    m_divingAliens.clear();

    initAliens(m_catcherPos, SpriteType::CATCHER);
    initAliens(m_mothPos, SpriteType::MOTH);
    initAliens(m_beePos, SpriteType::BEE);

    m_spawnTimer.restart();
    m_tickTimer.restart();
    m_diveIndx = 0;
}

Rect AlienGroup::boundingRect() const { return m_rect; }

void AlienGroup::setPosition(glm::vec2 pos)
{
    m_rect = { pos.x, pos.y, m_rect.w, m_rect.h };
}

void AlienGroup::move(glm::vec2 offset)
{
    m_rect = {
        m_rect.x + offset.x,
        m_rect.y + offset.y,
        m_rect.w, m_rect.h
    };
}

glm::vec2 AlienGroup::position() const { return { m_rect.x, m_rect.y }; }

void AlienGroup::setMoveDir(float dir) { m_moveDir = dir; }
