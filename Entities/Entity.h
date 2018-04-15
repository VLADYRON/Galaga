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

class Entity : public LifeCycle
{
public:
    virtual ~Entity() = 0;


    bool isActive() const;
    const Transform& getTransform() const;
    void setTransform(const Transform& transform);

    /**
     * Gets top left coordinate of entity.
     * shorthand for getPosition() - getOrigin()
     * @return top left coordinate of entity.
     */
    glm::vec2 getTopLeft() const;
    glm::vec2 getPosition() const;
    void setPosition(const glm::vec2& position);

    const glm::vec2& getVelocity() const;
    void setVelocity(const glm::vec2& velocity);

    float getRotation() const;
    void setRotation(float rotation);

    /**
     * Get origin relative to top left corner
     * @return local relative origin
     */
    const glm::vec2& getOrigin() const;

    /**
     * Set origin relative to top left corner
     * @param origin
     */
    void setOrigin(const glm::vec2& origin);

    void move(const glm::vec2& position);

    virtual void update(float deltaTime) { }
    void activate() override;
    void deactivate() override;

private:
    Transform m_transform;
    bool m_isActive;
};


#endif //GALAGA_ENTITY_H
