#include "ColorHelpers.h"

void clamp_hue(VectorHSL *hsl)
{    
    if (hsl->h >= 360)
        hsl->h = hsl->h - 360;
        
    else if (hsl->h < 0)
        hsl->h = 360 + hsl->h;
}

void update_colors(VectorHSL *hsl, HSLTracker *hsl_increment, VectorRGB *color) {
    hsl->h += hsl_increment->h;
    hsl->s += hsl_increment->s;
    hsl->l += hsl_increment->l;
    clamp_hue(hsl);
    ColorHelpers_HSLToRGB(hsl, color);
}

void SinglePaletteUpdate(int index, VectorRGB color, SRL::CRAM::Palette palette)
{
    palette.GetData()[index] = SRL::Types::HighColor(color.r,  color.g,  color.b);
}

// use for real-time adjustments, then update the palette from bufferPal
void MultiPalette2Buffer(SRL::Types::HighColor *colorBuffer, VectorHSL *hslPal, HSLTracker *hsl_increment, PaletteRange *range) {
    VectorRGB color;
    for (int i = range->lower; i <= range->upper; i++) {
        update_colors(&hslPal[i], hsl_increment, &color);
        colorBuffer[i] = SRL::Types::HighColor(color.r,  color.g,  color.b);
    }
    hsl_increment->h = 0;
    hsl_increment->s = 0;
    hsl_increment->l = 0;
}

void UpdatePaletteFromBuffer(SRL::Types::HighColor *colorBuffer, SRL::CRAM::Palette *palette, PaletteRange *range) {
    for (int i = range->lower; i <= range->upper; i++) {
        palette->GetData()[i]  = colorBuffer[i];
    }
}

// transformations
void MultiRgbToHsl(VectorHSL *hslPal, uint16_t* basePalette, PaletteRange *range) {
    VectorRGB rgbColor;
    for (int i = range->lower; i <= range->upper; i++) {
        fromBGR555(basePalette[i], rgbColor.r, rgbColor.g, rgbColor.b);
        ColorHelpers_RGBToHSL(&rgbColor, &hslPal[i]);
    }
}

// use for real-time adjustments, then update the palette from bufferPal
void MultiHslTorRgb2Buffer(VectorHSL *hslPal, SRL::Types::HighColor *colorBuffer, PaletteRange *range) {
    static VectorRGB rgbColor;
    for (int i = range->lower; i <= range->upper; i++) {
        rgbColor.r = colorBuffer[i].Red;
        rgbColor.g = colorBuffer[i].Green;
        rgbColor.b = colorBuffer[i].Blue;
        ColorHelpers_HSLToRGB(&hslPal[i], &rgbColor); // I could probably just send it the truecolor
    }
}

// tools
void min_max_sl_id(VectorHSL *hslPal, PaletteRange *range, ImageAttr *attr) {
    attr->min_sat_id = range->lower;
    attr->max_sat_id = range->upper;
    for (int i = range->lower; i <= range->upper; i++) {
        if (hslPal[i].s < hslPal[attr->min_sat_id].s) {
            attr->min_sat_id = i;
        }
        if (hslPal[i].s > hslPal[attr->max_sat_id].s) {
            attr->max_sat_id = i;
        }
    }
    attr->min_lum_id = range->lower;
    attr->max_lum_id = range->upper;
    for (int i = range->lower; i <= range->upper; i++) {
        if (hslPal[i].l < hslPal[attr->min_lum_id].l) {
            attr->min_lum_id = i;
        }
        if (hslPal[i].l > hslPal[attr->max_lum_id].l) {
            attr->max_lum_id = i;
        }
    }
}

