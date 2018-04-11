//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_FIGHTER_H
#define GALAGA_FIGHTER_H

#include <Pure2D/Renderables/Texture.h>
#include "Entity.h"
#include "../Components/Sprite.h"
#include "SpaceEntity.h"

struct Rect;

class Fighter : public SpaceEntity
{
public:
    explicit Fighter(World& world);

    void fireMissile();
};


#endif //GALAGA_FIGHTER_H
