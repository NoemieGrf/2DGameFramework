#pragma once

#include <string>
#include "../GameManagerTypeGetter.h"
#include "../../Config/GlobalSetting.h"
#include "../../Config/PlayerSetting.h"
#include "../../Config/MonsterSetting.h"
#include "../../Config/SceneSetting.h"

class ConfigManager: public GameManagerTypeGetter<GameManagerType::Config>
{
public:
    ConfigManager();

public:
    auto GetGlobalSetting() const -> const GlobalSetting&;
    auto GetPlayerSetting() const -> const PlayerSetting&;
    auto GetMonsterSetting() const -> const MonsterSetting&;
    auto GetSceneSetting() const -> const SceneSetting&;

private:
    void LoadGlobalSetting();
    void LoadPlayerSetting();
    void LoadMonsterSetting();
    void LoadSceneSetting();

private:
    GlobalSetting _globalSetting;
    PlayerSetting _playerSetting;
    MonsterSetting _monsterSetting;
    SceneSetting _sceneSetting;

};