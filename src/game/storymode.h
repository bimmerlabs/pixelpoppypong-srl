#pragma once

#include <srl.hpp>
#include "../core/assets.h"
#include "../core/sprites.h"
#include "gameplay.h"
#include "team_select.h"

#define CHARACTER_POS_X  0
#define CHARACTER_POS_Y  -128
#define CHARACTER_POS_OFFSET 128
#define CHARACTER_SELECT_TIMER (6 * 60)

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

static inline void drawCharacterList(void) 
{
    PPLAYER player = &g_Players[0];
    
    my_sprite_draw(&menu_bg2);
    my_sprite_draw(player->_cursor[0]);
    my_sprite_draw(player->_cursor[1]);
    character_pos_y = character_pos_selected;
    
    for(uint8_t i = 0; i <= MAX_ROUNDS; i++)
    {
        if (i == player->character.choice)
        {
            i++;
        }
        character_portrait.id = character_portrait.anim[0].asset + i;
        set_spr_position(&character_portrait, character_pos_x, character_pos_y, 90);
        set_spr_scale(&character_portrait, 2.0, 2.0);
        my_sprite_draw(&character_portrait);
        character_pos_y -= CHARACTER_POS_OFFSET;
    }
}
