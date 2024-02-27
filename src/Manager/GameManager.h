#pragma once

#include "../Utility/Noncopyable.h"
#include "GameManagerType.h"

class GameManager: public Noncopyable
{
public:
    virtual ~GameManager();

public:
    virtual void PreTick();
    virtual void Tick();
    virtual void LateTick();
    virtual GameManagerType GetType() = 0;
};