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
    LoadMap();
}

auto ConfigManager::LoadGlobalSetting() -> void
{
    nlohmann::json json = LoadJsonFile("./config/GlobalSetting.json");
    _globalSetting.globalGravity = json["globalGrivity"];
    _globalSetting.levelMapPath = json["levelMapPath"];
}

auto ConfigManager::LoadLevelSetting() -> void
{
    nlohmann::json json = LoadJsonFile("./config/LevelSetting.json");
}

auto ConfigManager::LoadPlayerSetting() -> void
{
    nlohmann::json json = LoadJsonFile("./config/PlayerSetting.json");
    _playerSetting.imagePath = json["imagePath"];
    _playerSetting.initMaxHp = json["initMaxHp"];
    _playerSetting.initMaxMp = json["initMaxMp"];
}

auto ConfigManager::LoadMonsterSetting() -> void
{
    nlohmann::json json = LoadJsonFile("./config/MonsterSetting.json");

    // all monster detail
    for (auto monsterConfigJson: json["allConfig"])
    {
        MonsterConfig config;
        config.monsterName = monsterConfigJson["name"];
        _monsterSetting.monsterConfig[config.monsterName] = config;
    }

    // monster mark
    for (auto monsterMapMarkJson: json["monsterMapMark"])
    {
        std::string mark = monsterMapMarkJson["mark"];
        std::string monster = monsterMapMarkJson["monster"];
        _monsterSetting.monsterMapMark[mark[0]] = monster;
    }
}

auto ConfigManager::LoadSceneSetting() -> void
{
    nlohmann::json json = LoadJsonFile("./config/SceneSetting.json");
}

auto ConfigManager::LoadMap() -> void
{
    std::ifstream txtFile(_globalSetting.levelMapPath);
    if (!txtFile.is_open())
    {
        Logger::LogError(std::string("File open failed: ") + _globalSetting.levelMapPath);
        return;
    }

    _mapData.clear();
    if (std::string lineContent; std::getline(txtFile, lineContent))
        _mapData.push_back(std::move(lineContent));

    txtFile.close();
}

auto ConfigManager::GetGlobalSetting() const -> const GlobalSetting&
{
    return _globalSetting;
}

auto ConfigManager::GetLevelSetting() const -> const LevelSetting&
{
    return _levelSetting;
}

auto ConfigManager::GetPlayerSetting() const -> const PlayerSetting&
{
    return _playerSetting;
}

auto ConfigManager::GetMonsterSetting() const -> const MonsterSetting&
{
    return _monsterSetting;
}

auto ConfigManager::GetSceneSetting() const -> const SceneSetting&
{
    return _sceneSetting;
}

auto ConfigManager::GetMapData() const -> const std::vector<std::string>&
{
    return _mapData;
}
