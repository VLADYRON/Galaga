//
// Created by matt on 3/22/18.
//

#include "Game.h"
#include "AssetPaths.h"
#include "../Entities/Entity.h"
#include "../Util/SpriteMap.h"
#include "../Util/Rect.h"
#include "../Util/TextureManager.h"
#include "../Util/Defaults.h"
#include <Pure2D/Util/Clock.h>
#include <Pure2D/Input/Keyboard.h>
#include <Pure2D/Util/Random.h>
#include <glm/ext.hpp>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <iostream>

Game::Game():
    m_window(),
    m_world(),
    m_player(m_world)
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

    Fighter& playerShip = m_player.getShip();

    defaults::set(playerShip, SpriteType::SHIP_WHITE);

    auto& alien = m_world.instantiate<Alien>({ -115, 769 });
    defaults::set(alien, SpriteType::BEE);
    alien.setDivepath({
        Spline::Node({ 10,44 }),
        Spline::Node({ -115,769 }),
        Spline::Node({ 59,746 }),
        Spline::Node({ 204,634 }),
        Spline::Node({ 104,563 }),
        Spline::Node({ 45,645 }),
        Spline::Node({ 123,729 }),
        Spline::Node({ 251,648 }),
        Spline::Node({ 99,627 }),
        Spline::Node({ 200,735 }),
        Spline::Node({ 338,601 }),
        Spline::Node({ 393,300 }),
        Spline::Node({ 368,41 })
      });

    glm::vec2 position = {
        (m_window.getSize().x / 2.f),
        (m_window.getSize().y - playerShip.getSize().y / 2.f)
    };

    playerShip.setPosition(position);

    using namespace pure::keyboard;

    m_player.addKeybind(Key::A, [](Fighter& player, float dt) {
        player.move({ -(std::round(player.getVelocity().x * dt)), 0.f });
        if (player.getTopLeft().x < 0)
            player.setPosition({ (player.getSize().x / 2.f), player.getPosition().y });
    });

    m_player.addKeybind(Key::D, [this](Fighter& player, float dt) {
        player.move({ (std::round(player.getVelocity().x * dt)), 0.f });
        if (player.getTopLeft().x + player.getSize().x > m_window.getSize().x)
        {
            player.setPosition({ m_window.getSize().x - (player.getSize().x / 2.f), player.getPosition().y });
        }
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

    m_player.handleInput(event);
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

// TODO: Create some game states
void Game::update(float deltaTime)
{
    m_stars.update(deltaTime);
    m_world.update();

    const EArr<Missile>& missiles = m_world.getEntities<Missile>();
    const EArr<Alien>& aliens = m_world.getEntities<Alien>();

    m_player.update(deltaTime);

    // TODO: find some way to not have to const cast, or at least hide it...

    for (auto& a : aliens)
    {
        const_cast<Alien&>(a).update(deltaTime);
    }

    for (auto& m : missiles)
    {
        auto& ms = const_cast<Missile&>(m);
        ms.update(deltaTime);
        glm::vec2 pos = ms.getPosition();

        Rect winRect = { 0, 0, m_window.getSize().x, m_window.getSize().y };

        if (winRect.isOutside(pos))
            m_world.destroy<Missile>(ms);
    }
}


void Game::render()
{

    const EArr<Missile>& missiles = m_world.getEntities<Missile>();
    const EArr<Alien>& aliens = m_world.getEntities<Alien>();


    for (auto& m : missiles)
        m_window.draw(m);
    for (auto& a : aliens)
        m_window.draw(a);

    m_window.draw(m_stars);
    m_window.draw(m_player.getShip());
}

