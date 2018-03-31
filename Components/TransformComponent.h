//
// Created by matt on 3/26/18.
//

#ifndef GALAGA_TRANSFORMCOMPONENT_H
#define GALAGA_TRANSFORMCOMPONENT_H

#include <glm/vec2.hpp>

struct TransformComponent
{
    TransformComponent();

    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 origin;
    float rotation;
};


#endif //GALAGA_TRANSFORMCOMPONENT_H
