//
// Created by matt on 4/14/18.
//

#ifndef GALAGA_LIFECYCLE_H
#define GALAGA_LIFECYCLE_H

class LifeCycle
{
public:
    virtual void onCreate() = 0;
    virtual void onDestroy() = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
};

#endif //GALAGA_LIFECYCLE_H
