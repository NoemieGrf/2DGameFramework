#pragma once

#include <functional>
#include "Utility/Noncopyable.h"
#include "Config/AnimationSetting.h"
#include "Condition/AnimTransConditionFactory.h"

class Animator: Noncopyable
{
public:
    using TryAnimationChanged = std::function<bool(const std::string& from, const std::string& to)>;
    using OnAnimationChanged = std::function<void(const std::string& from, const std::string& to)>;

public:
    Animator(const AnimatorConfig* transitionMap, const OnAnimationChanged& onAnimChanged);

public:
    void Update();

private:
    TryAnimationChanged _tryAnimChange;
    OnAnimationChanged _onAnimChanged;
    const AnimatorConfig* _animationTransitionMap;
    std::string _currentAnimation;
};