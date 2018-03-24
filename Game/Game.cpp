//
// Created by matt on 3/22/18.
//

#include "Game.h"
#include "AssetPaths.h"
#include <Pure2D/Util/Clock.h>
#include <Pure2D/Util/Random.h>
#include <glm/ext.hpp>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <iostream>

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

// TODO: Put these in a player class or some shit
SDL_Rect textureRect = {
    18 * 7, 0, 18, 18
};

SDL_Rect renderRect = {
    500, 768 - 50, 50, 50
};

void Game::start()
{
    m_player = m_window.getRenderer().getTexture(paths::GalagaSpriteSheet);
    m_stars.create(200, 500, m_window.getSize());

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
    m_stars.update(deltaTime);
}

void Game::render()
{
    SDL_RenderCopy(m_window.getRenderer().getHandle(), m_player->getHandle(), &textureRect, &renderRect);
    m_window.draw(m_stars);
}
