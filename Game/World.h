//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_WORLD_H
#define GALAGA_WORLD_H

#include <Pure2D/State/StateManager.h>
#include <glm/vec2.hpp>
#include <functional>
#include <Pure2D/State/State.h>
#include <typeindex>
#include <vector>
#include "EntityManager.h"
#include "../Entities/Fighter.h"
#include "../typedefs.h"
#include "../Entities/Missile.h"
#include "../Entities/Alien.h"
#include "../Player/PlayerController.h"
#include "../Entities/Explosion.h"
#include "../Entities/Soldier.h"
#include "../Entities/Catcher.h"

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
        checkTypeErr<T>();

        return m_entityManager.get<T>().getLiveObjects();
    }

    template<typename T>
    EArr<T*> getEntitiesOfType()
    {
        return m_entityManager.getAllOfType<T>();
    }

    template<typename T>
    T& instantiate(glm::vec2 position, SpriteType type, bool shouldActivate = true)
    {
        checkTypeErr<T>();

        T& entity = m_entityManager.create<T>();
        entity.setPosition(position);
        entity.setType(type);

        if (shouldActivate) entity.activate();

        return entity;
    }

    /**
    * Searches in all pools of given base type for given entity
    * and then destroys it
    *
    * -- Use this for polymorphic types when exact type is not known --
    *
    * @tparam T Base class
    * @param entity entity to be destroyed
    */
    template<typename T>
    void destroyBySuper(T& entity)
    {
        checkTypeErr<T>();

        entity.deactivate();
        m_entityManager.destroyBySuper(&entity);
    }

    /**
     * Requests for an entity to be deleted
     * @tparam T Type of entity to be deleted
     * @param entity
     */
    template<typename T>
    void destroy(T& entity)
    {
        checkTypeErr<T>();

        entity.deactivate();
        m_entityManager.destroy<T>(&entity);
    }

    PlayerController* getPlayer();

private:

    PlayerController m_player;
    EntityManager<
        Missile,
        Soldier,
        Catcher,
        Explosion
        > m_entityManager;

    template<typename T>
    constexpr void checkTypeErr()
    {
        static_assert(std::is_base_of<Entity, T>::value, "Given type must be subclass of Entity");
    }


};


#endif //GALAGA_WORLD_H
