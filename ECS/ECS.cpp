//
// Created by matt on 3/25/18.
//

#include "ECS.h"
#include "../Components/Component.h"
#include <unordered_map>
#include <memory>


pure::uint32 ECS::createEntity()
{
    static pure::uint32 idCounter = 0;

    m_entities.emplace(++idCounter, ComponentMap());

    return idCounter;
}

bool ECS::attachComponent(pure::uint32 entity, Uptr_Component& component)
{
    auto entityItr = m_entities.find(entity);
    if (entityItr == m_entities.end()) return false;

    ComponentMap& cmpMap = entityItr->second;

    cmpMap.emplace(std::type_index(typeid(*component)), std::move(component));
    return true;
}

std::vector<Component*> ECS::getComponents(pure::uint32 entity)
{
    std::vector<Component*> components;

    auto entityItr = m_entities.find(entity);
    if (entityItr == m_entities.end()) return components;

    ComponentMap& cmpMap = entityItr->second;

    components.reserve(cmpMap.size());

    for (auto& pair: cmpMap)
        components.push_back(pair.second.get());

    return components;
}

ECS &ECS::getInstance()
{
    static ECS ecs;
    return ecs;
}
