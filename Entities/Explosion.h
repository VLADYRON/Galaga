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

    bool isDone() const;
    void update(float deltaTime) final;

    void activate() final;

private:
    pure::Animator<Explosion> m_anim;

    void setAnim(uint32_t numAnims, SDL_Rect start, glm::vec2 offset);
};


#endif //GALAGA_EXPLOSION_H
