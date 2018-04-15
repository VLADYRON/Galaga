//
// Created by matt on 4/9/18.
//

#ifndef GALAGA_ALIEN_H
#define GALAGA_ALIEN_H


#include "SpaceEntity.h"
#include "../Splines/SplinePath.h"

class Alien : public SpaceEntity
{
public:

    static constexpr float minStopDist = 2.f;

    explicit Alien();

    bool isDiving() const;

    void setDivePath(std::vector<Spline::Node> path, bool begin = true);
    void startDivePath();
    void update(float deltaTime) final;


private:
    float m_speed;
    bool m_isDiving;

    SplinePath m_divePath;
};


#endif //GALAGA_ALIEN_H
