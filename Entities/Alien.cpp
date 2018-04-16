//
// Created by matt on 4/9/18.
//

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <Pure2D/Util/Constants.h>
#include "Alien.h"

Alien::Alien():
        m_speed(350.f),
        m_isDiving(false)
{
    setSize({ 50, 50 });
    setOrigin(getSize() / 2.f);

}

void Alien::update(float deltaTime)
{
    // TODO: Maybe refactor all this logic for moving along spline into separate component/class
    if (!m_divePath.isDone())
    {
        SplinePath::ResultPoint rp = m_divePath.getNextStep(deltaTime * m_speed);

        setPosition(rp.pos);
        setRotation(rp.forwardRotation);
    }
    else
    {
        // TODO: Maybe have AlienGroup class handle this part...
        if (!m_isDiving) return;
        glm::vec2 dir = m_groupCell.position - getPosition();

        if (glm::length(dir) <= minStopDist)
        {
            setRotation(180.f); // face toward bottom of screen
            setPosition(m_groupCell.position);
            m_isDiving = false;
            return;
        }


        const float rot = (std::atan2(dir.y, dir.x) * pure::RAD_TO_DEG) + 90.f;
        setRotation(rot);

        move(glm::normalize(dir) * m_speed * deltaTime);
    }
}

void Alien::setDivePath(std::vector<Spline::Node> path, bool begin)
{
    if (begin) m_isDiving = true;
    m_divePath.setPath(std::move(path), begin);
}

void Alien::startDivePath()
{
    m_divePath.startPath();
    m_isDiving = true;
}

bool Alien::isDiving() const { return m_isDiving; }

void Alien::setGroupCell(GroupCell cell) { m_groupCell = cell; }
GroupCell Alien::groupCell() const { return m_groupCell; }

void Alien::setType(SpriteType type) { m_type = type; }
SpriteType Alien::type() const { return m_type; }

