#pragma once

#include <string>
#include "AnimTransCondition.h"

class AnimTransCheckTrigger: public AnimTransCondition
{
public:
    explicit AnimTransCheckTrigger(const std::string& targetTrigger);

public:
    bool Check(Entity* pEntity) override;

private:
    std::string _targetTrigger;
};