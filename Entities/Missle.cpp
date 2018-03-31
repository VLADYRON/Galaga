//
// Created by matt on 3/30/18.
//

#include "Missle.h"

void Missle::draw(SDL_Renderer *renderer) const
{

}

void Missle::setTextureRect(const SDL_Rect &rect) { m_sprite.textureRect = rect; }
void Missle::setTexture(pure::Texture *texture) { m_sprite.texture = texture; }
