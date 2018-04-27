//
// Created by matt on 4/12/18.
//

#include "PlayState.h"
#include <Pure2D/Util/Convert.h>
#include "../Entities/Entity.h"
#include "../Util/Defaults.h"
#include "../Util/Rect.h"
#include "../Splines/SplinePaths.h"
#include "../Player/PlayerController.h"

PlayState::PlayState(pure::StateManager& manager, pure::Window* window):
        pure::State(manager),
        m_window(window),
        m_alienGroup(m_world, { 50, 50 }, m_window->getSize()),
        m_player(*m_world.getPlayer()),
        m_collision(m_world)
{ }

void PlayState::onCreate()
{
    Fighter& playerShip = m_player.getShip();

    defaults::set(playerShip, SpriteType::SHIP_WHITE);

    glm::vec2 position = {
        (m_window->getSize().x / 2.f),
        (m_window->getSize().y - playerShip.getSize().y / 2.f)
    };

//    m_alienGroup.spawnAliens(20, SpriteType::BEE);
    m_alienGroup.start();
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
    m_collision.update();

    {
        using namespace pure::keyboard;
        SDL_Rect r = m_player.getShip().textureRect();
        if (isKeyPressed(Key::UP)) r.y -= 5;
        if (isKeyPressed(Key::LEFT)) r.x -= 5;
        if (isKeyPressed(Key::RIGHT)) r.x += 5;
        if (isKeyPressed(Key::DOWN)) r.y += 5;
        m_player.getShip().setTextureRect(r);
    }

    const EArr<Missile*>& missiles = m_world.getEntities<Missile>();

    m_player.update(deltaTime);
    m_alienGroup.update(deltaTime);

    for (auto m : missiles)
    {
        if (!m->isActive()) continue;
        m->update(deltaTime);
        glm::vec2 pos = m->getPosition();

        const Rect winRect = { 0, 0, m_window->getSize().x, m_window->getSize().y };

        if (winRect.isOutside(pos))
            m_world.destroy<Missile>(*m);
    }
}

void PlayState::draw(const pure::Window &window)
{
    const EArr<Missile*>& missiles = m_world.getEntities<Missile>();
    const EArr<Alien*>& aliens = m_world.getEntities<Alien>();


    for (auto m : missiles) drawEntity(m);
    for (auto a : aliens) drawEntity(a);

    m_window->draw(m_stars);
    m_window->draw(m_player.getShip());

}

void PlayState::handleInput(const SDL_Event &event)
{
    m_player.handleInput(event);

}
