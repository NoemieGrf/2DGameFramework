#pragma once

#include <vector>
#include <string>

#include "../GameManagerTypeGetter.h"
#include "../../Config/GlobalSetting.h"
#include "../../Config/PlayerSetting.h"
#include "../../Config/MonsterSetting.h"
#include "../../Config/SceneSetting.h"
#include "../../Config/LevelSetting.h"

class ConfigManager: public GameManagerTypeGetter<GameManagerType::Config>
{
public:
    ConfigManager();

public:
    auto GetGlobalSetting() const -> const GlobalSetting&;
    auto GetLevelSetting() const -> const LevelSetting&;
    auto GetPlayerSetting() const -> const PlayerSetting&;
    auto GetMonsterSetting() const -> const MonsterSetting&;
    auto GetSceneSetting() const -> const SceneSetting&;

    auto GetMapData() const -> const std::vector<std::string>&;

private:
    auto LoadGlobalSetting() -> void;
    auto LoadLevelSetting() -> void;
    auto LoadPlayerSetting() -> void;
    auto LoadMonsterSetting() -> void;
    auto LoadSceneSetting() -> void;

    auto LoadMap() -> void;

private:
    // json setting
    GlobalSetting _globalSetting = {};
    LevelSetting _levelSetting = {};
    PlayerSetting _playerSetting = {};
    MonsterSetting _monsterSetting = {};
    SceneSetting _sceneSetting = {};

    // txt setting
    std::vector<std::string> _mapData = {};
};