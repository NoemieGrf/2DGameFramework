
#include "Game/Game.h"

int main()
{
    Game::GetInstance()->InitConfig();
    Game::GetInstance()->InitWindow();
    Game::GetInstance()->InitScene();
    Game::GetInstance()->GameLoop();
    Game::GetInstance()->Destroy();
    return 0;
}