#include "Player.h"
#include <algorithm>

Player::Player(PlayerID player_id, PlayerID teammate_id)
    : player_id_{player_id}, teammate_id_{teammate_id}
{
    for (auto& suit: hand_)
    {
        suit.reserve(8);
    }
}

void Player::OnDeal(const Card& card)
{
    switch (card.id_/(DECK_SIZE/SUITS))
    {
        case static_cast<int>(Suit::Club):
            hand_.at(static_cast<int>(Suit::Club)).emplace_back(card);
            break;
        case static_cast<int>(Suit::Diamond):
            hand_.at(static_cast<int>(Suit::Diamond)).emplace_back(card);
            break;
        case static_cast<int>(Suit::Spade):
            hand_.at(static_cast<int>(Suit::Spade)).emplace_back(card);
            break;
        case static_cast<int>(Suit::Heart):
            hand_.at(static_cast<int>(Suit::Heart)).emplace_back(card);
            break;
        default:
            break;
    }
}

void Player::Sort()
{
    for (auto& suit_cards: GetHand())
    {
        std::sort(std::begin(suit_cards), std::end(suit_cards),
          [](const Card& lhs, const Card& rhs) -> bool { return lhs.id_ < rhs.id_; });
    }
}

Hand& Player::GetHand()
{
    return hand_;
}

PlayerID Player::GetTeammateID()
{
    return teammate_id_;
}

PlayerID Player::GetID()
{
    return player_id_;
}

void Player::ClearHand()
{
    for (auto& suit: hand_)
    {
        suit.clear();
    }
}
