//
// Created by matt on 4/23/18.
//

#include "CollisionSystem.h"
#include "../Game/World.h"
#include "../Player/PlayerController.h"
#include "../Util/Rect.h"

CollisionSystem::CollisionSystem(World &world):
    m_world(world)
{

}

void CollisionSystem::update()
{
    resolvePlayerCollision();
    resolveAlienCollision();
    resolveMissileCollision();
}

void CollisionSystem::resolvePlayerCollision()
{
//    Fighter& player = m_world.getPlayer()->getShip();
//    auto aliens = m_world.getEntities<Alien>();
//    auto missiles = m_world.getEntities<Missile>();
//
//    Rect playerRect = player.getBoundingRect();
//
//    for (auto a : aliens)
//        if (a->getBoundingRect().doesCollide(playerRect))
//            player.deactivate();
//
//    for (auto m : missiles)
//        if (m->getBoundingRect().doesCollide(playerRect))
//            player.deactivate();
}

void CollisionSystem::resolveMissileCollision()
{
    Fighter& player = m_world.getPlayer()->getShip();
    auto aliens = m_world.getEntities<Alien>();
    auto missiles = m_world.getEntities<Missile>();

    Rect playerRect = player.collilderRect();


    for (auto m : missiles)
    {
        if (m->colliderRect().doesCollide(playerRect))
        {
            player.deactivate();
            m_world.destroy<Missile>(*m);
            continue;
        }

        for (auto a : aliens)
        {
            if (m->colliderRect().doesCollide(a->colliderRect()))
            {
                m_world.destroy<Alien>(*a);
                m_world.destroy<Missile>(*m);
            }
        }
    }
}

void CollisionSystem::resolveAlienCollision()
{
    Fighter& player = m_world.getPlayer()->getShip();
    auto aliens = m_world.getEntities<Alien>();
    auto missiles = m_world.getEntities<Missile>();
}
