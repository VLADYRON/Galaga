//
// Created by matt on 3/22/18.
//

#include "Game.h"
#include <Pure2D/Util/Clock.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>

Game::Game()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
}

Game::~Game()
{
    SDL_Quit();
    IMG_Quit();
}

bool Game::createWindow(const char *title, pure::uint32 width, pure::uint32 height)
{
    return m_window.create(title, width, height);
}

void Game::start()
{
    doLoop();
}

void Game::handleEvents(const SDL_Event &event)
{
    if (event.type == SDL_QUIT)
        m_window.close();

    if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
        m_window.close();
}

void Game::doLoop()
{
    SDL_Event event{};
    pure::Clock clock;

    SDL_GL_SetSwapInterval(0);

    const float dt = 1.f / m_window.getRefreshRate();

    while(m_window.isOpen())
    {
        while(SDL_PollEvent(&event))
            handleEvents(event);

        m_window.clear();

        float frameTime = clock.restart();

        while(frameTime > 0.f)
        {
            const float deltaTime = std::min(frameTime, dt);
            update(deltaTime);
            frameTime -= deltaTime;
        }

        render();

        m_window.swapBuffers();
    }
}
void Game::update(float deltaTime)
{

}

void Game::render()
{

}
