#pragma once
#include <srl.hpp>
#include "../core/assets.h"
#include "../vdp2/sprite_colors.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;

#define CHARACTER_SELECT_TIMER 99
#define CHARACTER_X_RADIUS Fxp(140)
#define CHARACTER_Y_RADIUS Fxp(-60)
#define END_RADIUS Fxp(-1400)

#define TO_TURNS (1.0f/360.0f)

#define CHARACTER_GAP_ANGLE 30
#define MOVEMENT_SPEED 1

#define CONFIRM_PRESSES    (2)

typedef struct _STORY_CHARACTER_SELECT
{
    unsigned int timer;
    unsigned int selection;
    bool rotateLeft;
    bool rotateRight;
    
    Fxp xRadius;
    Fxp yRadius;
    Fxp yPos;
    int angle;
    int gapAngle;
    int spr_id;
    bool pressedLeft;
    bool pressedRight;
    bool isAngleSnapped;
    bool snapEnd;
    bool start;
    bool finished;
    bool end;
} STORY_CHARACTER_SELECT;

extern STORY_CHARACTER_SELECT characterSelect;
extern bool rotateLeft;
extern bool rotateRight;


#ifdef __cplusplus
extern "C" {
#endif

void characterSelectInit(void);
void characterSelectInput(void);
void characterSelectUpdate(void);
void characterMeterDraw(void);
void characterSelectDraw(void);
void characterSelectPositionUpdate(int angle, int sprAngle);

int snap_to_nearest_angle(int angle);

void snap_to_random_character(int targetAngle);

#ifdef __cplusplus
}
#endif