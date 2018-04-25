//
// Created by matt on 4/23/18.
//

#ifndef GALAGA_COLLISIONSYSTEM_H
#define GALAGA_COLLISIONSYSTEM_H

class World;

class CollisionSystem
{
public:
    explicit CollisionSystem(World& world);

    void update();

private:
    World& m_world;

    void resolvePlayerCollision();
    void resolveMissileCollision();
    void resolveAlienCollision();
};


#endif //GALAGA_COLLISIONSYSTEM_H
