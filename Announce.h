#pragma once

#include <string_view>
#include <unordered_map>
#include <vector>

enum class Announce
{
    Club,
    Diamond,
    Spade,
    Heart,
    NoTrumps,
    AllTrumps,
    DoubleClub,
    DoubleDiamond,
    DoubleSpade,
    DoubleHeart,
    DoubleNoTrump,
    DoubleAllTrump,
    ReDoubleClub,
    ReDoubleDiamond,
    ReDoubleSpade,
    ReDoubleHeart,
    ReDoubleNoTrump,
    ReDoubleAllTrump,
    Pass,
    Count,
    None,
};

using A = Announce;
inline std::string_view AnnounceToString(Announce announce)
{
    switch (announce)
    {
    case A::Club:
        return "Club";
    case A::Diamond:
        return "Diamond";
    case A::Spade:
        return "Spade";
    case A::Heart:
        return "Heart";
    case A::NoTrumps:
        return "NoTrump";
    case A::AllTrumps:
        return "AllTrumps";
    case A::DoubleClub:
        return "DoubleClub";
    case A::DoubleDiamond:
        return "DoubleDiamond";
    case A::DoubleSpade:
        return "DoubleSpade";
    case A::DoubleHeart:
        return "DoubleHeart";
    case A::DoubleNoTrump:
        return "DoubleNoTrump";
    case A::DoubleAllTrump:
        return "DoubleAllTrump";
    case A::ReDoubleClub:
        return "ReDoubleClub";
    case A::ReDoubleDiamond:
        return "ReDoubleDiamond";
    case A::ReDoubleSpade:
        return "ReDoubleSpade";
    case A::ReDoubleHeart:
        return "ReDoubleHeart";
    case A::ReDoubleNoTrump:
        return "ReDoubleNoTrump";
    case A::ReDoubleAllTrump:
        return "ReDoubleAllTrump";
    case A::Pass:
        return "Pass";
    default:
        return "";
    }
}

// clang-format off
inline std::unordered_map<Announce, std::vector<Announce>> possible_announces_teammate = {
    {A::Pass, {A::Club, A::Diamond, A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::Club, {A::Diamond, A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::Diamond, {A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::Spade, {A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::Heart, {A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::NoTrumps, {A::AllTrumps, A::Pass}},
    {A::AllTrumps, {A::Pass}},
    {A::DoubleClub, {A::Diamond, A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::DoubleDiamond, {A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::DoubleSpade, {A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::DoubleHeart, {A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::DoubleNoTrump, {A::AllTrumps, A::Pass}},
    {A::DoubleAllTrump, {A::Pass}},
    {A::ReDoubleClub, {A::Diamond, A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::ReDoubleDiamond, {A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::ReDoubleSpade, {A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::ReDoubleHeart, {A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::ReDoubleNoTrump, {A::AllTrumps, A::Pass}},
    {A::ReDoubleAllTrump, {A::Pass}},
};

inline std::unordered_map<Announce, std::vector<Announce>> possible_announces_nonteammate = {
    {A::Pass, {A::Club, A::Diamond, A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::Club, {A::Diamond, A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass, A::DoubleClub}},
    {A::Diamond, {A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass, A::DoubleDiamond}},
    {A::Spade, {A::Heart, A::NoTrumps, A::AllTrumps, A::Pass, A::DoubleSpade}},
    {A::Heart, {A::NoTrumps, A::AllTrumps, A::Pass, A::DoubleHeart}},
    {A::NoTrumps, {A::AllTrumps, A::Pass, A::DoubleNoTrump}},
    {A::AllTrumps, {A::Pass, A::DoubleAllTrump}},
    {A::DoubleClub, {A::ReDoubleClub, A::Diamond, A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::DoubleDiamond, {A::ReDoubleDiamond, A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::DoubleSpade, {A::ReDoubleSpade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::DoubleHeart, {A::ReDoubleHeart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::DoubleNoTrump, {A::ReDoubleNoTrump, A::AllTrumps, A::Pass}},
    {A::DoubleAllTrump, {A::ReDoubleAllTrump, A::Pass}},
    {A::DoubleClub, {A::ReDoubleClub, A::Diamond, A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::ReDoubleClub, {A::Diamond, A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::ReDoubleDiamond, {A::Spade, A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::ReDoubleSpade, {A::Heart, A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::ReDoubleHeart, {A::NoTrumps, A::AllTrumps, A::Pass}},
    {A::ReDoubleNoTrump, {A::AllTrumps, A::Pass}},
    {A::ReDoubleAllTrump, {A::Pass}},
};
// clang-format on
