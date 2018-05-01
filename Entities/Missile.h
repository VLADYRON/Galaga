//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_MISSILE_H
#define GALAGA_MISSILE_H

#include <Pure2D/Renderables/Renderable.h>
#include "../Components/Sprite.h"
#include "SpaceEntity.h"
#include "SpriteType.h"

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

    void activate() override;

private:
    SpriteType m_type;

};


#endif //GALAGA_MISSILE_H
