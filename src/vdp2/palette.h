#pragma once

#include "../main.h"

#define PaletteID (0)

extern SRL::CRAM::Palette gamePalette;
extern uint16_t* basePalette;

#ifdef __cplusplus
extern "C" {
#endif

uint16_t* init_game_palette();

SRL::CRAM::Palette LoadSpritePalette(uint16_t* palData);
void LoadBackgroundPalette(uint16_t* palData);

#ifdef __cplusplus
}
#endif