//
// Created by matt on 4/12/18.
//

#include "PlayState.h"
#include <Pure2D/Window/Window.h>
#include "../Entities/Entity.h"
#include "../Util/Defaults.h"
#include "../Util/Rect.h"
#include "../Splines/SplinePaths.h"

PlayState::PlayState(pure::StateManager& manager, pure::Window* window):
        pure::State(manager),
        m_alienGroup(m_world, { 50, 50 }),
        m_player(m_world),
        m_window(window)
{ }

void PlayState::onCreate()
{
    Fighter& playerShip = m_player.getShip();

    defaults::set(playerShip, SpriteType::SHIP_WHITE);

    glm::vec2 position = {
        (m_window->getSize().x / 2.f),
        (m_window->getSize().y - playerShip.getSize().y / 2.f)
    };

    m_alienGroup.spawnAliens(8, SpriteType::BEE);

    playerShip.setPosition(position);

    setPlayerKeybinds();

    m_stars.create(200, 500, m_window->getSize());
}

void PlayState::setPlayerKeybinds()
{
    using namespace pure::keyboard;

    m_player.addKeybind(pure::keyboard::Key::A, [](Fighter& player, float dt) {
        player.move({-(round(player.getVelocity().x * dt)), 0.f });
        if (player.getTopLeft().x < 0)
            player.setPosition({ (player.getSize().x / 2.f), player.getPosition().y });
    });

    m_player.addKeybind(pure::keyboard::Key::D, [this](Fighter& player, float dt) {
        player.move({(round(player.getVelocity().x * dt)), 0.f });
        if (player.getTopLeft().x + player.getSize().x > m_window->getSize().x)
        {
            player.setPosition({m_window->getSize().x - (player.getSize().x / 2.f), player.getPosition().y });
        }
    });
}

void PlayState::update(float deltaTime)
{

    m_stars.update(deltaTime);

    const EArr<Missile*>& missiles = m_world.getEntities<Missile>();

    m_player.update(deltaTime);
    m_alienGroup.update(deltaTime);

    for (auto m : missiles)
    {
        m->update(deltaTime);
        glm::vec2 pos = m->getPosition();

        Rect winRect = { 0, 0, m_window->getSize().x, m_window->getSize().y };

        if (winRect.isOutside(pos))
            m_world.destroy<Missile>(*m);
    }
}

void PlayState::draw(const pure::Window &window)
{
    const EArr<Missile*>& missiles = m_world.getEntities<Missile>();
    const EArr<Alien*>& aliens = m_world.getEntities<Alien>();


    for (auto m : missiles)
        m_window->draw(*m);
    for (auto a : aliens)
        m_window->draw(*a);

    m_window->draw(m_stars);
    m_window->draw(m_player.getShip());
}

void PlayState::handleInput(const SDL_Event &event)
{
    m_player.handleInput(event);
}

