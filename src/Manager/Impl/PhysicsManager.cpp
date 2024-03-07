#include "PhysicsManager.h"
#include "../../Game/Game.h"
#include "ConfigManager.h"
#include "SceneManager.h"
#include "../../Component/Impl/CompCollider.h"
#include "../../Component/Impl/CompTransform.h"


PhysicsManager::PhysicsManager()
{
    const ConfigManager* pConfigMgr = Game::GetManager<ConfigManager>();
    b2Vec2 gravity { 0.0f, -pConfigMgr->GetGlobalSetting().globalGravity };

    _pPhysicWorld = std::make_unique<b2World>(gravity);
}

b2World* PhysicsManager::GetPhysicWorld() const
{
    return _pPhysicWorld.get();
}

std::unique_ptr<b2Body, PhysicsManager::B2BodyDeleter> PhysicsManager::CreatePhysicBody(const b2BodyDef* def)
{
    b2Body* pBody = _pPhysicWorld->CreateBody(def);
    return std::unique_ptr<b2Body, PhysicsManager::B2BodyDeleter>(pBody);
}

void PhysicsManager::Tick()
{
    // update physics world
    _pPhysicWorld->Step(Game::GetDeltaTime(), velocityIterations, positionIterations);

    // apply all physics world position to real world position
    auto pSceneMgr = Game::GetManager<SceneManager>();
    auto& allEntities = pSceneMgr->GetSceneEntities();
    for (auto& [guid, pEntity]: allEntities)
    {
        auto pCollider = pEntity->GetComponent<CompCollider>();
        if (pCollider == nullptr)
            continue;

        auto pCompTrans = pEntity->GetComponent<CompTransform>();
        if (pCompTrans == nullptr)
            continue;

        auto pos = pCollider->GetPhysicalWorldPosition();
        pCompTrans->SetPosition(pos);
    }
}

