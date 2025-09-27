#include "Round.h"

#include "Announce.h"
#include "BiddingState.h"
#include "PlayingState.h"
#include "ScoringState.h"
#include "Premiums.h"
#include <algorithm>
#include <cstdlib>

DeckIterator DealEachPlayer(PlayerList& players, int cards, DeckIterator it);

Round::Round()
{
    cards_played_.reserve(DECK_SIZE);
}

Round::~Round()
{
}

void Round::Deal(PlayerList& players)
{
}

RoundResults Round::Play(PlayerList& players, uint8_t starting_player)
{
    //Consider starting player and dealing clockwise or counterclockwise
    //Does dealing direction have any significance in Belot?
    auto deck_iterator = DealEachPlayer(players, FIRST_DEAL, std::begin(deck));
    deck_iterator = DealEachPlayer(players, SECOND_DEAL, deck_iterator);

    auto [announce, announcing_team] = GamePlay::Bidding(players, starting_player);
    //DEBUG::LOG("Last Bid: " + std::string{AnnounceToString(announce)});
    if (announce == Announce::Pass)
    {
        for (auto& player: players)
        {
            player.ClearHand();
        }
        return RoundResults{};
    }
    DealEachPlayer(players, THIRD_DEAL, deck_iterator);

    //Is sorting each player's cards necessary like we sort them in real life?
    //It makes analysing premiums easier...
    std::ranges::for_each(players, [](auto& player)
            {
                //DEBUG::LOG("Player: " + std::to_string(player.GetID()));
                //PrintHand(player.GetHand());
                player.Sort();
            });

    std::array<Hand, PLAYERS_COUNT> original_hand;
    std::ranges::for_each(players, [&original_hand, announce](auto& player)
            {
                original_hand.at(player.GetID()) = player.GetHand();
                //Think of a way to make this with one comparison...
                if (announce != Announce::NoTrumps ||
                    announce != Announce::ReDoubleNoTrump ||
                    announce != Announce::DoubleNoTrump)
                {
                    AnalyseHandForPremiums(player.GetHand());
                }
            });

    //TODO(Mario): Need to add logic for analysing premiums and pass it to scoring function
    //TODO(Mario): Need to add logic for belot K/Q
    auto round_results = GamePlay::Playing(players, starting_player, announce);

    //DEBUG::LOG("T1 : " + str(points.team_1));
    //DEBUG::LOG("T2 : " + str(points.team_2));

    int valat = (round_results.T1_won_tricks == 0 || round_results.T2_won_tricks == 0)
                    ? TEAM_1_ID
                    : TEAM_2_ID;

    return GamePlay::Scoring(announce,
                             round_results.T1_points,
                             round_results.T2_points,
                             valat,
                             announcing_team);
}

DeckIterator DealEachPlayer(PlayerList& players, int cards, DeckIterator it)
{
    for (auto& player : players)
    {
        for (size_t card = 0; card < cards; card++)
        {
            player.OnDeal(*it);
            it = std::next(it);
        }
    }
    return it;
}

