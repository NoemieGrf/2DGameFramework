#include "ConfigManager.h"

#include <fstream>
#include "nlohmann/json.hpp"
#include "../../Utility/Logger.h"

static nlohmann::json LoadJsonFile(const std::string& filePath)
{
    nlohmann::json json;
    std::ifstream configJsonFile(filePath);
    if (!configJsonFile.is_open())
    {
        Logger::LogError(std::string("File open failed: ") + filePath);
        return json;
    }

    configJsonFile >> json;
    configJsonFile.close();

    return json;
}

ConfigManager::ConfigManager()
{
    LoadGlobalSetting();
    LoadPlayerSetting();
    LoadMonsterSetting();
    LoadSceneSetting();
}

void ConfigManager::LoadGlobalSetting()
{
    nlohmann::json json = LoadJsonFile("./config/GlobalSetting.json");
    _globalSetting.globalGrivity = json["globalGrivity"];
}

void ConfigManager::LoadLevelSetting()
{
    nlohmann::json json = LoadJsonFile("./config/LevelSetting.json");
}

void ConfigManager::LoadPlayerSetting()
{
    nlohmann::json json = LoadJsonFile("./config/PlayerSetting.json");
    _playerSetting.imagePath = json["imagePath"];
    _playerSetting.initMaxHp = json["initMaxHp"];
    _playerSetting.initMaxMp = json["initMaxMp"];
}

void ConfigManager::LoadMonsterSetting()
{
    nlohmann::json json = LoadJsonFile("./config/MonsterSetting.json");
}

void ConfigManager::LoadSceneSetting()
{
    nlohmann::json json = LoadJsonFile("./config/SceneSetting.json");
}

const GlobalSetting& ConfigManager::GetGlobalSetting() const
{
    return _globalSetting;
}

const LevelSetting& ConfigManager::GetLevelSetting() const
{
    return _levelSetting;
}

const PlayerSetting& ConfigManager::GetPlayerSetting() const
{
    return _playerSetting;
}

const MonsterSetting& ConfigManager::GetMonsterSetting() const
{
    return _monsterSetting;
}

const SceneSetting& ConfigManager::GetSceneSetting() const
{
    return _sceneSetting;
}