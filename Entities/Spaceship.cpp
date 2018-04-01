//
// Created by matt on 3/30/18.
//

#include "Spaceship.h"
#include "../Game/World.h"
#include "../Util/Rect.h"
#include "Missile.h"
#include "../Util/Defaults.h"
#include <Pure2D/Util/Convert.h>

Spaceship::Spaceship(World &world)
    : Entity(world)
{
    setSize({ 50, 50 });
    setOrigin(getSize() / 2.f);
    setVelocity({ 250, 0 });
}

void Spaceship::draw(SDL_Renderer *renderer) const
{
    assert(m_sprite.textureRect != std::nullopt);

    m_sprite.draw(renderer, getTransform());
    SDL_Rect rect = (SDL_Rect)getBoundingRect();
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

void Spaceship::fireMissile()
{
    glm::vec2 shipPos = getPosition();
    glm::vec2 firePos = { shipPos.x, shipPos.y - getSize().y / 2.f };
    auto& m = m_world->instantiate<Missile>(firePos);
    defaults::set(m, SpriteType::MISSLE_PLAYER);
}





