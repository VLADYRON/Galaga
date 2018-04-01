//
// Created by matt on 3/31/18.
//

#include <glm/vec2.hpp>
#include "Rect.h"

bool Rect::isOutside(const glm::vec2 &point)
{
    return (
        (point.x < x) || (point.y < y) || (point.x > (x + w)) || (point.y > (y + h))
    );
}

bool Rect::isInside(const glm::vec2 &point)
{
    return (
        (point.x > x) && (point.y > y) && (point.x < (w + x)) && (point.y < (h + y))
    );
}
