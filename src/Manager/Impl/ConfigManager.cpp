#include "ConfigManager.h"

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

static nlohmann::json LoadJsonFile(const std::string& filePath)
{
    nlohmann::json json;
    std::ifstream configJsonFile(filePath);
    if (!configJsonFile.is_open())
    {
        std::cout << "File open failed: " << filePath << std::endl;
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