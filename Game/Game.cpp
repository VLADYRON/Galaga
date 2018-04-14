//
// Created by matt on 3/22/18.
//

#include "Game.h"
#include "AssetPaths.h"
#include "../Util/TextureManager.h"
#include "../States/GameState.h"
#include "../States/PlayState.h"
#include <Pure2D/State/StateManager.h>
#include <Pure2D/Util/Clock.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <SDL2/SDL_image.h>
#include <iostream>

Game::Game():
    m_stateManager(m_window)
{
    SDL_Init(SDL_INIT_EVERYTHING);
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
    {
        TextureManager& textureManager = TextureManager::instance();
        pure::Texture* spritesheet =  m_window.getRenderer().getTexture(paths::GalagaSpriteSheet);
        textureManager.addTexture(paths::GalagaSpriteSheet, spritesheet);
    }

    m_stateManager.registerState<PlayState>((int)GameState::Playing, &m_window);

    m_stateManager.pushState((int)GameState::Playing);

    doLoop();
}

void Game::handleEvents(const SDL_Event &event)
{
    if (event.type == SDL_QUIT)
        m_window.close();

    if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
        m_window.close();

    m_stateManager.handleInput(event);
}

void Game::doLoop()
{
    SDL_Event event{};
    pure::Clock clock;

    SDL_GL_SetSwapInterval(0);

    const float dt = 1.f / 60.f;
    float accum = 0.f;


    while(m_window.isOpen())
    {
        while(SDL_PollEvent(&event))
            handleEvents(event);

        const float frameTime = clock.restart();
        accum += frameTime;

        while(accum >= dt)
        {
            update(dt);
            accum -= dt;
        }

        m_window.clear(glm::vec4(0, 0, 0, 255));

        render();

        m_window.swapBuffers();
    }
}

void Game::update(float deltaTime)
{
    m_stateManager.update(deltaTime);
}


void Game::render()
{
    m_stateManager.draw();
}

