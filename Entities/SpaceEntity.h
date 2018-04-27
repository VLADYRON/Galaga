//
// Created by matt on 4/9/18.
//

#ifndef GALAGA_SPACEENTITY_H
#define GALAGA_SPACEENTITY_H


#include <Pure2D/Renderables/Texture.h>
#include "Entity.h"
#include "../Components/Sprite.h"

struct Rect;

class SpaceEntity : public Entity, public pure::Renderable, public LifeCycle
{
public:
    SpaceEntity() = default;

    bool isActive() const;

    SDL_Rect textureRect() const;
    void setTextureRect(const SDL_Rect& rect);

    virtual void setTexture(pure::Texture* texture);

    virtual glm::vec2 getSize() const;
    void setSize(const glm::vec2& size);

    Rect getBoundingRect() const;
    glm::vec2 getCenterPos() const;

    void activate() override;
    void deactivate() override;

protected:
    Sprite m_sprite;
    bool m_isActive = false;

    void draw(SDL_Renderer* renderer) const final;
};


#endif //GALAGA_SPACEENTITY_H
