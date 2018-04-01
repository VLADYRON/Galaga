//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_RECT_H
#define GALAGA_RECT_H

#include <SDL2/SDL_rect.h>

struct Rect
{
    float x, y;
    float w, h;

    explicit operator SDL_Rect() const { return { (int)x, (int)y, (int)w,(int) h }; }

    bool isOutside(const glm::vec2& point);

    bool isInside(const glm::vec2& point);
};

#endif //GALAGA_RECT_H
