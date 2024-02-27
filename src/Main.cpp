
#include "Game/Game.h"

int main()
{
    Game::GetInstance()->Init();
    Game::GetInstance()->GameLoop();
    Game::GetInstance()->Destroy();
    return 0;
}