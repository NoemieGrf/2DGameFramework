#pragma once

#include <string>
#include "Game/GlobalDefine.h"
#include "Animation/Condition/AnimTransCondition.h"

struct AnimatorConfig
{
    umap<std::string /* config anim name */, std::string /* spine anim name */> configAnimNameToSpineAnimNameMap;
    umap<std::string /* trans target anim */, std::vector<uptr<AnimTransCondition>>> transitions;
};

struct AnimationSetting
{
    umap<std::string /* animator name */, AnimatorConfig> animatorConfigMap;
};