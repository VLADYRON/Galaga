//
// Created by matt on 4/9/18.
//

#ifndef GALAGA_ALIEN_H
#define GALAGA_ALIEN_H


#include "SpaceEntity.h"
#include "../Util/SplinePath.h"

class Alien : public SpaceEntity
{
public:
    explicit Alien(World& world);

    void setDivepath(std::vector<Spline::Node> path);
    void update(float deltaTime) final;

private:
    float m_speed;
    SplinePath m_divePath;
};


#endif //GALAGA_ALIEN_H
