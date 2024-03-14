#pragma once

#include <queue>
#include <string>
#include <optional>
#include "../ComponentTypeGetter.h"

class CompAnimator : public ComponentTypeGetter<ComponentType::Animator>
{
public:
    void Update();

public:
    auto EnqueueTrigger(const std::string& trigger) -> void;
    auto DequeueTrigger() -> std::optional<std::string>;

private:
    std::queue<std::string> _animTriggers;
    
};