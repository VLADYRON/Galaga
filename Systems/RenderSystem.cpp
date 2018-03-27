//
// Created by matt on 3/26/18.
//

#include "RenderSystem.h"
#include "../Components/SpriteComponent.h"

RenderSystem::RenderSystem(pure::Window &window):
    m_window(window)
{
    m_cmpMask = ComponentType::Sprite | ComponentType::Position;
}

ComponentType RenderSystem::getMask() const
{
    return m_cmpMask;
}

void RenderSystem::update(float deltaTime)
{
    ECS& ecs = ECS::getInstance();

    for (Entity e : m_entities)
    {
        auto* spriteCmp = ecs.getComponent<SpriteComponent>(e);
        m_window.draw(*spriteCmp->sprite);
    }
}
