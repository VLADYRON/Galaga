//
// Created by matt on 4/9/18.
//

#ifndef GALAGA_ALIEN_H
#define GALAGA_ALIEN_H


#include "SpaceEntity.h"
#include <functional>
#include <vector>
#include <Pure2D/Renderables/Animator.h>
#include "../Splines/SplinePath.h"
#include "../Components/FormationPosition.h"
#include "SpriteType.h"
#include "../Components/Health.h"


class Alien : public SpaceEntity
{
public:
    enum class State
    {
        IDLE,
        DIVING,
        DIVE_END,
        IN_FORMATION
    };

    using AlienBehavior = std::function<void(Alien&, float)>;

    explicit Alien();
    virtual ~Alien() = default;

    bool isDiving() const;

    void setBehavior(AlienBehavior behavior);

    void startBehavior();
    void endBehavior();

    void setFormationPos(FormationPosition cell);
    FormationPosition formationPos() const;

    int health() const;
    void takeDamage();

    pure::Animator<Alien>* const animator();

    void setState(State state);
    State state() const;

    float speed() const;

    Rect colliderRect() const;

    void setDivePath(std::vector<Spline::Node> path, bool begin = true);
    void startDivePath();
    void update(float deltaTime) final;

    void activate() final;


protected:
    float m_speed;
    State m_state;
    bool m_isBehaviorActive;

    pure::Animator<Alien> m_anim;
    SpriteType m_type;
    AlienBehavior m_behavior;
    FormationPosition m_formationPos;
    Health m_health;

    SplinePath m_divePath;

    virtual void handleIdleState() { };
    virtual void handleInFormationState() { }
    virtual void handleDivingState() = 0;
    virtual void handleDiveEndState() = 0;

};


#endif //GALAGA_ALIEN_H
