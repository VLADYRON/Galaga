//
// Created by matt on 3/30/18.
//

#include "Spaceship.h"
#include "../Game/Rect.h"

void Spaceship::draw(SDL_Renderer *renderer) const
{
    assert(m_sprite.textureRect != std::nullopt);
    SDL_Rect drawRect = getBoundingRect();

    SDL_RenderCopyEx(
        renderer,
        m_sprite.texture->getHandle(),
        &*m_sprite.textureRect,
        &drawRect,
        getTransform().rotation,
        nullptr,
        SDL_FLIP_NONE
    );
}

void Spaceship::setTextureRect(const SDL_Rect &rect) { m_sprite.textureRect = rect; }
void Spaceship::setTexture(pure::Texture *texture) { m_sprite.texture = texture; }

void Spaceship::setSize(const glm::vec2 &size) { m_sprite.size = size; }
glm::vec2 Spaceship::getSize() const { return m_sprite.size; }

Rect Spaceship::getBoundingRect() const
{
    return { getTopLeft().x, getTopLeft().y, m_sprite.size.x, m_sprite.size.y };
}

glm::vec2 Spaceship::getCenterPos() const
{
    return getTopLeft() + (getSize() / 2.f);
}

void Spaceship::fireMissle()
{
    // TODO: Implement Me
}





