//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_RECT_H
#define GALAGA_RECT_H

struct Rect
{
    float x, y;
    float w, h;

    operator SDL_Rect() const { return { (int)x, (int)y, (int)w,(int) h }; }
};

#endif //GALAGA_RECT_H
