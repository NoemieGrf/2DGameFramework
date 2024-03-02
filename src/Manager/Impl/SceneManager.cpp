#include "SceneManager.h"

#include "../../Game/Game.h"
#include "../../Manager/Impl/ConfigManager.h"

void SceneManager::InitLevel() 
{
    InitMap();
}

void SceneManager::InitMap()
{
    const ConfigManager* pConfigMgr = Game::GetManager<ConfigManager>();
    const auto& mapData = pConfigMgr->GetMapData();
    const auto& monsterSetting = pConfigMgr->GetMonsterSetting();

    // map tile coord
    _levelMap.Clear();
    for (int i = (int)mapData.size() - 1; i >= 0; i--)
    {
        const std::string& thisLayerMap = mapData[i];
        const int mapLengthThisLayer = static_cast<int>(thisLayerMap.size());

        for (int j = 0; j < mapLengthThisLayer - 1; j++)
        {
            const auto tileCoord = vec2i {static_cast<int>(mapData.size()) - 1 - i, j};
            switch (thisLayerMap[j])
            {
            case '*':   // chunk
                _levelMap.AddGroundTile(tileCoord);
                break;
            case '0':   // player born point
                _levelMap.SetPlayerBornCoord(tileCoord);
                break;
            default:
                char monsterMark = thisLayerMap[j];
                if (monsterSetting.monsterMapMark.contains(monsterMark))
                {
                    const std::string& monsterName = monsterSetting.monsterMapMark.at(monsterMark);
                    if (monsterSetting.monsterConfig.contains(monsterName))
                        _levelMap.AddMonsterBornCoord(tileCoord, monsterName);
                }
                break;
            }
        }
    }
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
