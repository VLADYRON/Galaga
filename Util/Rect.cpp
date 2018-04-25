//
// Created by matt on 3/31/18.
//

#include <glm/vec2.hpp>
#include "Rect.h"
#include <SDL2/SDL_rect.h>


bool Rect:: isOutside(const glm::vec2 &point) const
{
    return (
        (point.x < x) || (point.y < y) || (point.x > (x + w)) || (point.y > (y + h))
    );
}

bool Rect::isInside(const glm::vec2 &point) const
{
    return (
        (point.x > x) && (point.y > y) && (point.x < (w + x)) && (point.y < (h + y))
    );
}

Rect::operator SDL_Rect() const
{
    return {
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(w),
        static_cast<int>(h)
    };
}

float Rect::right() const { return x + w; }
float Rect::bottom() const { return y + h; }

bool Rect::doesCollide(const Rect &other) const
{
    return (
        (x < other.right()) && (right() > other.x) && (y < other.bottom()) && (bottom() > other.y)
    );
}

bool Rect::doesCollide(const SDL_Rect &other) const
{
    Rect r = {
        static_cast<float>(other.x),
        static_cast<float>(other.y),
        static_cast<float>(other.w),
        static_cast<float>(other.h)
    };
    return doesCollide(r);
}
