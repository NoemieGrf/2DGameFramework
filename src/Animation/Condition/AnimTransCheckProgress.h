#pragma once

#include "AnimTransCondition.h"

class AnimTransCheckProgress: public AnimTransCondition
{
public:
    explicit AnimTransCheckProgress(float ratio);

public:
    bool Check(Entity* pEntity) override;

private:
    float _ratio;
};