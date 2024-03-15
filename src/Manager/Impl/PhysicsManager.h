#pragma once

#include "box2d/box2d.h"
#include "Game/Game.h"
#include "Game/GlobalDefine.h"
#include "Manager/GameManagerTypeGetter.h"

class CompCollider;

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
            phyMgr->DestroyPhysicBody(p);
        }
    };

public:
    auto GetPhysicWorld() const -> b2World*;
    auto GetColliderFromBody(b2Body* pBody) -> CompCollider*;
    auto CreatePhysicBody(const b2BodyDef* def, CompCollider* pCollider) -> std::unique_ptr<b2Body, PhysicsManager::B2BodyDeleter>;
    auto DestroyPhysicBody(b2Body* pBody) -> void;

public:
    auto Tick() -> void override;

private:
    // physic world
    uptr<b2World> _pPhysicWorld = nullptr;

    // all body map
    umap<b2Body*, CompCollider*> _bodyToColliderMap;

    // const
    static const int velocityIterations = 8;
    static const int positionIterations = 3;
};