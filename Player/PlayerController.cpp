//
// Created by matt on 3/28/18.
//

#include <Pure2D/Input/Keyboard.h>
#include "PlayerController.h"
#include "../Entities/Entity.h"
#include <cmath>

PlayerController::PlayerController(World &world):
    m_player(world)
{ }

void PlayerController::handleInput(SDL_Event &event)
{

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

