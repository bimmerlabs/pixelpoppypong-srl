#pragma once
#include <srl.hpp>
#include "../objects/player.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;

#define TEAM_SELECT_TIMER (1 * 60)

// UI locations
#define PORTRAIT_X Fxp(-120)
#define PORTRAIT_Y Fxp(-166)
#define PORTRAIT_DEPTH Fxp(90) // why is this Fxp?

#define PAW_X Fxp(247)

#define CHARACTER_TEXT_Y 2
#define TEAM_TEXT_X1 33
#define TEAM_TEXT_X2 35
#define TEAM_TEXT_Y 4
// #define METER_TEXT_X 18
// #define METER_TEXT_Y2 2
// #define METER_TEXT_Y3 4

// #define METER_X  Fxp(-40)
// #define METER_Y1 Fxp(34)
// #define METER_Y2 Fxp(3)
// #define METER_Y3 Fxp(29)
// #define METER_HEIGHT Fxp(0.9)
// #define METER_WIDTH Fxp(25)

#define PLAYER_OFFSET_Y Fxp(112)
#define PLAYER_TEXT_OFFSET_Y 7
#define PLAYER_BG_DEPTH Fxp(95)
#define PLAYER_BG_X1 Fxp(88)
#define PLAYER_BG_X2 Fxp(208)
#define PLAYER_BG_Y Fxp(50)

#define MENU_BG2_X Fxp(-120)
#define MENU_BG2_WIDTH Fxp(56)
#define MENU_BG2_HEIGHT Fxp(240)
#define MENU_BG2_DEPTH Fxp(95)
#define MENU_BG1_DEPTH Fxp(92)

#define CURSOR_DEPTH Fxp(80)

extern int g_StartGameFrames; // for debugging
extern bool g_TeamSelectPressedStart; // for debugging
extern bool all_players_ready; // for debugging

#ifdef __cplusplus
extern "C" {
#endif

void resetTeams(void);
void drawCharacterSelectGrid(void);  // re-organize these to be in order
void characterSelect_input(void);
void teamSelect_init(void);
void teamSelect_input(void);
bool playerReadyState(void);
void resetReadyState(void);
bool validateTeamCount(void);
void teamSelect_update(void);
void teamSelect_draw(void);

#ifdef __cplusplus
}
#endif