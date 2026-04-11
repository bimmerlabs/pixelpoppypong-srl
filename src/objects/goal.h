#pragma once
#include <srl.hpp>
#include "player.h"
#include "../core/assets.h"

#define GOAL_X_POS Fxp(330)
#define GOAL_WIDTH Fxp(40)
#define GOAL_X_BOUNDS     GOAL_X_POS - GOAL_WIDTH
#define GOAL_LEFT_BOUNDS -(GOAL_X_POS - GOAL_WIDTH)
#define GOAL_RIGHT_BOUNDS GOAL_X_POS - GOAL_WIDTH
#define GOAL_CENTER_POS Fxp(0)
#define GOAL_MARGIN Fxp(20)

using namespace SRL::Types;
using namespace SRL::Math::Types;

extern bool g_AnimateGoal;
extern bool g_ExplodeGoal;

typedef enum _GOAL_SCALE
{
    GOAL_SCALE_EASY = 20,
    GOAL_SCALE_MEDIUM = 20, //16
    GOAL_SCALE_HARD = 20, //13
    GOAL_SCALE_VS_MODE = 10,
} GOAL_SCALE;

// typedef enum _GOAL_Y_POS
// {
#define GOAL_Y_POS_EASY Fxp(140)
#define GOAL_Y_POS_MEDIUM Fxp(140) // 120
#define GOAL_Y_POS_HARD = Fxp(140) // 100
#define GOAL_Y_POS_MID = Fxp(0)
#define GOAL_Y_POS_TOP_VS_MODE Fxp(160)
#define GOAL_Y_POS_MID_VS_MODE Fxp(79)
#define GOAL_Y_POS_BOT_VS_MODE Fxp(2)
// } GOAL_Y_POS;

typedef struct _GOAL_POSITION
{
    Fxp x;
    Fxp top;
    Fxp bot;
    Fxp mid;
    int top_flip;
    int bot_flip;
    int top_zmode;
    int mid_zmode;
    int bot_zmode;

} GOAL_POSITION, *PGOAL_POSITION;

typedef struct _GOAL_OBJECT
{
    bool isColliding;
    bool onLeftSide; // is this needed? (use player as proxy)
    int scale;
    GOAL_POSITION pos;
    uint8_t id;
    Sprite *sprite;
    PPLAYER player;
    bool drawSingleGoal;
} GOAL, *PGOAL;

extern GOAL g_Goal[MAX_PLAYERS];

#ifdef __cplusplus
extern "C" {
#endif

void initGoalColors(void);
void animateGoalColor(bool *_do_update);

void initGoals(void);
void setGoalSize(void);
void drawGoals(void);
void explodeGoals(void);

void checkRightGoalCollision(Sprite *ball);
void checkLeftGoalCollision(Sprite *ball);

#ifdef __cplusplus
}
#endif