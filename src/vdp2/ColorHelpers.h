#pragma once

#include "palettetools.h"

#ifdef __cplusplus
extern "C" {
#endif

void ColorHelpers_RGBToHSL(VectorRGB *color, VectorHSL *hsl);
void ColorHelpers_HSLToRGB(VectorHSL *hsl, VectorRGB *color);

#ifdef __cplusplus
}
#endif