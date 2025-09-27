#include "Player.h"

#include "Game.h"

//#include "Debug.h"
//#include "Utility.h"

int main()
{
    //This logic is for testing purposes only
    PlayerList players{
        Player{0, 2},
        Player{1, 3},
        Player{2, 0},
        Player{3, 1},
    };
    Game belot;
    while (true)
    {
        int winning_team = belot.Start(players);
        //DEBUG::LOG("Winning team: " + str(winning_team));
    }
}
