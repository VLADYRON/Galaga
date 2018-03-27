//
// Created by matt on 3/26/18.
//

#ifndef GALAGA_SYSTEM_H
#define GALAGA_SYSTEM_H

#include <vector>
#include "../ECS/ECS.h"

class System
{
public:
    System() = default;
    virtual ~System() = 0;

    virtual ComponentType getMask() const = 0;
    void registerEntity(ECS::Entity entity);

    virtual void update(float deltaTime) { };

protected:
    std::vector<ECS::Entity> m_entities;
};


#endif //GALAGA_SYSTEM_H

