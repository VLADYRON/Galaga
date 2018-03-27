//
// Created by matt on 3/26/18.
//

#ifndef GALAGA_TYPEDEFS_H
#define GALAGA_TYPEDEFS_H

#include <memory>
#include <Pure2D/Util/Constants.h>

using Uptr_Component = std::unique_ptr<class Component>;
using Uptr_System = std::unique_ptr<class System>;
using Entity = pure::uint32;

#endif //GALAGA_TYPEDEFS_H
