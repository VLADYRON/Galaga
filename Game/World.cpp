//
// Created by matt on 3/30/18.
//

#include "../Entities/Entity.h"
#include "World.h"


using namespace pure;

PlayerController *World::getPlayer() { return m_player; }

void World::setPlayer(PlayerController &player) { m_player = &player; }

