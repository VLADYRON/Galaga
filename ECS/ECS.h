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

class Component;

class ECS final
{
public:
    using Uptr_Component = std::unique_ptr<Component>;
    using ComponentMap = std::unordered_map<std::type_index, Uptr_Component>;

    static ECS& getInstance();

    pure::uint32 createEntity();

    bool attachComponent(pure::uint32 entity, Uptr_Component& component);

    std::vector<Component*> getComponents(pure::uint32 entity);

    template<typename T>
    T* getComponent(pure::uint32 entity)
    {
        auto entityItr = m_entities.find(entity);
        if (entityItr != m_entities.end())
        {
            ComponentMap& cmpMap = entityItr->second;
            std::type_index typeIndex(typeid(T));

            auto componentItr = cmpMap.find(typeIndex);
            if (componentItr != cmpMap.end())
                return static_cast<T*>(componentItr->second.get());
        }

        return nullptr;
    }

private:
    ECS() = default;

    std::unordered_map<pure::uint32, ComponentMap> m_entities;
    std::unordered_map<pure::uint32, int> m_entityMask;
};


#endif //GALAGA_ECS_H
