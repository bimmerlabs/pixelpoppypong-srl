#pragma once
#include <srl.hpp>
// #include "physics.h"
// #include "gameplay.h"
#include "../core/audio.h"
#include "../objects/player.h"
#include "../objects/goal.h"
#include "../objects/teams.h"

#define SCORE_DISPLAY_TIME (15 * 60)

#define INITIALS_LENGTH 3  // Three-letter initials like "ABC"
#define SCORE_ENTRIES 10
#define UNLOCK_CRAIG_SCORE 2500000
#define UNLOCK_GARFIELD_SCORE 5000000

using namespace SRL::Types;
using namespace SRL::Math::Types;

typedef struct {
    uint32_t score;
    char initials[INITIALS_LENGTH + 1];  // +1 for null terminator
} HighScoreEntry;

extern HighScoreEntry highScores[SCORE_ENTRIES];

void highScore_init(void);
void init_scores(void);
void display_scores(void);
void score_input(void);

void sortHighScores(HighScoreEntry scores[]);
void addHighScore(uint32_t newScore, const char *initials);
void update_bg_position(void);

extern PLAYER g_Players[MAX_PLAYERS];

void calculateScore(Sprite *ball, uint8_t playerID);

void updateScore(Sprite *ball, int playerID);