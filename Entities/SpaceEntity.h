//
// Created by matt on 4/9/18.
//

#ifndef GALAGA_SPACEENTITY_H
#define GALAGA_SPACEENTITY_H


#include <Pure2D/Renderables/Texture.h>
#include "Entity.h"
#include "../Components/Sprite.h"

struct Rect;

class SpaceEntity : public Entity, public pure::Renderable
{
public:
    explicit SpaceEntity(World& world);
    virtual ~SpaceEntity() = 0;
    void setTextureRect(const SDL_Rect& rect);
    void setTexture(pure::Texture* texture);

    glm::vec2 getSize() const;
    void setSize(const glm::vec2& size);

    Rect getBoundingRect() const;
    glm::vec2 getCenterPos() const;


protected:
    Sprite m_sprite;

    void draw(SDL_Renderer* renderer) const final;
};


#endif //GALAGA_SPACEENTITY_H
