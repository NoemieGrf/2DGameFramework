#pragma once

#include <string>
#include "Game/GlobalDefine.h"
#include "Animation/AnimTransCondition.h"

struct AnimationConfig
{
    // this animation name
    std::string animName;

    // this animation name in spine skeleton
    std::string spineName;

    // is loop animation
    bool isLoop;

    // all transitions from this animation
    umap<std::string /* trans target anim */, std::vector<uptr<AnimTransCondition>>> transitions;
};

struct AnimatorConfig
{
    umap<std::string /* config anim name */, AnimationConfig> animationConfigMap;
};

struct AnimationSetting
{
public:
    umap<std::string /* animator name */, AnimatorConfig> animatorConfigMap;

public:
    auto GetAnimatorConfig(const std::string& animatorName) const -> const AnimatorConfig*;
};