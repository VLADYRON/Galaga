//
// Created by matt on 3/25/18.
//

#ifndef GALAGA_ECS_H
#define GALAGA_ECS_H

#include <Pure2D/Util/Constants.h>
#include <typeindex>
#include <unordered_map>
#include <memory>
#include <vector>
#include <Pure2D/Util/NonCopyable.h>
#include "ComponentType.h"
#include "../typedefs.h"

// TODO: Maybe implement Components as a pool instead of creating them on
// the fly at runtime in a map?

// TODO: Implement a way to remove components

class ECS final : public pure::NonCopyable
{
public:


    using Entity = pure::uint32;

    static ECS& getInstance();

    Entity createEntity();

    bool attachComponent(Entity entity, Uptr_Component component);

    std::vector<Component*> getComponents(Entity entity);

    void addSystem(Uptr_System system);

    template<typename T>
    T* getComponent(Entity entity)
    {
        auto entityItr = m_entities.find(entity);
        if (entityItr != m_entities.end())
        {
            Entity_& e = entityItr->second;
            std::type_index typeIndex(typeid(T));

            auto componentItr = e.components.find(typeIndex);
            if (componentItr != e.components.end())
                return static_cast<T*>(componentItr->second.get());
        }

        return nullptr;
    }

private:
    using ComponentMap = std::unordered_map<std::type_index, Uptr_Component>;

    ECS() = default;

    // helper struct for dealing with entities internally
    struct Entity_
    {
        pure::uint32 id;
        ComponentType mask;
        ComponentMap components;
    };

    std::unordered_map<pure::uint32, Entity_> m_entities;
    std::vector<Uptr_System> m_systems;
};


#endif //GALAGA_ECS_H
