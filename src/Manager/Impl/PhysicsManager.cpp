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

CompCollider* PhysicsManager::GetColliderFromBody(b2Body* pBody)
{
    auto itr = _bodyToColliderMap.find(pBody);
    if (itr == _bodyToColliderMap.end())
        return nullptr;

    return itr->second;
}

auto PhysicsManager::CreatePhysicBody(const b2BodyDef* def, CompCollider* pCollider) -> std::unique_ptr<b2Body, PhysicsManager::B2BodyDeleter>
{
    // create
    b2Body* pBody = _pPhysicWorld->CreateBody(def);

    // add to map
    _bodyToColliderMap[pBody] = pCollider;

    return std::unique_ptr<b2Body, PhysicsManager::B2BodyDeleter>(pBody);
}

void PhysicsManager::DestroyPhysicBody(b2Body* pBody)
{
    // remove from collider map
    _bodyToColliderMap.erase(pBody);

    // remove from physical world
    _pPhysicWorld->DestroyBody(pBody);
}

void PhysicsManager::Tick()
{
    auto pSceneMgr = Game::GetManager<SceneManager>();
    auto pPlayer = pSceneMgr->GetPlayerEntity();
    auto pPlayerCollider = pPlayer->GetComponent<CompCollider>();
    auto playerPhyPos = pPlayerCollider->GetPhysicalWorldPosition();

    // update physics world
    _pPhysicWorld->Step(Game::GetDeltaTime(), velocityIterations, positionIterations);

    playerPhyPos = pPlayerCollider->GetPhysicalWorldPosition();

    // sync all physics world position to real world position
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

