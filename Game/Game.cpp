//
// Created by matt on 3/22/18.
//

#include "Game.h"
#include "AssetPaths.h"
#include "../Entities/Entity.h"
#include "../Util/SpriteMap.h"
#include "../Game/Rect.h"
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

SDL_Rect renderRect = {
    500, 768 - 50, 50, 50
};

void Game::start()
{
    pure::Texture* texture = m_window.getRenderer().getTexture(paths::GalagaSpriteSheet);

    Spaceship& playerShip = m_player.getShip();

    playerShip.setTexture(texture);
    playerShip.setTextureRect(spritemap::SHIP_WHITE);
    playerShip.setSize({ 50, 50 });

    glm::vec2 position = {
        (m_window.getSize().x / 2.f),
        (m_window.getSize().y - playerShip.getSize().y / 2.f)
    };

    playerShip.setOrigin(playerShip.getSize() / 2.f);
    playerShip.setPosition(position);

    playerShip.setVelocity({ 250, 0 });

    using namespace pure::keyboard;

    m_player.addKeybind(Key::A, [](Spaceship& player, float dt) {
        player.move({ -(std::round(player.getVelocity().x * dt)), 0.f });
        if (player.getTopLeft().x < 0)
            player.setPosition({ (player.getSize().x / 2.f), player.getPosition().y });
    });

    m_player.addKeybind(Key::D, [this](Spaceship& player, float dt) {
        player.move({ (std::round(player.getVelocity().x * dt)), 0.f });
        if (player.getTopLeft().x + player.getSize().x > m_window.getSize().x)
        {
            player.setPosition({ m_window.getSize().x - (player.getSize().x / 2.f), player.getPosition().y });
        }
    });

    m_player.addKeybind(Key::SPACE, [](Spaceship& player, float dt) {
        player.fireMissle();
    });


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
    float accum = 0.f;

    while(m_window.isOpen())
    {
        while(SDL_PollEvent(&event))
            handleEvents(event);


        float frameTime = clock.restart();
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
    m_stars.update(deltaTime);
    m_player.update(deltaTime);
}


void Game::render()
{
    m_window.draw(m_player.getShip());
    m_window.draw(m_stars);
}

