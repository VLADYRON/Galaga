//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_RECT_H
#define GALAGA_RECT_H

struct SDL_Rect;

struct Rect
{
    float x, y;
    float w, h;

    explicit operator SDL_Rect() const;

    bool isOutside(const glm::vec2& point) const;

    bool isInside(const glm::vec2& point) const;

    float right() const;
    float bottom() const;
};

#endif //GALAGA_RECT_H
