#include <srl.hpp>
#include "palette.h"
#include "palette.pal"

SRL::CRAM::Palette gamePalette;
uint16_t* basePalette = 0;

// Palette for logo
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

    if (cramPalette.Load((SRL::Types::HighColor*)palData, 256) >= 0)
    {
        // Mark bank as in use
        SRL::CRAM::SetBankUsedState(id, mode, true);
    }
    return cramPalette;
}

void LoadBackgroundPalette(uint16_t* palData)
{
    SRL::CRAM::TextureColorMode mode = SRL::CRAM::TextureColorMode::Paletted256;

    int32_t id = 1;
    SRL::CRAM::Palette backgroundPalette(mode, id);
    backgroundPalette.Load((SRL::Types::HighColor*)palData, 256);
}