//
// Created by matt on 3/26/18.
//

#ifndef GALAGA_COMPONENTTYPE_H
#define GALAGA_COMPONENTTYPE_H


#include <cmath>

enum class ComponentType : long
{
    None = 0,
    Position = 1 << 0,
    Sprite = 1 << 1,
    NUM_COMPONENTS = (int)std::log2(static_cast<long>(ComponentType::Sprite))
};

inline ComponentType operator ~(ComponentType ct)
{
    long ctlong = ~(static_cast<long>(ctlong));
    return static_cast<ComponentType>(ctlong);
}

inline ComponentType operator &(ComponentType ctl, ComponentType ctr)
{
    auto ctlLong = static_cast<long>(ctl);
    auto ctrLong = static_cast<long>(ctr);
    return static_cast<ComponentType>(ctlLong & ctrLong);
}

inline ComponentType operator |(ComponentType ctl, ComponentType ctr)
{
    auto ctlLong = static_cast<long>(ctl);
    auto ctrLong = static_cast<long>(ctr);
    return static_cast<ComponentType>(ctlLong | ctrLong);
}

inline ComponentType operator <<(ComponentType ctl, ComponentType ctr)
{
    auto ctlLong = static_cast<long>(ctl);
    auto ctrLong = static_cast<long>(ctr);
    return static_cast<ComponentType>(ctlLong << ctrLong);
}

inline ComponentType operator >>(ComponentType ctl, ComponentType ctr)
{
    auto ctlLong = static_cast<long>(ctl);
    auto ctrLong = static_cast<long>(ctr);
    return static_cast<ComponentType>(ctlLong >> ctrLong);
}

inline ComponentType& operator &=(ComponentType& ctl, ComponentType ctr)
{
    ctl = ctl & ctr;
    return ctl;
}

inline ComponentType& operator |=(ComponentType& ctl, ComponentType ctr)
{
    ctl = ctl | ctr;
    return ctl;
}

inline ComponentType& operator <<=(ComponentType& ctl, ComponentType ctr)
{
    ctl = ctl << ctr;
    return ctl;
}

inline ComponentType& operator >>=(ComponentType& ctl, ComponentType ctr)
{
    ctl = ctl >> ctr;
    return ctl;
}


#endif //GALAGA_COMPONENTTYPE_H
