#pragma once

#include <vector>
#include <string>
#include "../Game/GlobalDefine.h"

class Map
{
public:
    Map();

public:
    auto Clear() -> void;
    auto SetPlayerBornCoord(const vec2i& coord);
    auto AddGroundTile(const vec2i& tile);
    auto AddMonsterBornCoord(const vec2i& coord, const std::string& monsterConfigName);

public:
    auto GetPlayerBornCoord() const -> const vec2i&;
    auto GetGroundTileCoords() const -> const std::vector<vec2i>&;
    auto GetMonstersBornCoords() const -> const umap<vec2i, std::string, vec2iHash>&;

private:
    vec2i _playerBornCoord;
    std::vector<vec2i> _ground;
    umap<vec2i, std::string, vec2iHash> _monstersBornCoord;
};