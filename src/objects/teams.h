#pragma once
#include "object.h"

#define MAX_TEAMS 4

typedef enum _TEAM_SELECT
{
    TEAM_1 = 1,
    TEAM_2 = 2,
    TEAM_3 = 3,
    TEAM_4 = 4,
    TEAM_COUNT = 5,
} TEAM_SELECT;

typedef enum _TEAMS_FOR_SCORING
{
    ONE_TEAM = 1,
    TWO_TEAMS = 2,
    THREE_TEAMS = 3,
    FOUR_TEAMS = 4,
} TEAMS_FOR_SCORING;

typedef struct _TEAM_OBJECT
{
    // number of teams
    short minTeams;
    short maxTeams;
    short numTeams;
    bool isAvailable[TEAM_COUNT];
    bool isActive[TEAM_COUNT];
} TEAM_OBJECT, *PTEAM_OBJECT;

extern TEAM_OBJECT g_Team;

void initTeams(void);
void resetTeamState(void);