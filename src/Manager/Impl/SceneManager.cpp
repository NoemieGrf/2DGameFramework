#include "SceneManager.h"

#include <sstream>
#include "../../Entity/EntityFactory.h"
#include "../../Game/Game.h"
#include "ConfigManager.h"
#include "ResourceManager.h"
#include "../../Component/Impl/CompSpine.h"

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

            // make entity name
            std::stringstream nameStringBuilder;
            nameStringBuilder << "Tile_" << (int)tileCoord.x << "_" << (int)tileCoord.y;
            std::string entityName = nameStringBuilder.str();

            // make png wanted size
            auto [guid, pEntity] = EntityFactory::CreateGadget(
                wallPngPath, 
                wallCenter, 
                vec2f{ 1, 1 }, 
                entityName
                );

            _allEntitiesMap[guid] = std::move(pEntity);
        }
    }
}

void SceneManager::InitPlayer()
{
    ConfigManager* pConfigMgr = Game::GetManager<ConfigManager>();
    ResourceManager* pResMgr = Game::GetManager<ResourceManager>();

    // calculate the born coordinate
    vec2f playerBornTilePos = VecConvert<int, float>(_levelMap.GetPlayerBornTileCoordinate());
    vec2f playerBornWorldPos = playerBornTilePos + vec2f{ 0.5f, 0.5f };

    // calculate the width-height scale of avatar
    const auto* pSpineRes = pResMgr->GetSpineResource(pConfigMgr->GetPlayerSetting().spineName);
    float avatarWidthHeightScale = pSpineRes->GetSkeletonWidthHeightScale();

    // create player
    auto [guid, pEntity] = EntityFactory::CreatePlayer(playerBornWorldPos, vec2f{ 1, 1 / avatarWidthHeightScale });
    _playerGuid = guid;

    // set idle animation
    CompSpine* pPlayerSpine = pEntity->GetComponent<CompSpine>();
    pPlayerSpine->SetFlip(true);
    pPlayerSpine->SetAnimation("Wait1Loop", true);

    _allEntitiesMap[guid] = std::move(pEntity);
}

uint SceneManager::GetPlayerEntityGuid() const
{
    return _playerGuid;
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
