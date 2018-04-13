//
// Created by matt on 4/12/18.
//

#ifndef GALAGA_POOLABLE_H
#define GALAGA_POOLABLE_H

template<typename P>
class ObjectPool;

static int test = 0;

template<typename T>
class Poolable : public T
{

    friend ObjectPool<T>;

    Poolable<T>* next;
public:
    inline ~Poolable()
    {
        test++;
    }
};


#endif //GALAGA_POOLABLE_H
