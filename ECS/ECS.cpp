//
// Created by matt on 3/25/18.
//

#include "ECS.h"
#include "../Systems/System.h"
#include "../Components/Component.h"
#include <unordered_map>
#include <memory>

Entity ECS::createEntity()
{
    static pure::uint32 idCounter = 0;
    Entity_ e;
    e.id = ++idCounter;

    auto insertItr = m_entities.emplace(e.id, std::move(e)).first;

    return idCounter;
}


bool ECS::attachComponent(Entity entity, Uptr_Component component)
{
    auto entityItr = m_entities.find(entity);
    if (entityItr == m_entities.end()) return false;

    Entity_& e = entityItr->second;
    e.mask |= component->getType();

    for (auto& sys : m_systems)
    {
        if ((sys->getMask() & e.mask) == sys->getMask())
            sys->registerEntity(e.id);
    }

    ComponentMap& cmpMap = e.components;

    cmpMap.emplace(std::type_index(typeid(*component)), std::move(component));
    return true;
}

void ECS::addSystem(Uptr_System system)
{
    m_systems.push_back(std::move(system));
}

std::vector<Component *> ECS::getComponents(Entity entity)
{
    std::vector<Component*> components;

    auto entityItr = m_entities.find(entity);
    if (entityItr == m_entities.end()) return components;

    Entity_& e = entityItr->second;

    components.reserve(e.components.size());

    for (auto& pair: e.components)
        components.push_back(pair.second.get());

    return components;
}

ECS &ECS::getInstance()
{
    static ECS ecs;
    return ecs;
}


