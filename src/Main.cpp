
#include "Game.h"

int main()
{
    Game g;
    g.InitConfig();
    g.InitWindow();
    g.InitScene();

    g.Run();

    g.Destroy();

    return 0;
}