#pragma once

#include <string>
#include <vector>
#include "../Game/GlobalDefine.h"

struct AnimationBlendPair
{
    std::string from;
    std::string to;
    float mixTime;
};

struct SpineData
{
    std::string name;
    std::string jsonPath;
    std::string atlasPath;
    float loadScale;
    std::vector<AnimationBlendPair> animationData;
};
struct SpineSetting
{
    umap<std::string, SpineData> allSpineData;
};