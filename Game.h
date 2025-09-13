#pragma once

#include "Player.h"

class Game
{
public:
    int Start(PlayerList& players);

private:
    uint8_t starting_player = 0;
    uint8_t T1_points = 0;
    uint8_t T2_points = 0;
};
