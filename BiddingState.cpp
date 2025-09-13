#include "BiddingState.h"
#include "Debug.h"

//TODO(Mario): Remove this
#include <random>
static std::random_device rd; // obtains a random number from hardware
static std::mt19937 g(rd());  // seeds the random number generator

std::pair<Announce, PlayerID> Bid(Announce highest_bid, PlayerID player_that_bid_highest, Player& player)
{
    bool last_bid_from_teammate = false;
    player_that_bid_highest ==
        player.GetTeammateID() ? last_bid_from_teammate = true : last_bid_from_teammate = false;

    std::vector<Announce>* possible_announces;
    last_bid_from_teammate == true
        ? possible_announces = &possible_announces_teammate[highest_bid]
        : possible_announces = &possible_announces_nonteammate[highest_bid];
    int possible_announces_begin = 0;
    int possible_announces_end = 0;
    possible_announces_end = possible_announces->size();

    //TODO(Mario): For now I'm using just a brute random algorithm. But I should consider
    //using more sophisticated method for figuring which bid to make based on certain
    //criteria
    Announce last_highest_bid = highest_bid;
    std::uniform_int_distribution<int> dist(possible_announces_begin,
                                            possible_announces_end - 1);
    int generated_bid_index = dist(rd);

    Announce new_bid = (*possible_announces)[generated_bid_index];
    //LOG("Player: " + std::to_string(player.GetID()));
    //LOG("Bid: " + std::string{AnnounceToString(new_bid)});
    if (new_bid != Announce::Pass)
    {
        last_highest_bid = new_bid;
        player_that_bid_highest = player.GetID();
    }
    return {last_highest_bid, player_that_bid_highest};
};

std::pair<Announce, TeamID> GamePlay::Bidding(PlayerList& players, PlayerID starting_player)
{
    //TODO(Mario): Need to add logic for analysing premiums they can factor in
    //bidding decision making

    PlayerID current_player_id = starting_player;
    PlayerID player_that_made_highest_bid = -1;
    Announce highest_announce = Announce::Pass;
    Announce last_announce = Announce::None;
    do
    {
        for (size_t turn = 0; turn < PLAYERS_COUNT; turn++)
        {
            last_announce = highest_announce;
            Player& current_player = players.at(current_player_id%PLAYERS_COUNT);
            auto last_bid_result = Bid(highest_announce, player_that_made_highest_bid, current_player);
            highest_announce = last_bid_result.first;
            player_that_made_highest_bid = last_bid_result.second;
            current_player_id++;
        }
    } while (last_announce != highest_announce);

    TeamID announce_from_team = -1;
    (player_that_made_highest_bid == 0 || player_that_made_highest_bid == 2)
        ? announce_from_team = TEAM_1_ID
        : announce_from_team = TEAM_2_ID;

    return {highest_announce, announce_from_team};
}
