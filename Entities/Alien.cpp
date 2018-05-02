//
// Created by matt on 4/9/18.
//

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <Pure2D/Util/Constants.h>
#include "Alien.h"
#include "../Util/Rect.h"
#include "../Util/TextureManager.h"
#include "../Game/AssetPaths.h"
#include "../Util/SpriteMap.h"

constexpr float minStopDist = 3.f;

Alien::Alien():
        m_speed(350.f),
        m_behavior(nullptr),
        m_anim(*this),
        m_health(1)
{
    setSize({ 50, 50 });
    setOrigin(getSize() / 2.f);
    m_divePath.setOnDone([this]() { m_state = Alien::State::DIVE_END; });
}

void Alien::update(float deltaTime)
{
    switch(state())
    {
        case State::IDLE: handleIdleState(); break;
        case State::DIVING: handleDivingState(); break;
        case State::DIVE_END: handleDiveEndState(); break;
        case State::IN_FORMATION: handleInFormationState(); break;
    }


    if (!m_divePath.isDone())
    {
        SplinePath::ResultPoint rp = m_divePath.getNextStep(deltaTime * m_speed);

        setPosition(rp.pos);
        setRotation(rp.forwardRotation);
    }
    else
    {
        if (m_isBehaviorActive && m_behavior != nullptr)
            m_behavior(*this, deltaTime);
    }
}

void Alien::setDivePath(std::vector<Spline::Node> path, bool begin)
{
    m_divePath.setPath(std::move(path), begin);
    m_state = Alien::State::DIVING;
}

void Alien::startDivePath()
{
    m_divePath.startPath();
    m_state = Alien::State::DIVING;
}

bool Alien::isDiving() const { return !m_divePath.isDone(); }

void Alien::setFormationPos(FormationPosition cell) { m_formationPos = cell; }
FormationPosition Alien::formationPos() const { return m_formationPos; }

void Alien::setBehavior(Alien::AlienBehavior behavior) { m_behavior = std::move(behavior); }
void Alien::startBehavior() { m_isBehaviorActive = true; }
void Alien::endBehavior() { m_isBehaviorActive = false; }
float Alien::speed() const { return m_speed; }

Alien::State Alien::state() const { return m_state; }

void Alien::setState(Alien::State state)
{
    // we don't want state changed from outside if we are currently diving
    if (m_state != Alien::State::DIVING)
        m_state = state;
}

Rect Alien::colliderRect() const
{
    Rect collider{};
    glm::vec2 pos = position();
    // TODO: Look into alternatives to switch statement... this is pretty ugg
    switch (type())
    {
        case SpriteType::BEE:
        case SpriteType::MOTH:
            collider.x = pos.x - 15;
            collider.y = pos.y - 15;
            collider.w = 35;
            collider.h = 33;
            break;
        case SpriteType::CATCHER:
            collider.x = pos.x - 20;
            collider.y = pos.y - 20;
            collider.w = 45;
            collider.h = 45;
            break;
        default:
            std::cout << "Alien has incorrect SpriteType, given: " << static_cast<int>(type()) << std::endl;
    }

    return collider;
}

void Alien::activate()
{
    SpaceEntity::activate();

    pure::Texture* spritesheet = TextureManager::instance().getTexture(paths::GALAGA_SPRITE_SHEET);
    assert(spritesheet != nullptr);

    setTexture(spritesheet);
    SDL_Rect textureRect{};

    switch (type())
    {
        case SpriteType::BEE:
            textureRect = spritemap::BEE_OPEN;
            break;
        case SpriteType::MOTH:
            textureRect = spritemap::MOTH_OPEN;
            break;
        case SpriteType::CATCHER:
            textureRect = spritemap::CATCHER_TURQUOISE_OPEN;
            m_health = Health(2);
            break;
        default:
            std::cout << "Given spritetype not defined for set function of type Alien" << std::endl;
    }


    setTextureRect(textureRect);
    m_anim.setAnimOpts(2, textureRect, { spritemap::SIZE, 0 });
    m_health.reset();
}

int Alien::health() const { return m_health.get(); }

void Alien::takeDamage() { m_health.takeDamage(1); }

pure::Animator<Alien>* const Alien::animator() { return &m_anim; }

