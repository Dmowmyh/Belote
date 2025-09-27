#pragma once

#include "Deck.h"
#include "Debug.h"
#include "Player.h"
/*#include "Utility.h"*/

#include <vector>

//The card order for sequences is: 7; 8; 9; 10; J; Q; K; A.

enum Premium
{
    Square100,
    Square150,
    Square200,
    Tierce,
    Quarte,
    Quint,
};


//This function can be faster...
inline bool HasSquare(const Hand& hand, const std::array<CardOrder, 4>& ids)
{
    int8_t count = 0;
    for (const auto& suit_cards: hand)
    {
        for (const auto& card: suit_cards)
        {
            if (card.id_ == ids[0] || card.id_ == ids[1]
                    || card.id_ == ids[2] || card.id_ == ids[3])
            {
                count++;
            }
        }
    }
    return count == 4;
}

inline std::pair<int8_t, int8_t> HasSequence(const std::vector<Card>& suit_cards)
{
    if (suit_cards.size() < 3)
    {
        return {0, 0};
    }

    int sequence_length = 1;
    int highest_card = 0;
    for (size_t i = 0; i < suit_cards.size()-1; ++i)
    {
        if (suit_cards[i].id_ != suit_cards[i+1].id_ - 1)
        {
            break;
        }
        highest_card = suit_cards[i].id_;
        sequence_length++;
    }
    return {sequence_length, highest_card};
}

inline std::vector<std::pair<Premium, int8_t>> AnalyseHandForPremiums(const Hand& hand)
{
    //Note if the hand has Tierce, Quarte, Quint, SquareX a player can
    //announce only one
    std::vector<std::pair<Premium, int8_t>> result;
    if (HasSquare(hand, all_jacks))
    {
        result.emplace_back(std::make_pair(Premium::Square200, -1));
        /*DEBUG::LOG("200");*/
    }
    if (HasSquare(hand, all_nines))
    {
        result.emplace_back(std::make_pair(Premium::Square150, -1));
        /*DEBUG::LOG("150");*/
    }
    if (HasSquare(hand, all_aces) || HasSquare(hand, all_kings)
            || HasSquare(hand, all_queens) || HasSquare(hand, all_tens))
    {
        result.emplace_back(std::make_pair(Premium::Square100, -1));
        /*DEBUG::LOG("100");*/
    }

    for (const auto& suit_cards: hand)
    {
        auto [length, highest_card] = HasSequence(suit_cards);
        if (length >= 3)
        {
            switch (length)
            {
                case 3:
                    result.emplace_back(std::make_pair(Premium::Tierce, highest_card));
                    /*DEBUG::LOG("Tierce");*/
                    break;
                case 4:
                    result.emplace_back(std::make_pair(Premium::Quarte, highest_card));
                    /*DEBUG::LOG("Quarte");*/
                    break;
                default:
                    result.emplace_back(std::make_pair(Premium::Quint, highest_card));
                    /*DEBUG::LOG("Quint");*/
                    break;
            }
            /*DEBUG::LOG("Sequence of length + " + std::to_string(length)*/
                    /*+ " highest card: " + std::to_string(highest_card));*/
        }
    }

    return {};
}
