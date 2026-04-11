#pragma once
#include <srl.hpp>
#include "../core/audio.h"
#include "../objects/player.h"
#include "../objects/goal.h"
#include "../objects/teams.h"
#include "../core/vdp1print.h"

// #define SCORE_DISPLAY_TIME (15 * 60)
#define SCORE_EXIT_TIME (15 * 60)

#define INITIALS_LENGTH 3  // Three-letter initials like "ABC"
#define SCORE_ENTRIES 10
#define UNLOCK_CRAIG_SCORE 2500000
#define UNLOCK_GARFIELD_SCORE 5000000

using namespace SRL::Types;
using namespace SRL::Math::Types;

typedef struct {
    uint32_t score;
    char initials[INITIALS_LENGTH + 1];  // +1 for null terminator (do I really need this??)
    uint8_t character;
    int8_t difficulty;
} HighScoreEntry;

extern HighScoreEntry highScores[SCORE_ENTRIES];

extern PLAYER g_Players[MAX_PLAYERS];

#ifdef __cplusplus
extern "C" {
#endif

static inline void highScoreTitleDraw(void)
{
    font.zmode = _ZmLC;
    set_spr_scale(&font, 1, 1);
    int32_t xpos = -136;
    int32_t ypos = -172;
    int32_t zpos = 50;
    const int32_t offset = 24;
    const int32_t space = 28;
    
    DrawSpriteText(&font, "High Scores:", xpos, ypos, zpos, offset, space);
}

static inline void exitHighScoresHelper(void)
{
    g_Game.lastState = GAME_STATE_HIGHSCORES;
    SRL::Debug::PrintClearScreen();
    SRL::VDP2::NBG2::ScrollDisable();
    SRL::VDP2::NBG0::SetPriority(SRL::VDP2::Priority::Layer7);
}

void highScore_init(void);
void init_scores(void);
void display_scores(void);
void score_input(void);

void sortHighScores(HighScoreEntry scores[]);
void addHighScore(uint32_t newScore, const char *initials, uint8_t character);
void update_bg_position(void);

void calculateScore(Sprite *ball, uint8_t playerID);

void updateScore(Sprite *ball, int playerID);

#ifdef __cplusplus
}
#endif