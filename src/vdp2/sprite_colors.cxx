#include "sprite_colors.h"
#include "palettetools.h"
#include "lighting.h"
#include "font.h"
#include "../main.h"

bool do_update_All = false;
bool do_update_font2All = false;
bool do_update_ppplogo = false;
bool do_update_logo1 = false;
// bool do_update_timer = false;
bool do_update_Goals[MAX_PLAYERS];
bool do_update_Pmenu[MAX_PLAYERS];
bool do_update_PmenuAll = false;
// bool do_update_menu1 = false;
// bool do_update_menu2 = false;
bool do_update_menu3 = false;
bool do_update_menu4 = false;
bool do_update_fish = false;
bool do_update_bomb = false;
bool do_update_shroom = false;

bool update_palette_All = false;
bool update_palette_font2All = false;
bool update_palette_ppplogo = false;
bool update_palette_logo1 = false;
// bool update_palette_timer = false;
bool update_palette_Goals[MAX_PLAYERS];
bool update_palette_Pmenu[MAX_PLAYERS];
bool update_palette_PmenuAll = false;
// bool update_palette_menu1 = false;
// bool update_palette_menu2 = false;
bool update_palette_menu3 = false;
bool update_palette_menu4 = false;
bool update_palette_fish = false;
bool update_palette_bomb = false;
bool update_palette_shroom = false;

SRL::Types::HighColor colorBuffer[MAX_PALETTE_ENTRIES];

// palette for calculating color and lighting - hue, saturation, luminance (populated at runtime)
VectorHSL hslSprites[MAX_PALETTE_ENTRIES]; // this could probably be smaller

// palette ranges
PaletteRange p_rangeSpritesAll   = { 0, 233 };     // all colors (excluding normal map colors)

// FONT (start index chosen arbitrarily) - don't forget to reset palette after exiting screen!
PaletteRange p_rangeFont2All  = {64, 93}; // A - END
PaletteRange p_rangeFont2[FONT_CHARS] = {
    {64, 64}, {65, 65}, {66, 66}, {67, 67}, {68, 68}, {69, 69}, // A B C D E F
    {70, 70}, {71, 71}, {72, 72}, {73, 73}, {74, 74}, {75, 75}, // G H I J K L
    {76, 76}, {77, 77}, {78, 78}, {79, 79}, {80, 80}, {81, 81}, // M N O P Q R
    {82, 82}, {83, 83}, {84, 84}, {85, 85}, {86, 86}, {87, 87}, // S T U V W X
    {88, 88}, {89, 89}, {90, 90}, {91, 91}, {92, 92}, {93, 93}, // Y Z ! . < END
};

PaletteRange p_rangeLogo      = { 16, 23 };     // logo

PaletteRange p_rangeGoals[MAX_PLAYERS] = {      // Goal Colors
    {176, 177}, {178, 179}, {180, 181}, {182, 183}
};

PaletteRange p_rangePmenu[MAX_PLAYERS] = {      // pmenu (players)
    {10, 10}, {11, 11}, {12, 12}, {13, 13}
};

PaletteRange p_rangePmenuAll  = { 10, 12 };

// PaletteRange p_rangeMenu1     = { 26, 26 };     // tmenu (title)
// PaletteRange p_rangeMenu2     = { 27, 27 };
PaletteRange p_rangeMenu3     = { 28, 28 };     // tmenu (title)
PaletteRange p_rangeMenu4     = { 31, 31 };

// PaletteRange p_rangePpoppy1   = { 33, 36 };     // pixel poppy
// PaletteRange p_rangePpoppy2   = { 37, 39 };
// PaletteRange p_rangePpoppy3   = { 40, 43 };
PaletteRange p_rangeTimer     = { 56, 57 };
// PaletteRange p_rangeMacchi1   = { 65, 66 };     // macchi
// PaletteRange p_rangeMacchi2   = { 68, 71 };
// PaletteRange p_rangeJelly1    = { 81, 82 };     // jelly
// PaletteRange p_rangeJelly2    = { 84, 87 };
// PaletteRange p_rangePenny1    = { 97, 98 };     //penny
// PaletteRange p_rangePenny2    = { 100, 103 };
// PaletteRange p_rangePotter1   = { 113, 114 };   // potter
// PaletteRange p_rangePotter2   = { 116, 119 };
// PaletteRange p_rangeSparta1   = { 113, 114 };   // sparta
// PaletteRange p_rangeSparta2   = { 116, 119 };
// PaletteRange p_rangePoppy1    = { 145, 146 };   // poppy
// PaletteRange p_rangePoppy2    = { 148, 151 };
// PaletteRange p_rangeTj1       = { 161, 162 };   // tj
// PaletteRange p_rangeTj2       = { 164, 167 };
// PaletteRange p_rangeGeorge1   = { 177, 178 };   // george
// PaletteRange p_rangeGeorge2   = { 180, 183 };
// PaletteRange p_rangeWuppy1    = { 193, 194 };   // wuppy
// PaletteRange p_rangeWuppy2    = { 196, 199 };
// PaletteRange p_rangeStadler1  = { 209, 215 };   // stadler
// PaletteRange p_rangeGarfield1 = { 225, 231 };   // garfield
PaletteRange p_rangeBomb      = { 160, 163 };   // bomb
PaletteRange p_rangeFish      = { 154, 156 };   // fish
PaletteRange p_rangeShroom    = { 158, 159 };   // mushroom
PaletteRange p_rangeNormalMap = { 234, 250 };   // normal map

// tracks the accumulation of changes for the HSL color model
HSLTracker hsl_incSprites[HSL_MAX+1] = {};

// initial image setup: hue, saturation, luminance, x_pos, y_pos, x_scale, y_scale, x_scroll (rate), y_scroll (rate), min_sat_id, max_sat_id, min_lum_id, max_lum_id
ImageAttr attrSprites = { 100, 255, 255, Fxp(0.0), Fxp(0.0), Fxp(0.25), Fxp(0.0), 0, 0, 0, 0}; // we don't need all of these (eliminate everything outside of lighting scope)

void init_sprites_img(void) {
    for(unsigned int i = 0; i <= HSL_MAX; i++)
    {
        hsl_incSprites[i].h = 0;
        hsl_incSprites[i].s = 0;
        hsl_incSprites[i].l = 0;
    }
    
    MultiRgbToHsl(hslSprites, basePalette, &p_rangeSpritesAll);
    
    min_max_sl_id(hslSprites, &p_rangeSpritesAll, &attrSprites);
    
    for(unsigned int i = 0; i < (MAX_PLAYERS); i++)
    {
        do_update_Pmenu[i] = false;
        update_palette_Pmenu[i] = false;
    }
}

// directly set the HSL color
bool calculate_sprites_color(PaletteRange *range) {
    MultiHslTorRgb2Buffer(hslSprites, colorBuffer, range);
    return true;
}

// set the HSL color by hue, saturation, and luminance increments
bool update_sprites_color(PaletteRange *range, unsigned char hsl_id) {
    MultiPalette2Buffer(colorBuffer, hslSprites, &hsl_incSprites[hsl_id], range);
    return true;
}

// update CRAM from buffer palette
bool update_sprites_palette(PaletteRange *range) {
    UpdatePaletteFromBuffer(colorBuffer, &gamePalette, range);
    return false;
}

void reset_sprites(void) {
    basePalette = init_game_palette();
    MultiRgbToHsl(hslSprites, basePalette, &p_rangeSpritesAll);   
    min_max_sl_id(hslSprites, &p_rangeSpritesAll, &attrSprites);
    // MultiPalette2Buffer(colorBuffer, hslSprites, &hsl_incSprites[HSL_MAX], &p_rangeSpritesAll);
}

void reset_bomb_color(void) {
    hsl_incSprites[HSL_BOMB].h = 0;
    // reset with partial palette or hardcoded value? (all I need is the original hue value)
    MultiRgbToHsl(hslSprites, basePalette, &p_rangeBomb);
    MultiPalette2Buffer(colorBuffer, hslSprites , &hsl_incSprites[HSL_BOMB], &p_rangeBomb);
    do_update_bomb = true;
}

void reset_normal_map(void) {
    hsl_incSprites[HSL_MAX].h = 0;
    InitNormal2d(hslSprites, basePalette, &light, &p_rangeNormalMap, &attrSprites);
}

void update_ppplogo_color(void) {
    NormalMapLighting2d(hslSprites, basePalette, colorBuffer, &light, &p_rangeNormalMap, &hsl_incSprites[HSL_MAX]);
}

void update_ppplogo_palette(void) {
    UpdatePaletteFromBuffer(colorBuffer, &gamePalette, &p_rangeNormalMap);
}