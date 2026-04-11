// nbg1.h
#pragma once

#include <srl.hpp>

#include "palettetools.h"

#define T_DAWN 5
#define T_DAY 11
#define T_DUSK 17
#define T_NIGHT 23

// time of day
typedef enum _BG_TIME
{
    BG_DUSK = 0,
    BG_NIGHT,
    BG_DAWN,
    BG_DAY,
} BG_TIME;

extern ImageAttr attrNbg1;

void init_nbg1_img(void);
void update_nbg1_time_slot(void);