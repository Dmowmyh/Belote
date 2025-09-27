#pragma once

#include "Player.h"
#include "RoundData.h"

class Round
{
public:
    Round();
    ~Round();
    RoundResults Play(PlayerList& players, uint8_t starting_player);

private:
    void Deal(PlayerList& players);
    std::vector<Card> cards_played_;
};
