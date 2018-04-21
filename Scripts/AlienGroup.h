//
// Created by matt on 4/14/18.
//

#ifndef GALAGA_ALIENGROUP_H
#define GALAGA_ALIENGROUP_H


#include <array>
#include <Pure2D/Util/NonCopyable.h>
#include <Pure2D/Renderables/Animator.h>
#include <Pure2D/Util/Clock.h>
#include "../Util/Rect.h"
#include "AlienSpawner.h"
#include "../Util/Defaults.h"

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
    void createAliens(std::array<glm::vec2, size>& positions, SpriteType type, uint32_t start, uint32_t count);

};


#endif //GALAGA_ALIENGROUP_H
