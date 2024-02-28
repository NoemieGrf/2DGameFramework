#pragma once

#include "box2d/box2d.h"
#include "../GameManagerTypeGetter.h"

class PhysicsManager: public GameManagerTypeGetter<GameManagerType::Physics>
{
public:
    PhysicsManager();

private:
    b2World* pPhysicWorld = nullptr;
};