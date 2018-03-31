//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_SPACESHIP_H
#define GALAGA_SPACESHIP_H

#include <Pure2D/Renderables/Texture.h>
#include "Entity.h"
#include "../Components/SpriteComponent.h"

struct Rect;

class Spaceship : public Entity
{
public:
    explicit Spaceship(World& world);
    void setTextureRect(const SDL_Rect& rect);
    void setTexture(pure::Texture* texture);

    glm::vec2 getSize() const;
    void setSize(const glm::vec2& size);

    Rect getBoundingRect() const;
    glm::vec2 getCenterPos() const;

    void fireMissle();

private:
    SpriteComponent m_sprite;

    void draw(SDL_Renderer* renderer) const final;
};


#endif //GALAGA_SPACESHIP_H
