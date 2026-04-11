#pragma once
#include "../objects/player.h"
#include "../game/highscores.h"

typedef struct _SAVEGAME 
{
    GameOptions g_GameOptions;
    bool characterUnlocked[CHARACTER_MAX];
    HighScoreEntry highScores[SCORE_ENTRIES];
    INPUT inputSettings[MAX_INPUTS];
} SaveGame;

extern SaveGame save_game;

#ifdef __cplusplus
extern "C" {
#endif

void    save_game_backup(void);

bool    load_game_backup(void);

bool   is_cart_mem_available(void); // here for debug

bool   is_internal_mem_available(void); // here for debug

#ifdef __cplusplus
}
#endif