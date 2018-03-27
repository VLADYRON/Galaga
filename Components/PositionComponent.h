//
// Created by matt on 3/26/18.
//

#ifndef GALAGA_POSITIONCOMPONENT_H
#define GALAGA_POSITIONCOMPONENT_H

#include <glm/vec2.hpp>
#include "Component.h"

struct TransformComponent : public Component
{
    explicit TransformComponent(pure::uint32 entity);

    glm::vec2 position;
    glm::vec2 velocity;
    float rotation;
};


#endif //GALAGA_POSITIONCOMPONENT_H
