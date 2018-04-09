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

    glm::vec2 getPoint(float pos) const;
    glm::vec2 getGradient(float pos) const;
    float length() const;

    float stepSize() const;
    void setStepSize(float step);

    float clampPos(float pos) const;

    void setPoints(std::vector<Node> points);
    void setPoint(size_t index, Node point);

private:
    std::vector<Node> m_points;
    float m_stepSize;
    float m_length;
    float m_tailLength;

    float calcNodeLength(size_t node) const;
    float getOffset(float pos) const;
    void calcLengths();


};


#endif //GALAGA_SPLINE_H
