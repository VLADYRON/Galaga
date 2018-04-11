//
// Created by matt on 3/28/18.
//

#ifndef GALAGA_PLAYERCONTROLLER_H
#define GALAGA_PLAYERCONTROLLER_H

#include <unordered_map>
#include <functional>
#include <Pure2D/Input/Keyboard.h>
#include "../Entities/Fighter.h"


union SDL_Event;

class PlayerController
{
public:
    using GameAction = std::function<void(Fighter&, float)>;

    explicit PlayerController(World& world);

    void handleInput(const SDL_Event& event);
    void update(float deltaTime);

    void addKeybind(pure::keyboard::Key key, GameAction action);
    void removeKeybind(pure::keyboard::Key key);
    void changeKeybind(pure::keyboard::Key oldKey, pure::keyboard::Key newKey);

    Fighter& getShip();

private:
    Fighter m_player;
    std::unordered_map<pure::keyboard::Key, GameAction> m_keybinds;

};


#endif //GALAGA_PLAYERCONTROLLER_H
