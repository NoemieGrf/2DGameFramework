#pragma once

#include "GameManager.h"

template <GameManagerType T>
class GameManagerTypeGetter: public GameManager
{
public:
    GameManagerType GetType() override
    {
        return T;
    }

    static GameManagerType Type()
    {
        return T;
    }
};