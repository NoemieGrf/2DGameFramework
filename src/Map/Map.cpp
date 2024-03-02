#include "Map.h"

Map::Map() = default;

auto Map::Clear() -> void
{
    _playerBornCoord = vec2i{0, 0};
    _ground.clear();
    _monstersBornCoord.clear();
}

auto Map::AddGroundTile(const vec2i& tile) -> void
{
    _ground.push_back(tile);
}

auto Map::SetPlayerBornCoord(const vec2i& coord) -> void
{
    _playerBornCoord = coord;
}

auto Map::AddMonsterBornCoord(const vec2i& coord, const std::string& monsterConfigName) -> void
{
    _monstersBornCoord[coord] = monsterConfigName;
}

auto Map::GetPlayerBornCoord() const -> const vec2i&
{
    return _playerBornCoord;
}

auto Map::GetGroundTileCoords() const -> const std::vector<vec2i>&
{
    return _ground;
}

auto Map::GetMonstersBornCoords() const -> const umap<vec2i, std::string, vec2iHash>&
{
    return _monstersBornCoord;
}
