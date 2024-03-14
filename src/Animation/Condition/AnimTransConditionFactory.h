#pragma once

#include <string>
#include "Game/GlobalDefine.h"
#include "AnimTransCondition.h"

class AnimTransCheckerFactory
{
public:
    AnimTransCheckerFactory() = delete;

public:
    static uptr<AnimTransCondition> CreateValueChecker(const std::string& operationType, const std::string& sourceType, float targetValue);
    static uptr<AnimTransCondition> CreateProgressChecker(float progress);
    static uptr<AnimTransCondition> CreateTriggerChecker(const std::string& triggerName);
    static uptr<AnimTransCondition> CreateStateChecker(const std::string& state, int value);

};