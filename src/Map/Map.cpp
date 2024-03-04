#include "Map.h"

Map::Map() = default;

Map::TileFunction Map::GetTileFunctionFromMapMark(char c)
{
    auto itr = _mapMapToTileFunction.find(c);
    if (itr != _mapMapToTileFunction.end())
        return itr->second;

    return Map::TileFunction::Air;
}

void Map::Clear()
{
    _playerBornCoord = vec2i{0, 0};
    _tileMap.clear();
}

void Map::SetMapTileSize(int x, int y)
{
    _tileMap.resize(x);
    for (auto& layer: _tileMap)
    {
        layer.resize(y);
        std::fill(layer.begin(), layer.end(), TileFunction::Air);
    }
}

void Map::SetTileFunction(const vec2i& coord, TileFunction f)
{
    _tileMap[coord.x][coord.y] = f;
    if (f == TileFunction::PlayerBorn)
        _playerBornCoord = coord;
}

Map::TileFunction Map::GetFunctionality(const vec2i& coord) const
{
    return _tileMap[coord.x][coord.y];
}

const vec2i& Map::GetPlayerBornTileCoordinate() const
{
    return _playerBornCoord;
}

std::vector<std::vector<Map::TileFunction>>& Map::GetTileMap()
{
    return _tileMap;
}

