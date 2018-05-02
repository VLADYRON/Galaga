//
// Created by matt on 5/1/18.
//

#ifndef GALAGA_CATCHER_H
#define GALAGA_CATCHER_H


#include "Alien.h"

class Catcher : public Alien
{
private:
    void handleDivingState() final;
    void handleDiveEndState() final;
};


#endif //GALAGA_CATCHER_H
