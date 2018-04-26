//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_WORLD_H
#define GALAGA_WORLD_H

#include <Pure2D/State/StateManager.h>
#include <glm/vec2.hpp>
#include <Pure2D/State/State.h>
#include "EntityManager.h"
#include "../Entities/Fighter.h"
#include "../typedefs.h"
#include "../Entities/Missile.h"
#include "../Entities/Alien.h"
#include "../Player/PlayerController.h"

namespace pure
{
    class State;
}


class Entity;
class PlayerController;

class World : private pure::NonCopyable
{
public:

    World();

    template<typename T>
    const EArr<T*> &getEntities()
    {
        return m_entityManager.get<T>().getLiveObjects();
    }

    template<typename T>
    T& instantiate(glm::vec2 position)
    {
        T& entity = m_entityManager.create<T>();
        entity.setPosition(position);
        return entity;
    }

    /**
     * Requests for an entity to be deleted
     * @tparam T Type of entity to be deleted
     * @param entity
     */
    template<typename T>
    void destroy(T& entity)
    {
        m_entityManager.destroy<T>(&entity);
    }

    PlayerController* getPlayer();

private:

    PlayerController m_player;
    EntityManager<
        Missile,
        Alien
        > m_entityManager;

};


#endif //GALAGA_WORLD_H
