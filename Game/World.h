//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_WORLD_H
#define GALAGA_WORLD_H

#include <Pure2D/State/StateManager.h>
#include <glm/vec2.hpp>
#include <Pure2D/State/State.h>

namespace pure
{
    class State;
}

class Entity;

class World
{
public:
    using UEntity_Ptr = std::unique_ptr<Entity>;

    explicit World(pure::Window &window);

    const std::vector<UEntity_Ptr> &getEntities(pure::State *state);

    template<typename T>
    T& instantiate(glm::vec2 position, pure::State *state = nullptr)
    {
        if (!state) state = m_currentState;

        std::unique_ptr<T> entity = std::make_unique<T>(*this);
        entity->setPosition(position);

        std::vector<UEntity_Ptr>& stateEntities = m_entities[state];

        stateEntities.push_back(std::move(entity));
        return *stateEntities.back();
    }

    bool destroy(Entity& entity, pure::State* state = nullptr);

    /**
     *  TODO:
     *  We will keep a map of state to a vector of pointers to entities in that state.
     *  something like: std::unordered_map<State*, std::vector<Entity*>>
     *
     *  We need to know the active state so that we can easily expose an instantiate method
     *  in this class that will create a new given entity (preferably with a template) for the
     *  active state.
     *
     *  States will query this world object to know about all the entities it contains.
     *  States will also use this object to create/destroy entities.
     *
     */
private:
    pure::StateManager m_stateManager;
    std::unordered_map<pure::State*, std::vector<UEntity_Ptr>> m_entities;
    pure::State* m_currentState;
};


#endif //GALAGA_WORLD_H
