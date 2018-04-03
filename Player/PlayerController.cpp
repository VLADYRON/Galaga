//
// Created by matt on 3/28/18.
//

#include <Pure2D/Input/Keyboard.h>
#include "PlayerController.h"
#include "../Game/World.h"
#include "../Entities/Entity.h"
#include <cmath>
#include <iostream>

PlayerController::PlayerController(World &world):
    m_player(world.instantiate<Spaceship>({ 0, 0 }))
{ }

void PlayerController::handleInput(const SDL_Event &event)
{
    if (event.type == SDL_KEYUP)
    {
        if (event.key.state == SDL_RELEASED && event.key.keysym.sym == SDLK_SPACE)
            m_player.fireMissile();
    }
}

void PlayerController::update(float deltaTime)
{
    using namespace pure::keyboard;

    for (auto& kv: m_keybinds)
    {
        if (isKeyPressed(kv.first))
            kv.second(m_player, deltaTime);
    }
}

Spaceship& PlayerController::getShip() { return m_player; }

void PlayerController::addKeybind(pure::keyboard::Key key, PlayerController::GameAction action) { m_keybinds.emplace(key, action); }
void PlayerController::removeKeybind(pure::keyboard::Key key) { m_keybinds.erase(key); }

void PlayerController::changeKeybind(pure::keyboard::Key oldKey, pure::keyboard::Key newKey)
{
    auto handler = m_keybinds.extract(oldKey);

    if (handler.empty()) return;

    handler.key() = newKey;
    m_keybinds.insert(std::move(handler));
}
