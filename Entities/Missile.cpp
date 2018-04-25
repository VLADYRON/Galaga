//
// Created by matt on 3/30/18.
//

#include <iostream>
#include <cmath>
#include <glm/ext.hpp>
#include "Missile.h"
#include "../Game/World.h"
#include "../Util/Rect.h"

Missile::Missile()
{
    setSize({ 50,50 });
    setOrigin(getSize() / 2.f);
    setVelocity({ 0, 750 });
}

void Missile::update(float deltaTime)
{
    move({ 0.f, -std::round(getVelocity().y * deltaTime) });
}

Rect Missile::colliderRect() const
{
    return {
        getPosition().x - 3,
        getPosition().y - 15,
        10,
        28
    };
}

