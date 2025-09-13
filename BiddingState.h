#pragma once

#include "Announce.h"
#include "Player.h"

namespace GamePlay
{
    std::pair<Announce, TeamID> Bidding(PlayerList& players, PlayerID starting_player);
}
