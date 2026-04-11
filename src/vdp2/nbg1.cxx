#include "nbg1.h"
#include "../main.h"
#include "../core/math.h"
#include "palette.h"
#include "NBG1.pal"
#include "sprite_colors.h"

// using namespace SRL::Types;
using namespace SRL::Math::Types;

// static unsigned char current_background = T_DAY;

// initial image setup: hue, saturation, luminance, x_pos, y_pos, x_scale, y_scale, x_scroll (rate), y_scroll (rate), min_sat_id, max_sat_id, min_lum_id, max_lum_id
ImageAttr attrNbg1 = { 0, 0, 0, Fxp(0.0), Fxp(0.0), Fxp(0.25), Fxp(0.0), 0, 0, 0, 0}; // default attributes (for single color image)

void init_nbg1_img(void) {
    SRL::Bitmap::TGA* background = new SRL::Bitmap::TGA("BG0.TGA"); // Load Bitmap image to work RAM
    SRL::Tilemap::Interfaces::Bmp2Tile* Tilebmp = new SRL::Tilemap::Interfaces::Bmp2Tile(*background); // convert bitmap to tilemap
    delete background; // free original bitmap from work ram
    SRL::VDP2::NBG1::LoadTilemap(*Tilebmp); // Transfer tilemap from work RAM to VDP2 VRAM and register with NBG2
    delete Tilebmp; // free tilemap from work ram 
        
    SRL::VDP2::NBG1::SetPriority(SRL::VDP2::Priority::Layer2);//set NBG1 priority
    SRL::VDP2::NBG1::ScrollDisable();
    #ifdef SRL_HIGH_RES_NON_INTERLACED
        slZoomNbg1(toFIXED(0.50), toFIXED(1.0));
    #endif
}

// directly set color based on time slot
void update_nbg1_time_slot(void) {
    if (!g_GameOptions.use_rtc) {
        g_Game.timeSlot++;
        if (g_Game.timeSlot > BG_DAY)
        {
            g_Game.timeSlot = BG_DUSK;  // wrap back to first
        }
        
    }
    else {
        // update based on time of day
        DateTime time = DateTime::Now();
        
        if (time.Hour() >= T_DAWN && time.Hour() < T_DAY) {
            g_Game.timeSlot = BG_DAWN;
        }
        
        if (time.Hour() >= T_DAY && time.Hour() < T_DUSK) {
            g_Game.timeSlot = BG_DAY;
        }
        
        if (time.Hour() >= T_DUSK && time.Hour() < T_NIGHT) {
            g_Game.timeSlot = BG_DUSK;
        }
        
        if (time.Hour() >= T_NIGHT && time.Hour() < T_DAWN) {
            g_Game.timeSlot = BG_NIGHT;
        }
    }
    
    switch (g_Game.timeSlot) {
    	case BG_DAWN: {
    		LoadBackgroundPalette(nbg1_dawn);
    		attrSprites.hue = 21;
    		attrSprites.sat = 245;
            break;
        }
        case BG_DAY: {
            LoadBackgroundPalette(nbg1_day);
            attrSprites.hue = 350;
    		attrSprites.sat = 255;
            break;
        }
        case BG_DUSK: {
            LoadBackgroundPalette(nbg1_dusk);
            attrSprites.hue = 359;
    		attrSprites.sat = 255;
            break;
        }
        case BG_NIGHT: {
            LoadBackgroundPalette(nbg1_night);
            attrSprites.hue = 340;
    		attrSprites.sat = 215;
            break;
        }
        default: {
            break;
        }
    }
}

