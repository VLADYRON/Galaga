//
// Created by matt on 3/26/18.
//

#ifndef GALAGA_SPRITECOMPONENT_H
#define GALAGA_SPRITECOMPONENT_H

#include <Pure2D/Renderables/Renderable.h>
#include <memory>
#include "Component.h"

struct SpriteComponent : public Component
{
    explicit SpriteComponent(pure::uint32 entity);
    std::unique_ptr<pure::Renderable> sprite;
};



#endif //GALAGA_SPRITECOMPONENT_H
