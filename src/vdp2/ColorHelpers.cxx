// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: ColorHelpers Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// Modified for Saturn by: Hassmaschine
// ---------------------------------------------------------------------
#include "ColorHelpers.h"

#define COLOR_MIN(a, b)                      ((a) < (b) ? (a) : (b))
#define COLOR_MAX(a, b)                      ((a) > (b) ? (a) : (b))

void ColorHelpers_RGBToHSL(VectorRGB *color, VectorHSL *hsl)
{
    if (!color->r && !color->g && !color->b) {
        if (hsl) {
            hsl->h = 0;
            hsl->s = 0;
            hsl->l = 0;
        }
        return;
    }

    short min = COLOR_MIN(COLOR_MIN(color->r, color->g), color->b);
    short max = COLOR_MAX(COLOR_MAX(color->r, color->g), color->b);

    short chroma = max - min;
    if (max) {
        if (max == min) {
            if (hsl) {
                hsl->h = 0;
                hsl->s = 0;
                hsl->l = min;
            }
        } else {
            if (hsl) {
                short h = 0;

                if (color->r == max)
                    h = 60 * (short)(color->g - color->b) / chroma;
                else if (color->g == max)
                    h = 60 * (short)(color->b - color->r) / chroma + 120;
                else
                    h = 60 * (short)(color->r - color->g) / chroma + 240;

                if (h < 0)
                    h += 360;
                    
                if (h >= 360)
                    h -= 360;

                hsl->h = h;
                hsl->s = 255 * chroma / max;
                hsl->l = max;
            }
        }
    }
}

void ColorHelpers_HSLToRGB(VectorHSL *hsl, VectorRGB *color)
{
    unsigned char green = 0, red = 0, blue = 0;

    // Clamp saturation and luminance to the 0-255 range for calculation - 8/24/2024
    short s_clamped = hsl->s < 0 ? 0 : (hsl->s > 255 ? 255 : hsl->s);
    short l_clamped = hsl->l < 0 ? 0 : (hsl->l > 255 ? 255 : hsl->l);

    if (s_clamped) {
        short s = l_clamped * s_clamped / 255;
        short h_mod = hsl->h % 60;  // Compute modulus once
        short s_times_mod = s * h_mod / 60;  // Precompute this part
        
        short p = l_clamped - s;
        short q = l_clamped - s_times_mod;
        short t = p + s_times_mod;  // Use the precomputed term for `t`

        switch (hsl->h / 60) {
            case 0:
                red   = l_clamped;
                green = t;
                blue  = p;
                break;

            case 1:
                red   = q;
                green = l_clamped;
                blue  = p;
                break;

            case 2:
                red   = p;
                green = l_clamped;
                blue  = t;
                break;

            case 3:
                red   = p;
                green = q;
                blue  = l_clamped;
                break;

            case 4:
                red   = t;
                green = p;
                blue  = l_clamped;
                break;

            case 5:
            default:
                red   = l_clamped;
                green = p;
                blue  = q;
                break;
        }
    } else {
        red   = l_clamped;
        green = l_clamped;
        blue  = l_clamped;
    }
        color->r = red;  // we never pass a null pointer here, so get rid of condition check
        color->g = green;
        color->b = blue;
}


