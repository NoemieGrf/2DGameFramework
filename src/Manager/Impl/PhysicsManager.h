#pragma once

#include "box2d/box2d.h"
#include "../../Game/Game.h"
#include "../../Game/GlobalDefine.h"
#include "../GameManagerTypeGetter.h"

class PhysicsManager: public GameManagerTypeGetter<GameManagerType::Physics>
{
public:
    PhysicsManager();

public:
    // the destructor of b2body is private,
    // the only way to delete b2body is b2world->DestroyBody(),
    // so we have to make a B2BodyDeleter to specific the
    // behaviour of unique_ptr<b2Body>
    struct B2BodyDeleter
    {
        void operator() (b2Body* p)
        {
            PhysicsManager* phyMgr = Game::GetManager<PhysicsManager>();
            phyMgr->GetPhysicWorld()->DestroyBody(p);
        }
    };

public:
    auto GetPhysicWorld() const -> b2World*;
    auto CreatePhysicBody(const b2BodyDef* def) -> std::unique_ptr<b2Body, PhysicsManager::B2BodyDeleter>;

public:
    auto Tick() -> void override;

private:
    // physic world
    uptr<b2World> _pPhysicWorld = nullptr;

    // const
    static const int velocityIterations = 8;
    static const int positionIterations = 3;
};