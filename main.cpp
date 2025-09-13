#include "Player.h"
#include "Game.h"

#include <iostream>

int main()
{
    PlayerList players{
        Player{0, 2},
        Player{1, 3},
        Player{2, 0},
        Player{3, 1},
    };
    Game belot;
    int counter = 0;
    while (true)
    {
        int winning_team = belot.Start(players);
        if (counter % 100000 == 0)
        {
            std::cout << counter << std::endl;
        }
        counter++;
    }
}
