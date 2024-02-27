#pragma once

#include "../../Utility/Noncopyable.h"
#include "GameManagerType.h"

class GameManager: public Noncopyable
{
public:
    virtual void Tick() = 0;
    virtual void LateTick() = 0;
    virtual GameManagerType GetType() = 0;
};