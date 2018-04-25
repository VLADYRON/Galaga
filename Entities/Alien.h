//
// Created by matt on 4/9/18.
//

#ifndef GALAGA_ALIEN_H
#define GALAGA_ALIEN_H


#include "SpaceEntity.h"
#include <functional>
#include "../Splines/SplinePath.h"
#include "../Util/Defaults.h"
#include "../Components/GroupCell.h"


class Alien : public SpaceEntity
{
public:
    enum class State
    {
        Idle,
        Diving,
        DiveEnd,
        InFormation
    };

    using AlienBehavior = std::function<void(Alien&, float)>;

    explicit Alien();

    void setBehavior(AlienBehavior behavior);

    void startBehavior();
    void endBehavior();

    void setType(SpriteType type);
    SpriteType type() const;

    void setGroupCell(GroupCell cell);
    GroupCell groupCell() const;

    void setState(State state);
    State state() const;

    float speed() const;

    Rect colliderRect() const;

    void setDivePath(std::vector<Spline::Node> path, bool begin = true);
    void startDivePath();
    void update(float deltaTime) final;


private:
    float m_speed;
    State m_state;
    bool m_isBehaviorActive;
    SpriteType m_type;
    AlienBehavior m_behavior;
    GroupCell m_groupCell;

    SplinePath m_divePath;
};


#endif //GALAGA_ALIEN_H
