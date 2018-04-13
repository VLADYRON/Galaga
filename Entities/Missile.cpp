//
// Created by matt on 3/30/18.
//

#include <iostream>
#include <cmath>
#include <glm/ext.hpp>
#include "Missile.h"
#include "../Game/World.h"

Missile::Missile()
{
    setSize({ 50, 50 });
    setOrigin(getSize() / 2.f);
    setVelocity({ 0, 350 });
}

void Missile::draw(SDL_Renderer *renderer) const
{
    m_sprite.draw(renderer, getTransform());
}

void Missile::setTextureRect(const SDL_Rect &rect) { m_sprite.textureRect = rect; }
void Missile::setTexture(pure::Texture *texture) { m_sprite.texture = texture; }

void Missile::setSize(const glm::vec2 &size) { m_sprite.size = size; }
glm::vec2 Missile::getSize() const { return m_sprite.size; }

void Missile::update(float deltaTime)
{
    move({ 0.f, -std::round(getVelocity().y * deltaTime) });
}

