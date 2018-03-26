//
// Created by matt on 3/25/18.
//

#ifndef GALAGA_COMPONENT_H
#define GALAGA_COMPONENT_H


#include <Pure2D/Util/Constants.h>
#include <bitset>

class Component
{

public:
    explicit Component(pure::uint32 entity);
    virtual ~Component() = default;

    pure::uint32 getEntity() const;

protected:

    pure::uint32 m_entity;
};

#endif //GALAGA_COMPONENT_H
