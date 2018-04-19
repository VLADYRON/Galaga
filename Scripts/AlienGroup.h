//
// Created by matt on 4/14/18.
//

#ifndef GALAGA_ALIENGROUP_H
#define GALAGA_ALIENGROUP_H


#include <vector>
#include <array>
#include <Pure2D/Util/Clock.h>
#include <glm/vec2.hpp>
#include "../Util/Defaults.h"
#include "../Util/Rect.h"
#include "../Game/World.h"
#include "../Entities/Alien.h"
#include "AlienSpawner.h"

class Alien;
class World;

class AlienGroup : private pure::NonCopyable
{
private:
//    struct SpawnGroupCollection
//    {
//        Alien* get(int x, int y);
//        std::vector<Alien*> getRow(int row);
//        std::array<Alien*, 40> groups;
//    private:
//        static constexpr int m_width = 8;
//    };

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

    // TODO: move this back to private when done debugging
    std::array<glm::vec2, 4> m_catcherPos;
    std::array<glm::vec2, 16> m_mothPos;
    std::array<glm::vec2, 20> m_beePos;
    Rect m_rect;
private:
    static const glm::vec2 m_size;
    float m_moveDir;
    bool m_needsSpawn;
    glm::vec2 m_boundary;
    glm::vec2 m_cellSize;

    World& m_world;
    pure::Clock m_moveTimer;
    pure::Clock m_spawnTimer;
    AlienSpawner m_spawner;
//    SpawnGroupCollection m_groups;

    std::vector<Alien*> m_aliens;

    // TEMP
    std::vector<Alien*> m_spawnOrder;
    int m_spawnOrderIndx = 0;
    // END TEMP

    void spawnAliens();
    void setupGroupPositions();
    void setupSpawnGroups();
    void move();
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
    void initAliens(std::array<glm::vec2, size>& positions, SpriteType type)
    {
        // default to offscreen pos
        static const glm::vec2 startPos = { -100, -100 };

        for (size_t i = 0; i < positions.size(); i++)
        {
            Alien* alien = &m_world.instantiate<Alien>(startPos);
            defaults::set(*alien, type);
            alien->setGroupCell({ positions[i], i });
            alien->deactivate();
            m_aliens.push_back(alien);
        }
    }

    template<size_t size>
    void updateGroupPos(std::array<glm::vec2, size>& positions, Alien* alien)
    {
        const GroupCell cellInfo = alien->groupCell();
        const glm::vec2 newPos = positions[cellInfo.index] + glm::vec2(m_rect.x, m_rect.y);
        alien->setGroupCell({ newPos, cellInfo.index });

        if (!alien->isDiving()) alien->setPosition(newPos);
    }

};


#endif //GALAGA_ALIENGROUP_H