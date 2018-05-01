//
// Created by matt on 4/30/18.
//

#include "Health.h"

Health::Health(int maxHp): m_maxHp(maxHp)
{ }

int Health::get() const { return m_hp; }
void Health::takeDamage(int dmg) { m_hp -= dmg; }
void Health::reset() { m_hp = m_maxHp; }
