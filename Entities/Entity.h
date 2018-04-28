//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_ENTITY_H
#define GALAGA_ENTITY_H

#include <Pure2D/Renderables/Renderable.h>
#include "../Components/Transform.h"
#include "../Interface/LifeCycle.h"

struct SDL_Renderer;
class World;

class Entity
{
public:
    virtual ~Entity() = 0;

    const Transform& getTransform() const;
    void setTransform(const Transform& transform);

    /**
     * Gets top left coordinate of entity.
     * shorthand for getPosition() - getOrigin()
     * @return top left coordinate of entity.
     */
    glm::vec2 getTopLeft() const;
    glm::vec2 position() const;
    void setPosition(const glm::vec2& position);

    const glm::vec2& velocity() const;
    void setVelocity(const glm::vec2& velocity);

    float getRotation() const;
    void setRotation(float rotation);

    /**
     * Get origin relative to top left corner
     * @return local relative origin
     */
    const glm::vec2& origin() const;

    /**
     * Set origin relative to top left corner
     * @param origin
     */
    void setOrigin(const glm::vec2& origin);

    void move(const glm::vec2& position);

    virtual void update(float deltaTime) { }

private:
    Transform m_transform;

};


#endif //GALAGA_ENTITY_H
