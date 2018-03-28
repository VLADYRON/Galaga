//
// Created by matt on 3/24/18.
//

#include "StarBackground.h"
#include <Pure2D/Util/Constants.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <glm/glm.hpp>

using pure::uint64;

StarBackground::StarBackground():
    m_isMoving(true)
{  }

void StarBackground::create(int numStars, float speed, const glm::vec2 &bounds)
{
    m_speed = speed;
    m_bounds = glm::vec2(bounds);

    m_stars.reserve((uint64)numStars);

    for (int i = 0; i < numStars; i++)
    {
        SDL_Point star = {
            m_rand((int)bounds.x),
            m_rand((int)bounds.y)
        };
        m_stars.push_back(star);
    }
}

bool StarBackground::isMoving() const { return m_isMoving; }
void StarBackground::setMoving(bool isMoving) { m_isMoving = isMoving; }

void StarBackground::update(float deltaTime)
{
    if (!m_isMoving) return;

    for (auto& star : m_stars)
    {
        star.y += std::round(m_speed * deltaTime);

        if (star.y > m_bounds.y)
        {
            star.x = m_rand((int)m_bounds.x);
            star.y = 0;
        }
    }
}

void StarBackground::draw(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoints(renderer, &m_stars[0], (int)m_stars.size());
}


