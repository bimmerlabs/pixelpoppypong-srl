#pragma once
#include <srl.hpp>
#include "../core/sprites.h"
#include "../objects/player.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;

#define FIELD_THRESHOLD Fxp(5) // how far the ball is on the other side (makes AI move ealier / easier)
#define LARGE_GOAL_THRESHOLD_MAX Fxp(20)
#define LARGE_GOAL_THRESHOLD_MIN Fxp(10)
#define SMALL_GOAL_THRESHOLD_MAX Fxp(10)
#define SMALL_GOAL_THRESHOLD_MIN Fxp(5)
#define MEDIUM_MOVEMENT_FACTOR Fxp(0.001)
#define SLOW_MOVEMENT_FACTOR Fxp(0.0005)

#define AI_GOAL_CENTER Fxp(80.0)

#define HARD_AI_MOVEMENT_SPEED   Fxp(0.0030)
#define MEDIUM_AI_MOVEMENT_SPEED Fxp(0.0015)
#define EASY_AI_MOVEMENT_SPEED   Fxp(0.0010)

#ifdef __cplusplus
extern "C" {
#endif

void playerAI(Sprite *ball);
void centerAiPlayer(PPLAYER player);
void boundAiPlayer(PPLAYER player);

#ifdef __cplusplus
}
#endif