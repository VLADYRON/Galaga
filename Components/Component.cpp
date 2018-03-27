//
// Created by matt on 3/25/18.
//

#include "Component.h"

Component::Component(pure::uint32 entity):
    m_entity(entity)
{ }

Component::~Component() { }

pure::uint32 Component::getEntity() const
{
    return m_entity;
}
