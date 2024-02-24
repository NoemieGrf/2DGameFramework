#pragma once

#include "../Game/GlobalDefine.h"

class Tactic
{
public:
    virtual ~Tactic();
    virtual auto UpdatePosition(const vec2f& inputPos) const -> vec2f = 0;
};