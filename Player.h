#pragma once

#include "Deck.h"
#include "Defs.h"
#include <vector>

inline constexpr int PLAYERS_COUNT = 4;

using PlayerID = int;
using Hand = std::array<std::vector<Card>, SUITS>;

class Player
{
public:
    Player(PlayerID player_id, PlayerID teammate_id);
    void OnDeal(const Card& card);
    void Sort();
    Hand& GetHand();
    void ClearHand();
    PlayerID GetTeammateID();
    PlayerID GetID();
private:
    Hand hand_;
    PlayerID player_id_{0};
    PlayerID teammate_id_{0};
};

using PlayerList = std::array<Player, PLAYERS_COUNT>;
