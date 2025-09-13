#pragma once

#include "Player.h"
#include "Announce.h"
#include "RoundData.h"

namespace GamePlay
{

RoundResults Playing(PlayerList& players,
                     int starting_player,
                     Announce announce);
}
