#pragma once

#include "Deck.h"

#include <iostream>
#include <vector>

namespace DEBUG
{
inline void LOG(const std::string& log)
{
    std::cout << log << std::endl;
}

inline void LOG(const Card& card)
{
    std::cout << RankToString(card.rank_) << " " << SuitToString(card.suit_) << ", ";
}

inline void LOG(const std::vector<Card>& hand)
{
    std::cout << "---HAND---\n";
    for (const auto& card : hand)
    {
        LOG(card);
    }
    std::cout << "\n";
    std::cout << "----------\n";
}
}
