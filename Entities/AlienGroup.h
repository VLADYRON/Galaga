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

class Alien;
class World;

class AlienGroup
{
public:
    explicit AlienGroup(World& world, glm::vec2 cellSize);

    void spawnAliens(size_t count, SpriteType type);

    void update(float deltaTime);

private:
//    static constexpr glm::vec2 m_dimensions = glm::vec2(5,5);
//    static constexpr size_t m_maxAliens = (size_t)(m_dimensions.x * m_dimensions.y);
    std::array<glm::vec2, 50> m_alienPositions;

    World& m_world;
    pure::Clock m_timer;
    size_t m_diveIndx;

    std::vector<Alien*> m_aliens;
    std::vector<Alien*> m_divingAliens;

    void startSpawnDives();
    void setGroupPositions(const glm::vec2& cellSize);
};


#endif //GALAGA_ALIENGROUP_H
