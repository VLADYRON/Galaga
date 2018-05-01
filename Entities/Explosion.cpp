//
// Created by matt on 4/26/18.
//

#include <iostream>
#include "Explosion.h"
#include "../Util/TextureManager.h"
#include "../Util/SpriteMap.h"
#include "../Game/AssetPaths.h"


Explosion::Explosion():
    m_anim(*this)
{
    setSize({ 100, 85 });
    setOrigin(getSize() / 2.f);
}

void Explosion::setAnim(uint32_t numAnims, SDL_Rect start, glm::vec2 offset)
{
    m_anim.setAnimOpts(numAnims, start, offset);
    m_anim.setDelay(0.05f);
}

void Explosion::update(float deltaTime)
{
    if (!isDone()) m_anim.timedStep();
}

bool Explosion::isDone() const { return m_anim.hasCompletedCycle(); }

void Explosion::activate()
{
    SpaceEntity::activate();

    pure::Texture* spritesheet = nullptr;

    if (type() == SpriteType::EXPLOSION_ALIEN)
    {
        spritesheet = TextureManager::instance().getTexture(paths::ALIEN_EXPLOSION);
        setAnim(4, spritemap::ALIEN_EXPLOSION, { spritemap::ALIEN_EXPLOSION_SIZE, 0 });

    }
    else if(type() == SpriteType::EXPLOSION_FIGHTER)
    {
        spritesheet = TextureManager::instance().getTexture(paths::GALAGA_SPRITE_SHEET);
        setAnim(4, spritemap::FIGHTER_EXPLOSION_BEGIN, { spritemap::FIGHTER_EXPLOSION_SIZE, 0 });
    }

    assert(spritesheet != nullptr);
    setTexture(spritesheet);
}
