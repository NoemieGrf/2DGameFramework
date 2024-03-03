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
    const std::vector<std::string>& mapData = pConfigMgr->GetMapData();

    // calculate the tile size of this map
    int yMax = mapData.size();
    int xMax = -1;
    for (const auto& layer: mapData)
        xMax = std::max(xMax, (int)layer.size());

    _levelMap.Clear();
    _levelMap.SetTileScale(xMax, yMax);

    // set every map tile functionality
    for (int i = (int)mapData.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < (int)mapData[i].size() - 1; j++)
        {
            vec2i tileCoord = vec2i {j, (int)mapData.size() - 1 - i};
            Map::TileFunction tileFunction = Map::GetTileFunctionFromMapMark(mapData[i][j]);
            _levelMap.SetTileFunction(tileCoord, tileFunction);
        }
    }
}

Entity* SceneManager::GetEntity(uint uid)
{
    auto itr = _allEntitiesMap.find(uid);
    if (itr == _allEntitiesMap.end())
        return nullptr;

    return itr->second.get();
}

Entity* SceneManager::GetPlayerEntity() 
{
    return GetEntity(_playerGuid);
}

umap<uint, uptr<Entity>>& SceneManager::GetSceneEntities()
{
    return _allEntitiesMap;
}
