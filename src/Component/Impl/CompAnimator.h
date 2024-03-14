#pragma once

#include <queue>
#include <string>
#include <optional>
#include "Component/ComponentTypeGetter.h"
#include "Config/AnimationSetting.h"

class CompAnimator : public ComponentTypeGetter<ComponentType::Animator>
{
public:
    void Update();

    /* Trigger */
    auto EnqueueTrigger(const std::string& trigger) -> void;
    auto DequeueTrigger() -> std::optional<std::string>;

    /* Setter & Getter */
    auto SetAnimationTransitionMap(const AnimatorConfig* map) -> void;

private:
    // animator triggers
    std::queue<std::string> _animTriggers;

    // animator config
    const AnimatorConfig* _animationTransitionMap;

    // current
    std::string _currentState;
    
};