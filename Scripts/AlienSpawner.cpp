//
// Created by matt on 4/18/18.
//

#include <iostream>
#include "AlienSpawner.h"
#include "../Entities/Alien.h"

bool AlienSpawner::isDone() const
{
    return m_diveIndx >= m_divingAliens.size() || m_divingAliens.empty();
}

void AlienSpawner::update()
{
    if (isDone()) return;

    if (m_diveTimer.getElapsedTime() >= 0.095f)
    {
        m_diveTimer.restart();
        Alien* alien = m_divingAliens[m_diveIndx];
        alien->startDivePath();
        alien->activate();
        m_diveIndx++;

        if (isDone())
        {
            reset();
            if (m_onDone) m_onDone();
        }
    }
}

void AlienSpawner::addAliens(std::vector<Alien *> aliens)
{
    for (auto a : aliens) m_divingAliens.push_back(a);
}

void AlienSpawner::addAlien(Alien *alien)
{
    if (!alien) return;
    m_divingAliens.push_back(alien);
}

void AlienSpawner::start()
{
    m_diveIndx = 0;
    m_diveTimer.restart();
}

void AlienSpawner::reset()
{
    m_divingAliens.clear();
}

void AlienSpawner::setOnDone(std::function<void()> onDone)
{
    m_onDone = std::move(onDone);
}

