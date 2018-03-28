//
// Created by matt on 3/22/18.
//

#include "Game.h"
#include "AssetPaths.h"
#include <Pure2D/Util/Clock.h>
#include <Pure2D/Input/Keyboard.h>
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

    const int TICKS_PER_SECOND = m_window.getRefreshRate();
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 10;

//    const float dt = 1.f / m_window.getRefreshRate();
//    float accum = 0;

    int nextTick = SDL_GetTicks();
    int loops;

    while(m_window.isOpen())
    {

        while (SDL_PollEvent(&event))
            handleEvents(event);

        m_window.clear();

        loops = 0;
        while (SDL_GetTicks() > nextTick && loops < MAX_FRAMESKIP)
        {
            update(1.f / (float)TICKS_PER_SECOND);
            nextTick += SKIP_TICKS;
            loops++;
        }


        render();

        m_window.swapBuffers();
    }

//    const float dt = 1.f / m_window.getRefreshRate();
//    float accum = 0;
//    float currentTime = SDL_GetTicks() * 0.001f;
//    int count = 0;
//
//    while(m_window.isOpen())
//    {
//
//        while (SDL_PollEvent(&event))
//            handleEvents(event);
//
//        m_window.clear();
//
//        float newTime = SDL_GetTicks() * 0.001f;
//        float frameTime = newTime - currentTime;
//
//        currentTime = newTime;
//
//        accum += frameTime;
//
//        while(accum >= dt)
//        {
//            update(dt);
//            accum -= dt;
//        }
//
//        render();
//
//        m_window.swapBuffers();
//    }

//    while(m_window.isOpen())
//    {
//        while(SDL_PollEvent(&event))
//            handleEvents(event);
//
//        m_window.clear();
//
//        const float frameTime = clock.restart();
//        accum += frameTime;
//
//        while(accum >= dt)
//        {
//            const float deltaTime = std::min(frameTime, dt);
//            update(dt);
//            accum -= dt;
//        }
//
//        render();
//
//        m_window.swapBuffers();
//    }
}


void Game::update(float deltaTime)
{
    m_stars.update(deltaTime);
    using namespace pure::keyboard;

    if (isKeyPressed(Key::A))
    {
        renderRect.x -= std::round(50 * deltaTime);
    }
    if (isKeyPressed(Key::D))
    {
        renderRect.x += std::round(50 * deltaTime);
    }
}

void Game::render()
{
    SDL_RenderCopy(m_window.getRenderer().getHandle(), m_player->getHandle(), &textureRect, &renderRect);
    m_window.draw(m_stars);
}
