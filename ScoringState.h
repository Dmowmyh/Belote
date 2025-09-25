#pragma once

#include "Debug.h"
#include "RoundData.h"
#include "Announce.h"
#include "Defs.h"

namespace GamePlay
{
inline RoundResults Scoring(Announce announce, int team_1_points,
    int team_2_points, int valat_team, int team_that_made_the_announcement)
{
    //DEBUG::LOG("Team 1 points before : " + std::to_string(team_1_points));
    //DEBUG::LOG("Team 2 points before : " + std::to_string(team_2_points));
    //DEBUG::LOG("Team that made the announcement : " + std::to_string(team_that_made_the_announcement));
    //DEBUG::LOG("Valat team: " + std::to_string(valat_team));
    team_1_points /= 10;
    team_2_points /= 10;

    if (A::NoTrumps == announce)
    {
        team_1_points *= 2;
        team_2_points *= 2;
    }

    int total_points = team_1_points + team_2_points;
    if (team_that_made_the_announcement == TEAM_1_ID && team_2_points > team_1_points)
    {
        return RoundResults{0, total_points};
        //INSIDE TEAM_1
    }
    else if (team_that_made_the_announcement == TEAM_2_ID && team_2_points > team_1_points)
    {
        return RoundResults{total_points, 0};
        //INSIDE TEAM_2
    }
    return {team_1_points, team_2_points};
}
}
