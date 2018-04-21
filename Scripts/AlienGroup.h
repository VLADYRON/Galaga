//
// Created by matt on 4/14/18.
//

#ifndef GALAGA_ALIENGROUP_H
#define GALAGA_ALIENGROUP_H


#include <vector>
#include <array>
#include <Pure2D/Util/Clock.h>
#include <Pure2D/Renderables/Animator.h>
#include <cstdint>
#include <glm/glm.hpp>
#include "../Util/Defaults.h"
#include "../Util/Rect.h"
#include "../Game/World.h"
#include "../Entities/Alien.h"
#include "AlienSpawner.h"
#include "../Util/SpriteMap.h"

class Alien;
class World;

class AlienGroup : private pure::NonCopyable
{
public:
    explicit AlienGroup(World& world, glm::vec2 cellSize, glm::vec2 boundary);

    void update(float deltaTime);
    void reset();
    void start();

    void move(glm::vec2 offset);
    Rect boundingRect() const;

    void setMoveDir(float dir);

    void setPosition(glm::vec2 pos);
    glm::vec2 position() const;

private:
    static const glm::vec2 m_size;

    std::array<glm::vec2, 4> m_catcherPos;
    std::array<glm::vec2, 16> m_mothPos;
    std::array<glm::vec2, 20> m_beePos;
    Rect m_rect;
    float m_moveDir;
    bool m_needsSpawn;
    glm::vec2 m_boundary;
    glm::vec2 m_cellSize;

    World& m_world;
    pure::Clock m_moveTimer;
    pure::Clock m_spawnTimer;
    AlienSpawner m_spawner;

    std::vector<Alien*> m_aliens;
    std::vector<pure::Animator<Alien>> m_animators;
    uint8_t m_groupAnimFrame;

    uint32_t m_spawnOrderIndx = 0;


    void spawnAliens();
    void setupGroupPositions();
    void initAliens();
    void move();
    void tickAnimations();
    bool hasPendingAliens() const;

    template<size_t size>
    void assignPositions(glm::vec2 cellSize, glm::vec2 offset, std::array<glm::vec2, size>& positions)
    {
        const glm::vec2 original = offset;

        for (size_t i = 0; i < positions.size(); i++)
        {
            positions[i] = glm::vec2(
               cellSize.x * offset.x,
               cellSize.y * offset.y
            );

            if ((i + 1) == positions.size() / 2)
            {
                offset.y++;
                offset.x = original.x;
            }
            else
            {
                offset.x++;
            }
        }
    }


    template<size_t size>
    void createAliens(std::array<glm::vec2, size>& positions, SpriteType type, uint32_t start, uint32_t count)
    {
        // default to offscreen pos
        static const glm::vec2 startPos = { -100, -100 };
        const uint32_t end = start + count;
        const auto goToFormation = [](Alien& alien, float dt) {
            glm::vec2 dir = alien.groupCell().position - alien.getPosition();

            if (glm::length(dir) <= 3.f)
            {
                alien.setRotation(180.f); // face toward bottom of screen
                alien.setPosition(alien.groupCell().position);
                alien.endBehavior();
                alien.setState(Alien::State::InFormation);
                return;
            }


            const float rot = (std::atan2(dir.y, dir.x) * pure::RAD_TO_DEG) + 90.f;
            alien.setRotation(rot);

            alien.move(glm::normalize(dir) * alien.speed() * dt);
        };

        for (uint32_t i = start; i < end; i++)
        {
            Alien* alien = &m_world.instantiate<Alien>(startPos);
            defaults::set(*alien, type);
            alien->setGroupCell({ positions[i], i });
            alien->deactivate();
            alien->setBehavior(goToFormation);
            m_aliens.push_back(alien);

            pure::Animator<Alien> animator(alien, 2, alien->textureRect(), { spritemap::SIZE, 0 });
            m_animators.push_back(animator);
        }
    }

    template<size_t size>
    void updateGroupPos(std::array<glm::vec2, size>& positions, Alien* alien)
    {
        const GroupCell cellInfo = alien->groupCell();
        const glm::vec2 newPos = positions[cellInfo.index] + glm::vec2(m_rect.x, m_rect.y);
        alien->setGroupCell({ newPos, cellInfo.index });

        if (alien->state() == Alien::State::InFormation) alien->setPosition(newPos);
    }

};


#endif //GALAGA_ALIENGROUP_H
