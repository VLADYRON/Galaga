//
// Created by matt on 4/18/18.
//

#ifndef GALAGA_ALIENSPAWNER_H
#define GALAGA_ALIENSPAWNER_H

#include <Pure2D/Util/Clock.h>
#include <vector>
#include <functional>

class Alien;

class AlienSpawner
{
public:
    bool isDone() const;
    void addAliens(std::vector<Alien*> aliens);
    void addAlien(Alien* alien);
    void start();
    void setOnDone(std::function<void()> onDone);

    void update();
    void reset();

private:
    pure::Clock m_diveTimer;
    std::vector<Alien*> m_divingAliens;
    uint32_t m_diveIndx;
    std::function<void()> m_onDone;
};


#endif //GALAGA_ALIENSPAWNER_H
