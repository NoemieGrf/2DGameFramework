#include "PhysicsManager.h"
#include "../../Game/Game.h"
#include "ConfigManager.h"

PhysicsManager::PhysicsManager()
{
    const ConfigManager* pConfigMgr = Game::GetManager<ConfigManager>();
    b2Vec2 grivity { 0.0f, -pConfigMgr->GetGlobalSetting().globalGrivity };

    pPhysicWorld = new b2World(grivity);
}
