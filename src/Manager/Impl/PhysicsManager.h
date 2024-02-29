#pragma once

#include "../../Game/GlobalDefine.h"
#include "box2d/box2d.h"
#include "../GameManagerTypeGetter.h"

class PhysicsManager: public GameManagerTypeGetter<GameManagerType::Physics>
{
public:
    PhysicsManager();

public:
    auto GetPhysicWorld() const -> b2World*;
    auto GetGroundBody() const -> b2Body*;

private:
    // physic world
    uptr<b2World> _pPhysicWorld = nullptr;

    // ground
    uptr<b2Body> _pGroundBody = nullptr;
};