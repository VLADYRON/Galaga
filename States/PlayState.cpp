//
// Created by matt on 4/12/18.
//

#include "PlayState.h"
#include <Pure2D/Util/Convert.h>
#include "../Entities/Entity.h"
#include "../Entities/Explosion.h"
#include "../Entities/Missile.h"
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

    m_alienGroup.start();
    playerShip.setPosition(position);

    setPlayerKeybinds();

    m_stars.create(200, 500, m_window->getSize());
}

void PlayState::setPlayerKeybinds()
{
    using namespace pure::keyboard;

    m_player.addKeybind(pure::keyboard::Key::A, [](Fighter& player, float dt) {
        player.move({-(round(player.velocity().x * dt)), 0.f });
        if (player.getTopLeft().x < 0)
            player.setPosition({ (player.getSize().x / 2.f), player.position().y });
    });

    m_player.addKeybind(pure::keyboard::Key::D, [this](Fighter& player, float dt) {
        player.move({(round(player.velocity().x * dt)), 0.f });
        if (player.getTopLeft().x + player.getSize().x > m_window->getSize().x)
        {
            player.setPosition({m_window->getSize().x - (player.getSize().x / 2.f), player.position().y });
        }
    });
}

void PlayState::update(float deltaTime)
{

    m_stars.update(deltaTime);
    m_collision.update();

    const EArr<Missile*>& missiles = m_world.getEntities<Missile>();
    const EArr<Explosion*>& explosions = m_world.getEntities<Explosion>();

    m_player.update(deltaTime);
    m_alienGroup.update(deltaTime);

    for (auto m : missiles)
    {
        if (!m->isActive()) continue;
        m->update(deltaTime);
        glm::vec2 pos = m->position();

        const Rect winRect = { 0, 0, m_window->getSize().x, m_window->getSize().y };

        if (winRect.isOutside(pos))
            m_world.destroy<Missile>(*m);

//        if (winRect.isOutside(pos))
//        {
//            m_world.destroy<Missile>(*m);
//            std::cout << m_world.getEntities<Missile>().size() << std::endl;
//        }
    }

    for (auto e : explosions)
    {
        if (!e->isActive()) continue;
        e->update(deltaTime);

        if (e->isDone()) m_world.destroy<Explosion>(*e);
    }
}

void PlayState::draw(const pure::Window &window)
{
    const EArr<Missile*>& missiles = m_world.getEntities<Missile>();
    const EArr<Alien*>& aliens = m_world.getEntities<Alien>();
    const EArr<Explosion*>& explosions = m_world.getEntities<Explosion>();


    for (auto m : missiles) drawEntity(m);
    for (auto a : aliens) drawEntity(a);
    for (auto e : explosions) drawEntity(e);

    m_window->draw(m_stars);
    m_window->draw(m_player.getShip());

}

void PlayState::handleInput(const SDL_Event &event)
{
    m_player.handleInput(event);

}
