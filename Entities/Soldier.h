//
// Created by matt on 5/1/18.
//

#ifndef GALAGA_SOLIDER_H
#define GALAGA_SOLIDER_H


#include "Alien.h"

class Soldier : public Alien
{
private:
    void handleDivingState() final;
    void handleDiveEndState() final;
};


#endif //GALAGA_SOLIDER_H
