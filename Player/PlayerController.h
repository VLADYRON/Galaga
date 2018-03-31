//
// Created by matt on 3/28/18.
//

#ifndef GALAGA_PLAYERCONTROLLER_H
#define GALAGA_PLAYERCONTROLLER_H

#include <unordered_map>
#include <functional>
#include <Pure2D/Input/Keyboard.h>
#include "../Entities/Spaceship.h"


union SDL_Event;

class PlayerController
{
public:
    using GameAction = std::function<void(Spaceship&, float)>;

    void handleInput(SDL_Event& event);
    void update(float deltaTime);

    void addKeybind(pure::keyboard::Key key, GameAction action);
    void removeKeybind(pure::keyboard::Key key);
    void changeKeybind(pure::keyboard::Key oldKey, pure::keyboard::Key newKey);

    Spaceship& getShip();

private:
    Spaceship m_player;
    std::unordered_map<pure::keyboard::Key, GameAction> m_keybinds;

};


#endif //GALAGA_PLAYERCONTROLLER_H
