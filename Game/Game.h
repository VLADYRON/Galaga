//
// Created by matt on 3/22/18.
//

#ifndef GALAGA_GAME_H
#define GALAGA_GAME_H

#include <Pure2D/Util/Constants.h>
#include <Pure2D/Window/Window.h>
#include <Pure2D/State/StateManager.h>

namespace pure
{
    class Texture;
}

class Game
{
public:

    Game();
    ~Game();

    bool createWindow(const char* title, uint32_t width, uint32_t height);
    void start();

private:
    pure::Window m_window;
    pure::StateManager m_stateManager;

    void handleEvents(const SDL_Event& event);
    void doLoop();
    void update(float deltaTime);
    void render();
};

#endif //GALAGA_GAME_H
