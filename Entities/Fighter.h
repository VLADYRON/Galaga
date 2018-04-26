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
    explicit Fighter();

    void setWorld(World& world);

    void fireMissile();

    Rect collilderRect() const;

private:
    World* m_world;
};


#endif //GALAGA_FIGHTER_H
