//
// Created by matt on 4/9/18.
//

#ifndef GALAGA_ALIEN_H
#define GALAGA_ALIEN_H


#include "SpaceEntity.h"
#include "../Splines/SplinePath.h"
#include "../Util/Defaults.h"
#include "../Components/GroupCell.h"

class Alien : public SpaceEntity
{
public:

    explicit Alien();

    void setType(SpriteType type);
    SpriteType type() const;

    void setGroupCell(GroupCell cell);
    GroupCell groupCell() const;

    bool isDiving() const;

    void setDivePath(std::vector<Spline::Node> path, bool begin = true);
    void startDivePath();
    void update(float deltaTime) final;


private:
    float m_speed;
    bool m_isDiving;
    SpriteType m_type;
    GroupCell m_groupCell;

    SplinePath m_divePath;
};


#endif //GALAGA_ALIEN_H
