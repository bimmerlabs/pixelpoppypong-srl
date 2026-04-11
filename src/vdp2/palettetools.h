#pragma once

#include <srl.hpp>

#define MAX_PALETTE_ENTRIES 256

using namespace SRL::Types;
using namespace SRL::Math::Types;

// // Struct definitions (original)
// typedef struct {
    // Uint8 r;
    // Uint8 g;
    // Uint8 b;
// } ObjectColor;

// typedef struct {
    // Sint16 h;
    // Sint16 s;
    // Sint16 l;
// } ObjectHSL;

// typedef struct {
    // Sint16 h;
    // Sint16 s;
    // Sint16 l;
// } GlobalHSL;

// Struct definitions
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} VectorRGB;

typedef struct {
    int16_t h; // 0-360 - maybe use SRL angle?
    int16_t s;
    int16_t l;
} VectorHSL;

typedef struct {
    int16_t h;
    int16_t s;
    int16_t l;
} HSLTracker;

typedef struct {
    uint8_t lower;
    uint8_t upper;
} PaletteRange;

// there are too many things here - delete everything not related to lighting?
typedef struct {
    uint16_t hue;
    uint8_t sat;
    uint8_t lum;
    Fxp x_pos;
    Fxp y_pos;
    Fxp x_scroll;
    Fxp y_scroll;
    uint8_t min_sat_id;
    uint8_t max_sat_id;
    uint8_t min_lum_id;
    uint8_t max_lum_id;
} ImageAttr;

#ifdef __cplusplus
extern "C" {
#endif

inline uint16_t toBGR555(uint8_t r, uint8_t g, uint8_t b)
{
    uint16_t r5 = (r >> 3) & 0x1F;
    uint16_t g5 = (g >> 3) & 0x1F;
    uint16_t b5 = (b >> 3) & 0x1F;

    return static_cast<uint16_t>(0x8000 | (b5 << 10) | (g5 << 5) | r5);
}

inline void fromBGR555(uint16_t color, uint8_t& r, uint8_t& g, uint8_t& b)
{
    uint8_t r5 =  color        & 0x1F;
    uint8_t g5 = (color >> 5)  & 0x1F;
    uint8_t b5 = (color >> 10) & 0x1F;

    // // Exact inverse of >>3 (fills low bits with zeros)
    // r = r5 << 3;
    // g = g5 << 3;
    // b = b5 << 3;
    
    // Scale to 8 bits
    r = (r5 << 3) | (r5 >> 2);
    g = (g5 << 3) | (g5 >> 2);
    b = (b5 << 3) | (b5 >> 2);
}

// Function prototypes
void clamp_hue(VectorHSL *hsl);
void update_colors(VectorHSL *hsl, HSLTracker *hsl_increment, VectorRGB *color);
void SinglePaletteUpdate(int index, VectorRGB color, SRL::CRAM::Palette palette);

void MultiPalette2Buffer(SRL::Types::HighColor *colorBuffer, VectorHSL *hslPal, HSLTracker *hsl_increment, PaletteRange *range);
void UpdatePaletteFromBuffer(SRL::Types::HighColor *colorBuffer, SRL::CRAM::Palette *palette, PaletteRange *range);

void MultiRgbToHsl(VectorHSL *hslPal, uint16_t* basePalette, PaletteRange *range);

void MultiHslTorRgb2Buffer(VectorHSL *hslPal, SRL::Types::HighColor *colorBuffer, PaletteRange *range);

void min_max_sl_id(VectorHSL *hslPal, PaletteRange *range, ImageAttr *attr);


#ifdef __cplusplus
}
#endif