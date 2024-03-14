#pragma once

#include <string>
#include "Game/GlobalDefine.h"
#include "Animation/Condition/AnimTransCondition.h"

struct AnimationTransitionMap
{
    umap<std::string /* trans target anim */, std::vector<uptr<AnimTransCondition>>> conditions;
};

struct AnimationSetting
{
    umap<std::string, AnimationTransitionMap> animationMap;
};