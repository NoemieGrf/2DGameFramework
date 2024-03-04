#include "SceneManager.h"

#include "../../Entity/EntityFactory.h"
#include "../../Game/Game.h"
#include "../../Manager/Impl/ConfigManager.h"

void SceneManager::InitLevel() 
{
    InitMap();
    InitPlayer();
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
    _levelMap.SetMapTileSize(xMax, yMax);

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

    // create all wall
    auto wallPngPath = pConfigMgr->GetGlobalSetting().levelWallTexPath;
    auto tileMap = _levelMap.GetTileMap();
    for (int i = 0; i < tileMap.size() - 1; i++)
    {
        for (int j = 0; j < tileMap[i].size() - 1; j++)
        {
            if (tileMap[i][j] != Map::TileFunction::Ground)
                continue;

            vec2f tileCoord = vec2f( i, j );
            vec2f wallCenter = tileCoord + vec2f{ 0.5f, 0.5f };
            auto [guid, pEntity] = EntityFactory::CreateGadget(wallPngPath, wallCenter, vec2f{ 1, 1 });
            _allEntitiesMap[guid] = std::move(pEntity);
        }
    }
}

void SceneManager::InitPlayer()
{
    vec2f playerBornTilePos = VecConvert<int, float>(_levelMap.GetPlayerBornTileCoordinate());
    vec2f playerBornWorldPos = playerBornTilePos + vec2f{ 0.5f, 0.5f };
    auto [guid, pEntity] = EntityFactory::CreatePlayer(playerBornWorldPos, vec2f{ 1, 1 });
    _playerGuid = guid;
    _allEntitiesMap[guid] = std::move(pEntity);
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
