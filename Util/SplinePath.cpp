//
// Created by matt on 4/9/18.
//

#include "SplinePath.h"
#include <cmath>

SplinePath::SplinePath():
    m_isDone(true),
    m_pos(0.f),
    m_onStart(nullptr),
    m_onDone(nullptr)
{ }

bool SplinePath::isDone() const { return m_isDone; }

void SplinePath::startPath()
{
    if (m_onStart) m_onStart();
    m_isDone = false;
}

SplinePath::ResultPoint SplinePath::getNextStep(float stepSize)
{

    float nextPos = m_pos + stepSize;

    if (nextPos >= m_path.length() || m_isDone)
    {
        m_isDone = true;
        if (m_onDone) m_onDone();
        // don't move and keep last position if next position would be
        // greater than the length of the spline or we are done
        nextPos = m_pos;
    }
    else
    {
        m_pos = nextPos;
    }

    const float offset = m_path.getOffset(nextPos);
    glm::vec2 pos = m_path.getPoint(offset);
    glm::vec2 gradient = m_path.getGradient(offset);
    const float deg = std::atan2(gradient.y, gradient.x);
    float angle = (deg * 180.f / 3.14f) + 90.f;

    if (angle < 0)
        angle = 360 + angle;

    return { pos, angle };

}

void SplinePath::setPath(std::vector<Spline::Node> path, bool begin)
{
    m_path.setPoints(std::move(path));
    if (begin) startPath();
}

void SplinePath::setOnStart(SplinePath::PathAction callback) { m_onStart = callback; }
void SplinePath::setOnDone(SplinePath::PathAction callback) { m_onDone = callback; }

