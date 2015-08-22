
#include <iostream>

#include "game.h"

int main()
{
    Game game;

    game.setup();
    while(game.isDone() == false)
    {
        game.loop();
    }
    game.cleanup();
    return 0;
}
