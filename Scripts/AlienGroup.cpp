//
// Created by matt on 4/14/18.
//

#include <Pure2D/Util/Convert.h>
#include <Pure2D/Util/Random.h>
#include "AlienGroup.h"

#include "../Splines/SplinePaths.h"
#include "../Util/Rect.h"

constexpr float moveTickDir = 0.5f;
constexpr float spawnDelay = 1.5f;
const glm::vec2 AlienGroup::m_size = { 10, 5 };

AlienGroup::AlienGroup(World &world, glm::vec2 cellSize, glm::vec2 boundary):
    m_world(world),
    m_rect({ 50, 50 }),
    m_moveDir(20.f),
    m_boundary(boundary),
    m_cellSize(cellSize),
    m_groupAnimFrame(0)
{
    setupGroupPositions();
    m_spawner.setOnDone([this]() {
        if (hasPendingAliens())
        {
            m_needsSpawn = true;
            m_spawnTimer.restart();
        }
    });
}

void AlienGroup::update(float deltaTime)
{

    if (m_needsSpawn && m_spawnTimer.getElapsedTime() >= spawnDelay)
        spawnAliens();

   if (m_moveTimer.getElapsedTime() >= moveTickDir)
   {
       move();
       tickAnimations();
   }
    m_spawner.update();
    for (auto alien : m_aliens)
    {
        if (!alien->isActive()) continue;

        alien->update(deltaTime);

        if (alien->state() == Alien::State::DiveEnd)
            alien->startBehavior();

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


}

// TODO: Stop using this and use start()
void AlienGroup::spawnAliens()
{
    if (!hasPendingAliens()) return;

    for (int i = 0; i < 8; i++)
    {
        Alien* alien = m_aliens[m_spawnOrderIndx++];

        alien->setDivePath(splinePaths::doubleLoopLeft({-107, 787}), false);
        m_spawner.addAlien(alien);
    }

    m_spawner.start();
    m_needsSpawn = false;
}

void AlienGroup::setupGroupPositions()
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

    {
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(m_mothPos.begin(), m_mothPos.end(), g);
        std::shuffle(m_beePos.begin(), m_beePos.end(), g);
    }

    initAliens();

    m_moveTimer.restart();
    m_spawnTimer.restart();
    m_needsSpawn = true;
}


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

Rect AlienGroup::boundingRect() const { return m_rect; }
glm::vec2 AlienGroup::position() const { return { m_rect.x, m_rect.y }; }

void AlienGroup::setMoveDir(float dir) { m_moveDir = dir; }

void AlienGroup::move()
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

    m_moveTimer.restart();
}

bool AlienGroup::hasPendingAliens() const
{
    return m_spawnOrderIndx < m_aliens.size();
}

void AlienGroup::initAliens()
{
    uint32_t mothIndx = 0;
    uint32_t beeIndx = 0;

    createAliens(m_beePos, SpriteType::BEE, beeIndx, 4); beeIndx += 4;
    createAliens(m_mothPos, SpriteType::MOTH, mothIndx, 4); mothIndx += 4;

    createAliens(m_catcherPos, SpriteType::CATCHER, 0, 4);
    createAliens(m_mothPos, SpriteType::MOTH, mothIndx, 4); mothIndx += 4;
    createAliens(m_mothPos, SpriteType::MOTH, mothIndx, 8); mothIndx += 8;

    createAliens(m_beePos, SpriteType::BEE, beeIndx, 8); beeIndx += 8;
    createAliens(m_beePos, SpriteType::BEE, beeIndx, 8); beeIndx += 8;
}

void AlienGroup::tickAnimations()
{

    for (size_t i = 0; i < m_animators.size(); i++)
    {
        if (m_aliens[i]->state() == Alien::State::InFormation)
        {
            if (m_animators[i].animFrameIndx() == m_groupAnimFrame)
                m_animators[i].step();

        }
    }
    m_groupAnimFrame = static_cast<uint8_t>(!m_groupAnimFrame);
}

