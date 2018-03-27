//
// Created by matt on 3/26/18.
//

#include "System.h"

System::~System() { }

void System::registerEntity(ECS::Entity entity) { m_entities.push_back(entity); }
