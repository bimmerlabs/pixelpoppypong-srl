#pragma once

#include <srl.hpp>
#include "palettetools.h"
#include "../core/math.h" // can we use SRL math instead?

using namespace SRL::Types;
using namespace SRL::Math::Types;

typedef struct {
    Fxp  x; // east / west
    Fxp  y; // north / south
    Fxp  z; // up / down
    unsigned char  ambient;
    char  intensity;
    uint16_t hue;
} LightSource;

extern LightSource light;

#ifdef __cplusplus
extern "C" {
#endif

void InitNormal2d(VectorHSL *hslPal, uint16_t* basePalette, LightSource *_light, PaletteRange *range, ImageAttr *img_cfg);
void NormalMapLighting2d(VectorHSL *hslPal, uint16_t* basePalette, SRL::Types::HighColor *colorBuffer, LightSource *_light, PaletteRange *range, HSLTracker *hsl_increment);

#ifdef __cplusplus
}
#endif
