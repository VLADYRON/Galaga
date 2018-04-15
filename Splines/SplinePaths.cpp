//
// Created by matt on 4/14/18.
//
#include "SplinePaths.h"
#include <vector>
#include <glm/vec2.hpp>
#include "Spline.h"

std::vector<Spline::Node> splinePaths::doubleLoopLeft(glm::vec2 startPos)
{
    return {
        Spline::Node({ 262,43 }),
        Spline::Node(startPos),
        Spline::Node({ 36,727 }),
        Spline::Node({ 107,623 }),
        Spline::Node({ 54,613 }),
        Spline::Node({ 70,665 }),
        Spline::Node({ 145,618 }),
        Spline::Node({ 127,572 }),
        Spline::Node({ 103,618 }),
        Spline::Node({ 198,610 }),
        Spline::Node({ 236,580 }),
        Spline::Node({ 274,528 }),
        Spline::Node({ 357,406 }),
        Spline::Node({ 201,41 })
    };
}
