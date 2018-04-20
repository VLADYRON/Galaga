//
// Created by matt on 4/8/18.
//

#include "Spline.h"
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>

Spline::Spline(float stepSize, std::vector<Spline::Node> points):
    m_stepSize(stepSize)
{
    setPoints(std::move(points));
    if (!m_points.empty()) calcLengths();
}

glm::vec2 Spline::getPoint(float t) const
{

    int p0, p1, p2, p3;

    p1 = (int)t + 1;
    p2 = p1 + 1;
    p3 = p2 + 1;
    p0 = p1 - 1;


    t = t - (int)t;

    const float tt = t * t;
    const float ttt = tt * t;

    float q1 = -ttt + 2.0f*tt - t;
    float q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
    float q3 = -3.0f*ttt + 4.0f*tt + t;
    float q4 = ttt - tt;

    const float tx = 0.5f * (m_points[p0].pos.x * q1 + m_points[p1].pos.x * q2 + m_points[p2].pos.x * q3 + m_points[p3].pos.x * q4);
    const float ty = 0.5f * (m_points[p0].pos.y * q1 + m_points[p1].pos.y * q2 + m_points[p2].pos.y * q3 + m_points[p3].pos.y * q4);

    return{ tx, ty };
}

glm::vec2 Spline::getGradient(float t) const
{
    int p0, p1, p2, p3;

    p1 = (int)t + 1;
    p2 = p1 + 1;
    p3 = p2 + 1;
    p0 = p1 - 1;

    t = t - (int)t;

    const float tt = t * t;

    float q1 = -3.f * tt + 4.f * t - 1.f;
    float q2 = 9.f * tt - 10.f * t;
    float q3 = -9.f * tt + 8.f * t + 1.f;
    float q4 = 3.f * tt - 2.f * t;

    const float tx = 0.5f * (m_points[p0].pos.x * q1 + m_points[p1].pos.x * q2 + m_points[p2].pos.x * q3 + m_points[p3].pos.x * q4);
    const float ty = 0.5f * (m_points[p0].pos.y * q1 + m_points[p1].pos.y * q2 + m_points[p2].pos.y * q3 + m_points[p3].pos.y * q4);

    return{ tx, ty };
}

float Spline::length() const { return m_length; }

void Spline::setPoints(std::vector<Spline::Node> points)
{
    m_points = std::move(points);
    calcLengths();
}

void Spline::setPoint(uint32_t  index, Spline::Node point)
{
    assert(index < m_points.size() && index >= 0);
    m_points[index] = point;
    calcLengths();
}

float Spline::calcNodeLength(uint32_t node) const
{
    float length = 0.f;
    float temp = 0.f;

    glm::vec2 oldPoint, newPoint;
    oldPoint = getPoint((float)node);

    for (float t = 0; t < 1.f; t += m_stepSize)
    {
        newPoint = getPoint((float)node + t);

        length += glm::length(newPoint - oldPoint);

        oldPoint = newPoint;
    }

    return length;
}

float Spline::getOffset(float pos) const
{
    int i = 0;

    while(pos > m_points[i].length)
    {
        pos -= m_points[i].length;
        i++;
    }

    return (float)i + (pos / m_points[i].length);

}

void Spline::calcLengths()
{
    m_length = 0;
    if (m_points.empty()) return;
    for (size_t i = 0; i < m_points.size() - 3; i++)
    {
        const float segSize = (m_points[i].length = calcNodeLength(i));
        m_length += segSize;
    }
}

float Spline::clampPos(float pos) const
{

    if (pos >= m_length) return pos - m_length;
    if (pos < 0.f) return pos + m_length;

    return pos;
}

float Spline::stepSize() const { return m_stepSize; }
void Spline::setStepSize(float step)
{
    m_stepSize = step;
    calcLengths();
}


Spline::Node::Node(glm::vec2 pos):
    pos(pos)
{ }
