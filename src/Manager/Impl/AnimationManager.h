#pragma once

#include "../GameManagerTypeGetter.h"

class AnimationManager: public GameManagerTypeGetter<GameManagerType::Animation>
{
public:
    void Tick() override;
};