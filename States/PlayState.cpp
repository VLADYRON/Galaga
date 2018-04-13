//
// Created by matt on 4/12/18.
//

#include "PlayState.h"
#include <Pure2D/Window/Window.h>
#include "../Util/Defaults.h"
#include "../Util/Rect.h"

PlayState::PlayState(pure::StateManager& manager, pure::Window& window):
    pure::State(manager),
    m_player(m_world),
    m_window(window)
{ }

void PlayState::onCreate()
{
    Fighter& playerShip = m_player.getShip();

    defaults::set(playerShip, SpriteType::SHIP_WHITE);

    std::vector<Spline::Node> path = {
            Spline::Node({ 262,43 }),
            Spline::Node({ -107,787 }),
            Spline::Node({ 36,727 }),
            Spline::Node({ 107,623 }),
            Spline::Node({ 54,613 }),
            Spline::Node({ 70,665 }),
            Spline::Node({ 145,618 }),
            Spline::Node({ 127,572 }),
            Spline::Node({ 103,618 }),
            Spline::Node({ 198,610 }),
            Spline::Node({ 236,580 }),
            Spline::Node({ 274,528 }),
            Spline::Node({ 357,406 }),
            Spline::Node({ 201,41 })
    };
    for (int i = 0; i < 8; i++)
    {
        auto& alien = m_world.instantiate<Alien>({ -107,787 });
        defaults::set(alien, SpriteType::BEE);
        alien.setDivepath(path, false);
    }


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
}

void PlayState::update(float deltaTime)
{
    static int indx = 0;
    static float timer = 0.f;
    m_stars.update(deltaTime);

    const EArr<Missile*>& missiles = m_world.getEntities<Missile>();
    const EArr<Alien*>& aliens = m_world.getEntities<Alien>();

    m_player.update(deltaTime);

    // TODO: find some way to not have to const cast, or at least hide it...

    timer += deltaTime;
    for (auto alien : aliens)
    {
        if (timer > 0.095f && indx < aliens.size())
        {
            timer = 0.f;
            aliens[indx]->startDivePath();
            indx++;
        }
        alien->update(deltaTime);
    }

    for (auto m : missiles)
    {
        m->update(deltaTime);
        glm::vec2 pos = m->getPosition();

        Rect winRect = { 0, 0, m_window.getSize().x, m_window.getSize().y };

        if (winRect.isOutside(pos))
            m_world.destroy<Missile>(*m);
    }
}

void PlayState::draw(const pure::Window &window)
{
    const EArr<Missile*>& missiles = m_world.getEntities<Missile>();
    const EArr<Alien*>& aliens = m_world.getEntities<Alien>();


    for (auto m : missiles)
        m_window.draw(*m);
    for (auto a : aliens)
        m_window.draw(*a);

    m_window.draw(m_stars);
    m_window.draw(m_player.getShip());
}

void PlayState::handleInput(const SDL_Event &event)
{
    m_player.handleInput(event);
}


