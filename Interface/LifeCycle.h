//
// Created by matt on 4/14/18.
//

#ifndef GALAGA_LIFECYCLE_H
#define GALAGA_LIFECYCLE_H

class LifeCycle
{
protected:
    virtual void activate() = 0;
    virtual void deactivate() = 0;
};

#endif //GALAGA_LIFECYCLE_H
