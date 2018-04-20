//
// Created by matt on 4/8/18.
//

#ifndef GALAGA_SPLINE_H
#define GALAGA_SPLINE_H

#include <vector>
#include <glm/vec2.hpp>

/**
 * Thanks to OneLoneCoder for this implementation of Splines!
 * https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_Splines2.cpp
 */

class Spline
{
public:
    struct Node
    {
        glm::vec2 pos;
        float length;

        explicit Node(glm::vec2 pos = glm::vec2());
    };

    explicit Spline(float stepSize = 0.005f, std::vector<Node> points = std::vector<Node>());

    float getOffset(float pos) const;
    glm::vec2 getPoint(float t) const;
    glm::vec2 getGradient(float t) const;
    float length() const;

    float stepSize() const;
    void setStepSize(float step);

    float clampPos(float pos) const;

    void setPoints(std::vector<Node> points);
    void setPoint(uint32_t index, Node point);

private:
    std::vector<Node> m_points;
    float m_stepSize;
    float m_length;

    float calcNodeLength(uint32_t  node) const;
    void calcLengths();


};


#endif //GALAGA_SPLINE_H
