#pragma once

#include <array>
#include <cstdint>
#include <unordered_map>

enum class Suit {Club, Diamond, Spade, Heart, Count, None};
enum class Rank {Seven, Eight, Nine, Ten, Jack, Queen, King, Ace, Count};

inline std::string_view SuitToString(Suit suit)
{
    switch (suit)
    {
        case Suit::Club: return "Club";
        case Suit::Diamond: return "Diamond";
        case Suit::Heart: return "Heart";
        case Suit::Spade: return "Spade";
        default: static_assert(true, "Invalid SuitToString call");
    }
    return "";
}

inline std::string_view RankToString(Rank rank)
{
    switch (rank)
    {
        case Rank::Seven: return "Seven";
        case Rank::Eight: return "Eight";
        case Rank::Nine: return "Nine";
        case Rank::Ten: return "Ten";
        case Rank::Jack: return "Jack";
        case Rank::Queen: return "Queen";
        case Rank::King: return "King";
        case Rank::Ace: return "Ace";
        default: static_assert(true, "Invalid RankToString call");
    }
    return "";
}

struct Card
{
    Rank rank_;
    Suit suit_;
    int8_t id_;
};

inline constexpr int DECK_SIZE = 32;

enum class CardOrder
{
    ClubSeven = 0, ClubEight = 1, ClubNine = 2, ClubTen = 3, ClubJack = 4, ClubQueen = 5, ClubKing = 6, ClubAce = 7,
    DiamondSeven = 8, DiamondEight = 9, DiamondNine = 10, DiamondTen = 11, DiamondJack = 12, DiamondQueen = 13, DiamondKing = 14, DiamondAce = 15,
    SpadeSeven = 16, SpadeEight = 17, SpadeNine = 18, SpadeTen = 19, SpadeJack = 20, SpadeQueen = 21, SpadeKing = 22, SpadeAce = 23,
    HeartSeven = 24, HeartEight = 25, HeartNine = 26, HeartTen = 27, HeartJack = 28, HeartQueen = 29, HeartKing = 30, HeartAce = 31,
};

using DeckIterator = std::array<Card, DECK_SIZE>::iterator;
inline std::array<Card, DECK_SIZE> deck = {
    Card{Rank::Ace, Suit::Club, 7}, Card{Rank::King, Suit::Club, 6}, Card{Rank::Queen, Suit::Club, 5}, Card{Rank::Jack, Suit::Club, 4},
    Card{Rank::Ten, Suit::Club, 3}, Card{Rank::Nine, Suit::Club, 2}, Card{Rank::Eight, Suit::Club, 1}, Card{Rank::Seven, Suit::Club, 0},

    Card{Rank::Ace, Suit::Diamond, 15}, Card{Rank::King, Suit::Diamond, 14}, Card{Rank::Queen, Suit::Diamond, 13}, Card{Rank::Jack, Suit::Diamond, 12},
    Card{Rank::Ten, Suit::Diamond, 11}, Card{Rank::Nine, Suit::Diamond, 10}, Card{Rank::Eight, Suit::Diamond, 9}, Card{Rank::Seven, Suit::Diamond, 8},

    Card{Rank::Ace, Suit::Spade, 23}, Card{Rank::King, Suit::Spade, 22}, Card{Rank::Queen, Suit::Spade, 21}, Card{Rank::Jack, Suit::Spade, 20},
    Card{Rank::Ten, Suit::Spade, 19}, Card{Rank::Nine, Suit::Spade, 18}, Card{Rank::Eight, Suit::Spade, 17}, Card{Rank::Seven, Suit::Spade, 16},

    Card{Rank::Ace, Suit::Heart, 31}, Card{Rank::King, Suit::Heart, 30}, Card{Rank::Queen, Suit::Heart, 29}, Card{Rank::Jack, Suit::Heart, 28},
    Card{Rank::Ten, Suit::Heart, 27}, Card{Rank::Nine, Suit::Heart, 26}, Card{Rank::Eight, Suit::Heart, 25}, Card{Rank::Seven, Suit::Heart, 24}
};

inline std::unordered_map<Rank, int8_t> trump_card_strength =
{
    {{Rank::Jack, 7}, {Rank::Nine, 6}, {Rank::Ace, 5}, {Rank::Ten, 4}, {Rank::King, 3}, {Rank::Queen, 2}, {Rank::Eight, 1}, {Rank::Seven, 0}}
};

inline std::unordered_map<Rank, int8_t> non_trump_card_strength =
{
    {{Rank::Ace, 7}, {Rank::Ten, 6}, {Rank::King, 5}, {Rank::Queen, 4}, {Rank::Jack, 3}, {Rank::Nine, 2}, {Rank::Eight, 1}, {Rank::Seven, 0}}
};
