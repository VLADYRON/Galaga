//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_MISSLE_H
#define GALAGA_MISSLE_H

#include <Pure2D/Renderables/Renderable.h>
#include "Entity.h"
#include "../Components/SpriteComponent.h"

namespace pure
{
    class Texture;
}

class Missle : public Entity
{

    void setTextureRect(const SDL_Rect& rect);
    void setTexture(pure::Texture* texture);

private:
    void draw(SDL_Renderer* renderer) const final;
    SpriteComponent m_sprite;
};


#endif //GALAGA_MISSLE_H
