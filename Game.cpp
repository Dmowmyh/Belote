#include "Game.h"

#include "Round.h"
#include "Deck.h"

#include <algorithm>
#include <random>

static std::random_device rd;
static std::mt19937 g(rd());

int Game::Start(PlayerList& players)
{
    T1_points = 0; T2_points = 0;
    while (T1_points < 152 && T2_points < 152)
    {
        //Shuffle the deck before each round to avoid code complication.
        //Shuffling before each round ensures maximum randomness.
        //In real life the played cards from the last round are used.
        std::shuffle(deck.begin(), deck.end(), g);
        Round round;
        auto round_results = round.Play(players, starting_player);
        starting_player++;
        if (starting_player >= PLAYERS_COUNT) starting_player = 0;
        T1_points += round_results.T1_points;
        T2_points += round_results.T2_points;
        //for (auto& player : players)
            //player.ClearHand();
    }
    return T1_points > T2_points;
}
