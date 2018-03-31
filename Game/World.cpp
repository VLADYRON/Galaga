//
// Created by matt on 3/30/18.
//

#include "../Entities/Entity.h"
#include "World.h"


using namespace pure;

World::World(pure::Window& window):
    m_stateManager(window),
    m_entities(),
    m_currentState(nullptr)
{
    m_stateManager.setOnStatePush([this](State& oldState, State& newState) {
        if (&oldState == &newState) return;

        m_currentState = &newState;
    });
}

const std::vector<World::UEntity_Ptr> &World::getEntities(pure::State *state) { return m_entities[state]; }

bool World::destroy(Entity &entity, pure::State* state)
{
    if (!state) state = m_currentState;

    std::vector<UEntity_Ptr>& stateEntities = m_entities[state];
    auto itr = std::find_if(stateEntities.begin(), stateEntities.end(), [&entity](UEntity_Ptr& e) {
        return e.get() == &entity;
    });

    if (itr == stateEntities.end()) return false;

    stateEntities.erase(itr);
    return true;
}
