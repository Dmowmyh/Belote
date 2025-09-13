#pragma once

#include "Deck.h"
#include <vector>

//The card order for sequences is: 7; 8; 9; 10; J; Q; K; A.

enum Premium
{
    Sequence,
    Square
};

enum Sequence
{
    Tierce,
    Quarte,
    Quint,
};

enum Square
{
    Square100,
    Square150,
    Square200
};

inline bool HasSquare(const Hand& hand, const std::array<int, 4>& ids)
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

inline int HasSequence(const std::vector<Card>& suit_cards)
{
    if (suit_cards.size() < 3)
    {
        return 0;
    }

    int sequence_length = 1;
    //for (size_t i = 0; i < suit_cards.size()-1; ++i)
    //{
        //for (size_t j = 1; j < suit_cards.size(); j++)
        //{
            //if (suit_cards[j-1].id_ != suit_cards[j].id_ + 1)
            //{
                //break;
            //}
            //sequence_length++;
        //}
    //}
    return sequence_length; // Found a consecutive sequence
}

inline std::vector<Premium> AnalyseHandForPremiums(const Hand& hand)
{
    //TODO(Mario): Note if the hand has Tierce, Quarte, Quint, SquareX a player can
    //announce only one
    //std::vector<Premium> result;
    //if (HasSquare(hand, {28, 20, 12, 4}))
    //{
        //result.emplace_back(Premium::Square);
        //std::cout << "200" << std::endl;
    //}
    //if (HasSquare(hand, {26, 18, 10, 2}))
    //{
        //result.emplace_back(Premium::Square);
        //std::cout << "150" << std::endl;
    //}
    //if (HasSquare(hand, {31, 23, 15, 7}))
    //{
        //result.emplace_back(Premium::Square);
        //std::cout << "100" << std::endl;
    //}
    //for (const auto& suit_cards: hand)
    //{
        //auto tierce = HasSequence(suit_cards);
        //if (tierce >= 3)
        //{
            //std::cout << "Tierce from: " << tierce << std::endl;
        //}
    //}

    return {};
}
