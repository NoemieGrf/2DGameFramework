#pragma once

#include <string>
#include <unordered_map>

struct SpineData
{
    std::string name;
    std::string jsonPath;
    std::string atlasPath;
    float loadScale;
};

struct SpineSetting
{
    std::unordered_map<std::string, SpineData> allSpineData;
};