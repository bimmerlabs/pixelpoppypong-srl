#include <srl.hpp>
#include "palette.h"
#include "palette.pal"

// for HSL colors / normap mapping
uint16_t* basePalette = 0;

// for sprites
SRL::CRAM::Palette gamePalette;

uint16_t* init_game_palette(void)
{
    gamePalette  = LoadSpritePalette(game_pal);
    return game_pal;
}

SRL::CRAM::Palette LoadSpritePalette(uint16_t* palData)
{
    SRL::CRAM::TextureColorMode mode = SRL::CRAM::TextureColorMode::Paletted256;

    int32_t id = 0;

    SRL::CRAM::Palette cramPalette(mode, id);

    cramPalette.Load((SRL::Types::HighColor*)palData, 256);
    
    return cramPalette;
}

void LoadBackgroundPalette(uint16_t* palData)
{
    SRL::CRAM::TextureColorMode mode = SRL::CRAM::TextureColorMode::Paletted256;

    int32_t id = 1;
    SRL::CRAM::Palette backgroundPalette(mode, id);
    backgroundPalette.Load((SRL::Types::HighColor*)palData, 256);
}