//
// Created by matt on 4/9/18.
//

#ifndef GALAGA_SPLINEPATH_H
#define GALAGA_SPLINEPATH_H


#include "Spline.h"
#include <functional>

class SplinePath
{
public:
    using PathAction = std::function<void()>;
    struct ResultPoint
    {
        glm::vec2 pos;
        float forwardRotation;
    };

    SplinePath();

    bool isDone() const;

    void setOnStart(PathAction callback);
    void setOnDone(PathAction callback);
    void startPath();
    SplinePath::ResultPoint getNextStep(float stepSize);

    void setPath(std::vector<Spline::Node> path, bool begin = true);

private:
    bool m_isDone;
    float m_pos;
    PathAction m_onStart;
    PathAction m_onDone;
    Spline m_path;
};


#endif //GALAGA_SPLINEPATH_H
