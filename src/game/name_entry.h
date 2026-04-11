#pragma once
#include <srl.hpp>
#include "../core/assets.h"
#include "../core/vdp1print.h"
#include "../vdp2/sprite_colors.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;

#define NAME_ENTRY_TIMER 99
#define NAME_X_RADIUS Fxp(140)
#define NAME_Y_RADIUS Fxp(50)
#define NAME_Y_POS 170
#define END_RADIUS Fxp(-1400)

#define TO_TURNS (1.0f/360.0f)

#define GAP_ANGLE 12

#define FIRST_INITIAL  (0)
#define SECOND_INITIAL (1)
#define THIRD_INITIAL  (2)
#define MAX_INITIAL    (3)

typedef struct _NAME_ENTRY
{
    unsigned int timer;
    unsigned int selection;
    bool rotateLeft;
    bool rotateRight;
    char initials[4];  // 3 letters + null terminator (do I need the null?
    int char_id[3];
    
    Fxp xRadius;
    Fxp yRadius;
    Fxp yPos;
    int angle;
    int gapAngle;
    bool pressedLeft;
    bool pressedRight;
    bool isAngleSnapped;
    bool finished;
    bool end;
} NAME_ENTRY;

extern NAME_ENTRY nameEntry;
extern bool rotateLeft;
extern bool rotateRight;


#ifdef __cplusplus
extern "C" {
#endif

static inline void nameEntryTitleDraw(void)
{
    font.zmode = _ZmLC;
    set_spr_scale(&font, 1, 1);
    int32_t xpos = -232;
    int32_t ypos = -200;
    int32_t zpos = 50;
    const int32_t offset = 24;
    const int32_t space = 28;
    
    DrawSpriteText(&font, "Enter Your Initials", xpos, ypos, zpos, offset, space);
}

void nameEntryInit(void);
void nameEntryInput(void);
void nameEntryUpdate(void);
void nameEntryDraw(void);
void nameEntryPositionUpdate(int angle, int sprAngle);

int snap_to_nearest_12(int angle);

int snap_to_end(int angle);

#ifdef __cplusplus
}
#endif