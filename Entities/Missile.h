//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_MISSILE_H
#define GALAGA_MISSILE_H

#include <Pure2D/Renderables/Renderable.h>
#include "Entity.h"
#include "../Components/Sprite.h"

namespace pure
{
    class Texture;
}

class Missile : public Entity, public pure::Renderable
{
public:
    explicit Missile(World& world);
    void setTextureRect(const SDL_Rect& rect);
    void setTexture(pure::Texture* texture);

    void setSize(const glm::vec2 &size);
    glm::vec2 getSize() const;

    void update(float deltaTime) final;

private:
    void draw(SDL_Renderer* renderer) const final;
    Sprite m_sprite;
};


#endif //GALAGA_MISSILE_H
