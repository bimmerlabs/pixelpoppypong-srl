#include "lighting.h"
#include "colorhelpers.h"
#include "palettetools.h"
#include "../core/util.h"

LightSource light = {Fxp(10), Fxp(255), Fxp(255), 31, 0, 0};  // scene light

// since VDP2 is basically 2d, there is no need to use the b channel or z distance in the calculation (the normal is always 1)
// only use for initial setup
void InitNormal2d(VectorHSL *hslPal, uint16_t* basePalette, LightSource *_light, PaletteRange *range, ImageAttr *img_cfg) {
    VectorRGB rgbColor;
    
    for (int i = range->lower; i <= range->upper; i++) {
        hslPal[i].h = img_cfg->hue;
        hslPal[i].s = img_cfg->sat;
        hslPal[i].l = img_cfg->lum;
        
        fromBGR555(basePalette[i], rgbColor.r, rgbColor.g, rgbColor.b);
        // Calculate the difference between the light source XYZ and the palette RGB values
        int diff_r = _light->x.As<int32_t>() - rgbColor.r;
        int diff_g = _light->y.As<int32_t>() - rgbColor.g;

        // Calculate the luminance adjustment based on the closeness of the light source to the color
        // For simplicity, let's assume we adjust it based on the Euclidean distance
        unsigned int value = diff_r * diff_r + diff_g * diff_g;
        short distance = ApproximateIntegerSqrt(value);
        
        hslPal[i].l = MAX(0, (255 - distance) + (_light->z.As<int32_t>() - 255)) + _light->ambient; // this could probably be more efficient
    }
}

// use for real-time adjustments, then update the palette from bufferPal
void NormalMapLighting2d(
                            VectorHSL *hslPal, 
                            uint16_t* basePalette, 
                            SRL::Types::HighColor *colorBuffer, 
                            LightSource *_light,
                            PaletteRange *range,
                            HSLTracker *hsl_increment
                         ) 
{
    VectorRGB rgbColor;
    
    for (int i = range->lower; i <= range->upper; i++) {        
        fromBGR555(basePalette[i], rgbColor.r, rgbColor.g, rgbColor.b);
        
        // Calculate the difference between the light source XYZ and the palette RGB values
        int diff_r = _light->x.As<int32_t>() - rgbColor.r;
        int diff_g = _light->y.As<int32_t>() - rgbColor.g;

        // Calculate the luminance adjustment based on the closeness of the light source to the color
        // For simplicity, let's assume we adjust it based on the Euclidean distance
        unsigned int value = diff_r * diff_r + diff_g * diff_g;
        short distance = ApproximateIntegerSqrt(value);

        hslPal[i].l = MAX(0, (255 - distance) + (_light->z.As<int32_t>() - 255)) + _light->ambient;
        
        update_colors(&hslPal[i], hsl_increment, &rgbColor);
        colorBuffer[i]  = SRL::Types::HighColor(rgbColor.r, rgbColor.g, rgbColor.b);
        // if (i == 240)
            // SRL::Debug::Print(2, 23, "hslPal.h:%3d ", hslPal[i].h);
    }
    hsl_increment->h = 0;
    hsl_increment->s = 0;
    hsl_increment->l = 0;
}

