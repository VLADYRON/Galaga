//
// Created by matt on 4/9/18.
//

#include "SpaceEntity.h"
#include <optional>
#include "../Util/Rect.h"

SpaceEntity::~SpaceEntity() { }

void SpaceEntity::draw(SDL_Renderer *renderer) const
{
    assert(m_sprite.textureRect != std::nullopt);

    m_sprite.draw(renderer, getTransform());
//    auto rect = static_cast<SDL_Rect>(getBoundingRect());
}

void SpaceEntity::setTextureRect(const SDL_Rect &rect) { m_sprite.textureRect = rect; }
void SpaceEntity::setTexture(pure::Texture *texture) { m_sprite.texture = texture; }

void SpaceEntity::setSize(const glm::vec2 &size) { m_sprite.size = size; }
glm::vec2 SpaceEntity::getSize() const { return m_sprite.size; }

Rect SpaceEntity::getBoundingRect() const
{
    return { getTopLeft().x, getTopLeft().y, m_sprite.size.x, m_sprite.size.y };
}

glm::vec2 SpaceEntity::getCenterPos() const
{
    return getTopLeft() + (getSize() / 2.f);
}

SDL_Rect SpaceEntity::textureRect() const
{
    if (m_sprite.textureRect == std::nullopt) return {};
    return *m_sprite.textureRect;
}

