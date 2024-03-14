#pragma once

#include <vector>
#include <string>

#include "../GameManagerTypeGetter.h"
#include "../../Config/GlobalSetting.h"
#include "../../Config/AnimationSetting.h"
#include "../../Config/PlayerSetting.h"
#include "../../Config/MonsterSetting.h"
#include "../../Config/SceneSetting.h"
#include "../../Config/LevelSetting.h"
#include "../../Config/SpineSetting.h"

class ConfigManager: public GameManagerTypeGetter<GameManagerType::Config>
{
public:
    ConfigManager();

public:
    auto GetGlobalSetting() const -> const GlobalSetting&;
    auto GetSpineSetting() const -> const SpineSetting&;
    auto GetAnimationSetting() const -> const AnimationSetting&;
    auto GetLevelSetting() const -> const LevelSetting&;
    auto GetPlayerSetting() const -> const PlayerSetting&;
    auto GetMonsterSetting() const -> const MonsterSetting&;
    auto GetSceneSetting() const -> const SceneSetting&;

    auto GetMapData() const -> const std::vector<std::string>&;

private:
    auto LoadGlobalSetting() -> void;
    auto LoadSpineSetting() -> void;
    auto LoadAnimationSetting() -> void;
    auto LoadLevelSetting() -> void;
    auto LoadPlayerSetting() -> void;
    auto LoadMonsterSetting() -> void;
    auto LoadSceneSetting() -> void;

    auto LoadMap() -> void;

private:
    // json setting
    GlobalSetting _globalSetting = {};
    SpineSetting _spineSetting = {};
    AnimationSetting _animationSetting = {};
    LevelSetting _levelSetting = {};
    PlayerSetting _playerSetting = {};
    MonsterSetting _monsterSetting = {};
    SceneSetting _sceneSetting = {};

    // txt setting
    std::vector<std::string> _mapData = {};
};