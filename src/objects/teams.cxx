#include "player.h"
#include "teams.h"
#include "../main.h"

TEAM_OBJECT g_Team = {};

void initTeams(void) {
    for(unsigned int i = TEAM_1; i < TEAM_COUNT; i++)
    {
        g_Team.isAvailable[i] = true;
        g_Team.isActive[i] = false;
        // if (g_GameOptions.debug_display)
            // SRL::Debug::Print(22, 15+i, "g_Team.isActive[%i]:%i", i, g_Team.isActive[i]);
    }
}

void resetTeamState(void) {
    for(unsigned int i = 0; i < MAX_PLAYERS; i++)
    {
        PPLAYER player = &g_Players[i];
        if (player->isPlaying) {
            g_Team.isActive[player->teamChoice] = true;
            player->isDead = false;
        }
    }
}
