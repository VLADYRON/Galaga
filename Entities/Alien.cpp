//
// Created by matt on 4/9/18.
//

#include <iostream>
#include "Alien.h"

Alien::Alien(World &world):
        SpaceEntity(world),
        m_speed(350.f)
{
    setSize({ 50, 50 });
    setOrigin(getSize() / 2.f);

    m_divePath.setOnDone([](){ std::cout << "PATH END" << std::endl; });
}

void Alien::update(float deltaTime)
{
    if (!m_divePath.isDone())
    {
        SplinePath::ResultPoint rp = m_divePath.getNextStep(deltaTime * m_speed);

        setPosition(rp.pos);
        setRotation(rp.forwardRotation);
    }
}

void Alien::setDivepath(std::vector<Spline::Node> path)
{
    m_divePath.setPath(std::move(path));
}

