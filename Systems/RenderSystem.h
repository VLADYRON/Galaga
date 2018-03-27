//
// Created by matt on 3/26/18.
//

#ifndef GALAGA_RENDERSYSTEM_H
#define GALAGA_RENDERSYSTEM_H

#include <Pure2D/Window/Window.h>
#include "System.h"

class RenderSystem final : public System
{
public:
    explicit RenderSystem(pure::Window& window);
    ~RenderSystem() final = default;

    ComponentType getMask() const final;

    void update(float deltaTime = 1.f) final;

private:
    pure::Window& m_window;
    ComponentType m_cmpMask;
};


#endif //GALAGA_RENDERSYSTEM_H
