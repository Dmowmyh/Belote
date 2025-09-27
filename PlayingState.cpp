#include "PlayingState.h"

#include "Debug.h"
#include <functional>

// clang-format off
/** 7, 8, 9, 10, J, Q, K, A  */
const std::array<int, 8> NoTrumpPoints = {0, 0, 0, 10, 2, 3, 4, 11};
const std::array<int, 8> TrumpPoints = {0, 0, 14, 10, 20, 3, 4, 11};
// clang-format on

bool IsTrump(const Card& card, Announce announce)
{
    if (announce == A::AllTrumps || announce == A::DoubleAllTrump || announce == A::ReDoubleAllTrump)
    {
        return true;
    }
    if (announce == A::Club || announce == A::DoubleClub || announce == A::ReDoubleClub)
    {
        return card.suit_ == Suit::Club;
    }
    if (announce == A::Diamond || announce == A::DoubleDiamond || announce == A::ReDoubleDiamond)
    {
        return card.suit_ == Suit::Diamond;
    }
    if (announce == A::Spade || announce == A::DoubleSpade || announce == A::ReDoubleSpade)
    {
        return card.suit_ == Suit::Spade;
    }
    if (announce == A::Heart || announce == A::DoubleHeart || announce == A::ReDoubleHeart)
    {
        return card.suit_ == Suit::Heart;
    }
    return false;
}

int CalculateHandPoints(const std::vector<Card>& cards, Announce announce)
{
    int points = 0;
    for (const auto& card: cards)
    {
        IsTrump(card, announce) ? points += TrumpPoints[(int)card.rank_] :
            points += NoTrumpPoints[(int)card.rank_];
    }
    return points;
}


bool Trump(const Card& card, const Card& highest_card, Suit suit)
{
    return trump_card_strength[card.rank_] > trump_card_strength[highest_card.rank_];
}

bool NonTrump(const Card& card, const Card& highest_card, Suit suit)
{
    return true;
}

template <Suit suit_>
bool SuitTrumps(const Card& card, const Card& highest_card, Suit suit)
{
    if (suit == suit_)
    {
        return trump_card_strength[card.rank_] > trump_card_strength[highest_card.rank_];
    }
    return non_trump_card_strength[card.rank_] >
           non_trump_card_strength[highest_card.rank_];
}

std::unordered_map<
    Announce,
    std::function<bool(const Card& card, const Card& highest_card, Suit suit)>>
    predicates = {
        {Announce::AllTrumps, Trump},
        {Announce::DoubleAllTrump, Trump},
        {Announce::ReDoubleAllTrump, Trump},
        {Announce::Club, SuitTrumps<Suit::Club>},
        {Announce::DoubleClub, SuitTrumps<Suit::Club>},
        {Announce::ReDoubleClub, SuitTrumps<Suit::Club>},
        {Announce::Diamond, SuitTrumps<Suit::Diamond>},
        {Announce::DoubleDiamond, SuitTrumps<Suit::Diamond>},
        {Announce::ReDoubleDiamond, SuitTrumps<Suit::Diamond>},
        {Announce::Spade, SuitTrumps<Suit::Spade>},
        {Announce::DoubleSpade, SuitTrumps<Suit::Spade>},
        {Announce::ReDoubleSpade, SuitTrumps<Suit::Spade>},
        {Announce::Heart, SuitTrumps<Suit::Heart>},
        {Announce::DoubleHeart, SuitTrumps<Suit::Heart>},
        {Announce::ReDoubleHeart, SuitTrumps<Suit::Heart>},
        {Announce::NoTrumps, NonTrump},
        {Announce::DoubleNoTrump, NonTrump},
        {Announce::ReDoubleNoTrump, NonTrump},
};

Card PlaySuitCard(
    Suit suit,
    std::vector<Card>& suit_cards,
    const std::function<bool(const Card& card, const Card& highest_card, Suit suit)>&
        predicate,
    const Card& highest_card)
{
    Card card_played;
    //id_ == -1 means no card is played
    card_played.id_ = -1;
    using Iter = std::vector<Card>::iterator;
    for (Iter it = suit_cards.begin(); it != suit_cards.end(); it++)
    {
        if (predicate(*it, highest_card, suit))
        {
            card_played = *it;
            suit_cards.erase(it);
            return card_played;
        }
    }

    if (!suit_cards.empty())
    {
        card_played = *suit_cards.begin();
        suit_cards.erase(suit_cards.begin());
    }

    return card_played;
}

Card PlayOtherCard(Hand& hand)
{
    Card card_played;

    for (std::vector<Card>& suit_cards: hand)
    {
        if (!suit_cards.empty())
        {
            auto first_card = suit_cards.begin();
            card_played = *first_card;
            suit_cards.erase(first_card);
            return card_played;
        }
    }

    //We need better randomness/choice here
    return card_played;
}


Card PlayCard(Player& player, Suit required_suit, Card highest_card, Announce announce)
{
    Hand& hand = player.GetHand();

    //No trump case
    if (required_suit == Suit::None)
    {
        return PlayOtherCard(hand);
    }

    Card card_played;
    auto& suit_cards = hand.at(static_cast<int>(required_suit));
    if (!suit_cards.empty())
    {
        card_played = PlaySuitCard(required_suit, suit_cards, predicates[announce], highest_card);
        return card_played;
    }

    return PlayOtherCard(hand);
}

RoundResults GamePlay::Playing(std::array<Player, PLAYERS_COUNT>& players,
                               int starting_player,
                               Announce announce)
{
    int active_player = starting_player;
    int winning_player = starting_player;
    std::vector<Card> current_trick;
    current_trick.reserve(PLAYERS_COUNT);
    Suit leading_suit = Suit::None;
    Card highest_card{};
    RoundResults round_results{};

    for (size_t turn = 0; turn < TURNS; turn++)
    {
        active_player = winning_player;
        leading_suit = Suit::None;
        highest_card = Card{};
        for (size_t player_turn = 0; player_turn < PLAYERS_COUNT; player_turn++)
        {
            Player& player = players[active_player];
            auto card = PlayCard(player, leading_suit, highest_card, announce);
            if (card.id_ > highest_card.id_)
            {
                winning_player = active_player;
                highest_card = card;
            }
            if (current_trick.empty())
            {
                leading_suit = card.suit_;
            }
            current_trick.emplace_back(std::move(card));
            active_player++;
            if (active_player >= PLAYERS_COUNT)
            {
                active_player = 0;
            }
        }
        auto points = CalculateHandPoints(current_trick, announce);
        if (winning_player == 0 || winning_player == 2)
        {
            round_results.T1_points += points;
            round_results.T1_won_tricks += 1;
        }
        else
        {
            round_results.T2_points += points;
            round_results.T2_won_tricks += 1;
        }
        current_trick.clear();
    }

    //Last turn awards +10 points for the winning player
    (winning_player == 0 || winning_player == 2)
        ? round_results.T1_points += 10
        : round_results.T2_points += 10;

    return round_results;
}

