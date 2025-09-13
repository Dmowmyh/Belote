#pragma once

#include "Player.h"
#include "RoundData.h"

class Round
{
public:
    Round();
    RoundResults Play(PlayerList& players, int starting_player);
    void Deal(PlayerList& players);

private:
    std::vector<Card> cards_played_;
};
