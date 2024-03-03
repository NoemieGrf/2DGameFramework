#pragma once

#include <vector>
#include <string>
#include "../Game/GlobalDefine.h"

class Map
{
public:
    Map();

public:
    enum class TileFunction
    {
        Air,
        Ground,
        PlayerBorn,
        MonsterBornA,
        MonsterBornB,
        MonsterBornC,
    };

    inline static umap<char, TileFunction> _mapMapToTileFunction = {
        {' ', TileFunction::Air,},
        {'*', TileFunction::Ground,},
        {'0', TileFunction::PlayerBorn,},
        {'A', TileFunction::MonsterBornA,},
        {'B', TileFunction::MonsterBornB,},
        {'C', TileFunction::MonsterBornC,},
    };

    static auto GetTileFunctionFromMapMark(char c) -> TileFunction;

public:
    auto Clear() -> void;
    auto SetTileScale(int x, int y) -> void;
    auto SetTileFunction(const vec2i& coord, TileFunction f) -> void;
    auto GetFunctionality(const vec2i& coord) const -> TileFunction;
    auto GetPlayerBornTileCoordinate() const -> const vec2i&;
    auto GetTileMap() -> std::vector<std::vector<TileFunction>>&;

private:
    vec2i _playerBornCoord;
    std::vector<std::vector<TileFunction>> _tileMap;
};