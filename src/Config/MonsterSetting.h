#pragma once

#include <string>
#include <unordered_map>

struct MonsterConfig
{
    std::string monsterName;
};

struct MonsterSetting
{
    std::unordered_map<std::string, MonsterConfig> monsterConfig;
    std::unordered_map<char, std::string> monsterMapMark;
};