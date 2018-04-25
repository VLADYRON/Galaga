//
// Created by matt on 4/12/18.
//

#ifndef GALAGA_PLAYSTATE_H
#define GALAGA_PLAYSTATE_H

#include <Pure2D/State/State.h>
#include <Pure2D/Window/Window.h>
#include "../Game/World.h"
#include "../Player/PlayerController.h"
#include "../Background/StarBackground.h"
#include "../Scripts/AlienGroup.h"
#include "../Scripts/CollisionSystem.h"


class PlayState : public pure::State
{
public:
    PlayState(pure::StateManager& manager, pure::Window* window);

private:

    pure::Window* m_window;
    World m_world;
    AlienGroup m_alienGroup;
    PlayerController m_player;
    StarBackground m_stars;
    CollisionSystem m_collision;

    void update(float deltaTime) final;
    void draw(const pure::Window& window) final;
    void handleInput(const SDL_Event& event) final;
    void onCreate() final;

    void setPlayerKeybinds();

    template<typename DrawableEntity>
    void drawEntity(DrawableEntity* de)
    {
        if (!de->isActive()) return;
        m_window->draw(*de);
    }
};


#endif //GALAGA_PLAYSTATE_H
