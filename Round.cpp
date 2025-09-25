#include "Round.h"

#include "Announce.h"
#include "BiddingState.h"
#include "PlayingState.h"
#include "ScoringState.h"
#include "Premiums.h"

DeckIterator DealEachPlayer(PlayerList& players, int cards, DeckIterator it);

Round::Round()
{
    cards_played_.reserve(DECK_SIZE);
}

void Round::Deal(PlayerList& players)
{
}

RoundResults Round::Play(PlayerList& players, int starting_player)
{
    //Consider starting player and dealing clockwise or counterclockwise
    auto deck_iterator = DealEachPlayer(players, FIRST_DEAL, std::begin(deck));
    deck_iterator = DealEachPlayer(players, SECOND_DEAL, deck_iterator);

    std::pair<Announce, TeamID> announce = GamePlay::Bidding(players, starting_player);
    //LOG("Last Bid: " + std::string{AnnounceToString(announce)});
    if (announce.first == Announce::Pass) return RoundResults{};
    DealEachPlayer(players, THIRD_DEAL, deck_iterator);

    //TODO(Mario): Is sorting necessary?
    for (auto& player : players)
    {
        player.Sort();
        //LOG("Player: " + std::to_string(player.GetID()));
        //PrintHand(player.GetHand());
    }

    std::array<Hand, PLAYERS_COUNT> original_hand;
    for (auto& player: players)
    {
        //std::cout << player.GetID() << std::endl;
        original_hand.at(player.GetID()) = player.GetHand();
        AnalyseHandForPremiums(player.GetHand());
        //for (auto suit_cards: player.GetHand())
        //{
            //for (auto card: suit_cards)
            //{
                //DEBUG::LOG(card);
            //}
        //}
        //std::cout << std::endl;
    }

    //TODO(Mario): Need to add logic for analysing premiums they can factor in
    //bidding decision making

    //TODO(Mario): Need to add logic for analysing premiums and pass it to scoring function
    //TODO(Mario): Need to add logic for belot K/Q
    auto round_results = GamePlay::Playing(players, starting_player, announce.first);

    //std::cout << "T1 : " << points.team_1 << std::endl;
    //std::cout << "T2 : " << points.team_2 << std::endl;

    int valat = -1;
    if (round_results.T1_won_tricks == 0 || round_results.T2_won_tricks == 0)
    {
        round_results.T1_won_tricks == 0 ? valat = TEAM_1_ID : valat = TEAM_2_ID;
    }

    return GamePlay::Scoring(announce.first,
                             round_results.T1_points,
                             round_results.T2_points,
                             valat,
                             announce.second);
}

DeckIterator DealEachPlayer(PlayerList& players, int cards, DeckIterator it)
{
    DeckIterator it_ = it;
    for (auto& player : players)
    {
        for (size_t card = 0; card < cards; card++)
        {
            player.OnDeal(*it_);
            it_ = std::next(it_);
        }
    }
    return it_;
}

