#include "PhysicsManager.h"
#include "../../Game/Game.h"
#include "ConfigManager.h"


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

