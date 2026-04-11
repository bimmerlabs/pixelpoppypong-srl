#pragma once
#include <srl.hpp>
#include "../core/sprites.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;

#ifdef __cplusplus
extern "C" {
#endif

static inline int16_t GetFontIndex(char c)
{
    if ((uint8_t)(c - '0') <= 9)  return c - '0';
    if ((uint8_t)(c - 'A') <= 25) return 10 + (c - 'A');
    if ((uint8_t)(c - 'a') <= 25) return 10 + (c - 'a');
    if (c == '!') return 36;
    return -1;
}

// todo: check spaces in functions that use this (gap seems too large)
static inline void DrawSpriteText(
    Sprite *font,
    const char* text, int32_t x, int32_t y, int32_t z,
    int32_t letterSpacing, int32_t wordSpacing)
{
    int32_t xpos = x;

    for (int i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];

        if (c == ' ')
        {
            xpos += wordSpacing;
            continue;
        }

        int16_t index = GetFontIndex(c);
        if (index < 0) continue;

        set_spr_position(font, xpos, y, z);
        font->id = font->anim[0].asset + index;
        my_sprite_draw(font);

        xpos += letterSpacing;
    }
}

#ifdef __cplusplus
}
#endif