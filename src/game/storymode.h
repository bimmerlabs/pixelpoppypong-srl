#pragma once

#include <srl.hpp>
#include "../core/assets.h"
#include "../core/sprites.h"
#include "gameplay.h"
#include "team_select.h"

#define CHARACTER_POS_X  -104
#define CHARACTER_POS_Y  -128
#define CHARACTER_POS_OFFSET 128
#define STORY_MODE_TIMER (6 * 60)

using namespace SRL::Types;
using namespace SRL::Math::Types;

extern int character_pos_x;
extern int character_pos_y;
extern int character_pos_selected;
extern int character_offset;
extern int g_StartStoryFrames;
void initStoryMode(void);
void initContinue(void);
void initNextRound(void);
void storySelectUpdate(void);
void tallyScore(void);

void drawCharacterList(void);

// helper function - returns true if all available opponents have been beaten
bool allOpponentsBeaten(void);