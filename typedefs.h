//
// Created by matt on 3/31/18.
//

#ifndef GALAGA_TYPEDEFS_H
#define GALAGA_TYPEDEFS_H

#include <functional>
#include <memory>
class Entity;

template<typename T>
using CtorCallback = std::function<T()>;

using UPtr_Entity = std::unique_ptr<Entity>;

#endif //GALAGA_TYPEDEFS_H
