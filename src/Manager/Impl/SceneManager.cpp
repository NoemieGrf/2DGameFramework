#include "SceneManager.h"

#include "../../Game/Game.h"
#include "../../Manager/Impl/ConfigManager.h"

void SceneManager::InitLevel() 
{
    const ConfigManager* pConfigMgr = Game::GetManager<ConfigManager>();

    // create ground map
    const auto& mapData = pConfigMgr->GetMapData();



}

Entity* SceneManager::GetEntity(uint uid) const
{
    auto itr = _allEntitiesMap.find(uid);
    if (itr == _allEntitiesMap.end())
        return nullptr;

    return itr->second.get();
}

Entity* SceneManager::GetPlayerEntity() const 
{
    return GetEntity(_playerGuid);
}