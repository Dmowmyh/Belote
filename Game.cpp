#include "Game.h"

#include "Round.h"
#include "Deck.h"

#include <algorithm>
#include <random>

#include <iostream>

static std::random_device rd; // obtains a random number from hardware
static std::mt19937 g(rd());  // seeds the random number generator

//confidence level
//find a way to play each possible hand the best way possible from each position based
//on the announces we have

int Game::Start(PlayerList& players)
{
    T1_points = 0; T2_points = 0;
    while (T1_points < 152 && T2_points < 152)
    {
        std::shuffle(deck.begin(), deck.end(), g);

        Round round;
        auto round_results = round.Play(players, starting_player);
        starting_player++;
        if (starting_player >= PLAYERS_COUNT) starting_player = 0;
        T1_points += round_results.T1_points;
        T2_points += round_results.T2_points;
    }
    std::cout << (int)T1_points << " " << (int)T2_points << std::endl;
    return T1_points > T2_points;
}
