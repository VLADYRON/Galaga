//
// Created by matt on 3/24/18.
//

#ifndef GALAGA_STARBACKGROUND_H
#define GALAGA_STARBACKGROUND_H

#include <Pure2D/Renderables/Renderable.h>
#include <Pure2D/Util/Random.h>
#include <SDL2/SDL_rect.h>
#include <glm/vec2.hpp>
#include <vector>

class StarBackground : public pure::Renderable
{
public:
    StarBackground();

    void create(int numStars, float speed, const glm::vec2& bounds);

    bool isMoving() const;

    void setMoving(bool isMoving);

    void update(float deltaTime);

private:
    float m_speed;
    bool m_isMoving;
    std::vector<SDL_Point> m_stars;
    glm::vec2 m_bounds;

    pure::Random m_rand;

    void draw(SDL_Renderer* renderer) const final;
};


#endif //GALAGA_STARBACKGROUND_H
