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

namespace pure
{
    class State;
}


class Entity;

class World : private pure::NonCopyable
{
public:

    /**
    * Cleans up any queued entities in deletion queue to be deleted
    */
    void update();

    template<typename T>
    const EArr<T> &getEntities()
    {
        return m_entityManager.get<T>();
    }

    template<typename T>
    T& instantiate(glm::vec2 position)
    {
        T& entity = m_entityManager.create<T>(*this);
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

private:

    EntityManager< 50,
        Missile,
        Alien
        > m_entityManager;

};


#endif //GALAGA_WORLD_H
