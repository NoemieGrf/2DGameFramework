#include "AnimationSetting.h"

const AnimatorConfig* AnimationSetting::GetAnimatorConfig(const std::string& animatorName) const
{
    auto itr = animatorConfigMap.find(animatorName);
    if (itr == animatorConfigMap.end())
        return nullptr;

    return &itr->second;
}