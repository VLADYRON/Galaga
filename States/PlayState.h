//
// Created by matt on 4/12/18.
//

#ifndef GALAGA_PLAYSTATE_H
#define GALAGA_PLAYSTATE_H

#include <Pure2D/State/State.h>
#include "../Game/World.h"
#include "../Player/PlayerController.h"
#include "../Background/StarBackground.h"

class PlayState : public pure::State
{
public:
    PlayState(pure::StateManager& manager, pure::Window& window);

private:

    pure::Window& m_window;
    World m_world;
    PlayerController m_player;
    StarBackground m_stars;

    void update(float deltaTime) final;
    void draw(const pure::Window& window) final;
    void handleInput(const SDL_Event& event) final;
    void onCreate() final;
};


#endif //GALAGA_PLAYSTATE_H
