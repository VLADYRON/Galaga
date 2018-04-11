//
// Created by matt on 3/26/18.
//

#ifndef GALAGA_TRANSFORM_H
#define GALAGA_TRANSFORM_H

#include <glm/vec2.hpp>

struct Transform
{
    Transform();

    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 origin;
    float rotation;
};


#endif //GALAGA_TRANSFORM_H
