//
// Created by matt on 3/30/18.
//

#include <iostream>
#include "Entity.h"

Entity::~Entity() { }

const Transform& Entity::getTransform() const { return m_transform; }
void Entity::setTransform(const Transform &transform) { m_transform = transform; }

glm::vec2 Entity::getPosition() const { return m_transform.position + m_transform.origin; }
void Entity::setPosition(const glm::vec2 &position) { m_transform.position = position - m_transform.origin; }

const glm::vec2 &Entity::getVelocity() const { return m_transform.velocity; }
void Entity::setVelocity(const glm::vec2 &velocity) { m_transform.velocity = velocity; }

float Entity::getRotation() const { return m_transform.rotation; }
void Entity::setRotation(float rotation) { m_transform.rotation = rotation; }

void Entity::move(const glm::vec2 &position) { m_transform.position += position; }

const glm::vec2& Entity::getOrigin() const { return m_transform.origin; }
void Entity::setOrigin(const glm::vec2 &origin)
{
    // make sure SDL position stays in sync with origin
    m_transform.position -= origin;

    m_transform.origin = origin;
}

glm::vec2 Entity::getTopLeft() const { return m_transform.position; }



