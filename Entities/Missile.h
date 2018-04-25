//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_MISSILE_H
#define GALAGA_MISSILE_H

#include <Pure2D/Renderables/Renderable.h>
#include "../Components/Sprite.h"
#include "SpaceEntity.h"

namespace pure
{
    class Texture;
}

class Missile : public SpaceEntity
{
public:
    explicit Missile();
    void update(float deltaTime) final;
    Rect colliderRect() const;

private:
};


#endif //GALAGA_MISSILE_H
