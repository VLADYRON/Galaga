//
// Created by matt on 4/26/18.
//

#ifndef GALAGA_EXPLOSION_H
#define GALAGA_EXPLOSION_H


#include <Pure2D/Renderables/Animator.h>
#include "SpaceEntity.h"

class Explosion : public SpaceEntity
{
public:

    Explosion();

    void activate() final;
    void deactivate() final;

    void setAnim(uint32_t numAnims, SDL_Rect start, glm::vec2 offset);

private:
    pure::Animator<Explosion> m_anim;
};


#endif //GALAGA_EXPLOSION_H
