//
// Created by matt on 3/22/18.
//

#ifndef GALAGA_GAME_H
#define GALAGA_GAME_H

#include <Pure2D/Util/Constants.h>
#include <Pure2D/Window/Window.h>

class Game
{
public:

    Game();
    ~Game();

    bool createWindow(const char* title, pure::uint32 width, pure::uint32 height);
    void start();

private:
    pure::Window m_window;

    void handleEvents(const SDL_Event& event);
    void doLoop();
    void update(float deltaTime);
    void render();
};

#endif //GALAGA_GAME_H
