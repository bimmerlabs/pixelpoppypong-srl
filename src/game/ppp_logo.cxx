#include "../main.h"
#include "ppp_logo.h"
#include "player_setup.h"
#include "../core/assets.h"
#include "../core/state.h"
#include "../core/screen_transition.h"
#include "../vdp2/lighting.h"
#include "../vdp2/sprite_colors.h"
#include "../vdp2/nbg1.h"

// Using to shorten names for Vector and HighColor
using namespace SRL::Types;
using namespace SRL::Math::Types;
using namespace SRL::Math;
using namespace SRL::Input;

unsigned int g_LogoTimer = 0;

bool test_colors = false;

// initializations for PPP screen
void pppLogo_init(void)
{
    // I think everything fits into VRAM, so there's no real need to unload anything
    // if (g_Game.lastState == GAME_STATE_TEAM_SELECT 
     // || g_Game.lastState == GAME_STATE_GAMEPLAY 
     // || g_Game.lastState == GAME_STATE_DEMO_LOOP 
     // || g_Game.lastState == GAME_STATE_CREDITS) {
        // unloadGameAssets();
    // }
    
    g_Game.lastState = GAME_STATE_PPP_LOGO;
    
    reset_normal_map();
    
    SRL::TV::TVOn();
    // SRL::Debug::Print(18, 14, "LOADING!");
    SRL::Debug::Print(18, 14, "  BOO!"); // MAKE A DIFFERENT MESSAGE PER DAY?
    
    if (!g_Assets.coreAssetsLoaded) {
        loadCoreAssets();
        loadCoreSoundAssets();
        g_Assets.coreAssetsLoaded = true;
    }
    else {
        switchCoreAssets();
    }
    if (!g_Assets.titleAssetsLoaded) {
        loadTitleScreenAssets();        
    }
    
    SRL::Debug::PrintClearScreen();
    
    if (g_GameOptions.mesh_display) {
        pppshadow.mesh = MESHon;
    }
    else {
        pppshadow.mesh = MESHoff;
    }
    
    light.x = Fxp(10);
    light.y = Fxp(255);
    light.z = Fxp(255);
    
    set_spr_scale(&pixel_poppy, 1.0, 1.0);
    pixel_poppy.rot.z = 0;
    set_spr_position(&pixel_poppy, 10, 255, 100);
    sprite_frame_reset(&pixel_poppy);
        
    g_LogoTimer = 0;
    
    
    screenTransition_init(MINIMUM_FADE, MINIMUM_FADE, MINIMUM_FADE);
        
    if (g_GameOptions.mosaic_display) {
        mosaicInit(NBG1ON);
    }
    g_Transition.fade_in_rate = 1;
    if (!g_GameOptions.debug_display) {
        slColOffsetOn(NBG0ON | SPRON);
        slColOffsetAUse(NBG0ON);
        slColOffsetBUse(NBG1ON);
        slColOffsetA(nbg1_rate, nbg1_rate, nbg1_rate);
        slColOffsetB(nbg1_rate, nbg1_rate, nbg1_rate);
    }
    else {
        slColOffsetOn(NBG1ON);
        slColOffsetAUse(OFF);
        slColOffsetBUse(SPRON);
        slColOffsetB(nbg1_rate, nbg1_rate, nbg1_rate);
    }
        
    SRL::VDP2::NBG1::ScrollEnable();
    
    g_Transition.mosaic_in_rate = MOSAIC_SLOW_RATE;
    g_Transition.music_in = true;
    g_Transition.all_in = true;
    test_colors = false;
}

// update callback routine for PPP logo

void pppLogo_input(void)
{
    PPLAYER player = &g_Players[0];
    
    if (!player->input->isSelected)
    {
        check_ui_inputs();
    }
    if (player->input->isSelected)
    {
        // Digital gamepad(player->input->id);

        // if (gamepad.WasPressed(Digital::Button::A) && attrSprites.hue < 360)
        // {
            // hsl_incSprites[HSL_MAX].h++;
        // }
        // else if (gamepad.WasPressed(Digital::Button::B) && attrSprites.hue > 0)
        // {
            // hsl_incSprites[HSL_MAX].h--;
        // }
        // else if (gamepad.WasPressed(Digital::Button::X))
        // {
            // light.ambient++;
        // }
        // else if (gamepad.WasPressed(Digital::Button::Y))
        // {
            // light.ambient--;
        // }        
        // else if (gamepad.WasPressed(Digital::Button::START) && test_colors)
        // {
            // set everything back to defaults
            nbg1_rate = NEUTRAL_FADE;
            slColOffsetA(nbg1_rate, nbg1_rate, nbg1_rate);
            slColOffsetB(nbg1_rate, nbg1_rate, nbg1_rate);
            g_Transition.mosaic_x = MOSAIC_MIN;
            g_Transition.mosaic_y = MOSAIC_MIN;
            slScrMosSize(g_Transition.mosaic_x, g_Transition.mosaic_y);
            g_Transition.fade_in_rate = 8;
            changeState(GAME_STATE_TITLE_SCREEN);
            return;
        // }

        // test_colors = true;
        // SRL::Debug::Print(2, 21, "Hue_inc:%3d ", hsl_incSprites[HSL_MAX].h);
        // SRL::Debug::Print(2, 22, "Hue:%3d ", hslSprites[240].h);
        // SRL::Debug::Print(2, 23, "light.ambient:%3d ", light.ambient);

    }

    // shouldn't need this since the inputs will always be reset when restarting the loop at ppplogo
    // else {
        // Digital gamepad(player->input->id);
        // //
        // // skip the logo if player 1 hits start
        // //
        // if(gamepad.WasPressed(Digital::Button::START))
        // {
            // // set everything back to defaults
            // nbg1_rate = NEUTRAL_FADE;
            // slColOffsetA(nbg1_rate, nbg1_rate, nbg1_rate);
            // slColOffsetB(nbg1_rate, nbg1_rate, nbg1_rate);
            // g_Transition.mosaic_x = MOSAIC_MIN;
            // g_Transition.mosaic_y = MOSAIC_MIN;
            // slScrMosSize(g_Transition.mosaic_x, g_Transition.mosaic_y);
            // g_Transition.fade_in_rate = 8;
            // changeState(GAME_STATE_TITLE_SCREEN);
            // return;
        // }
    // }
}

// update callback routine for PPP logo
void pppLogo_update(void)
{
    g_LogoTimer++;
    
    // transition mosaic in
    if(g_LogoTimer > 4)
    {
        g_Transition.slow_fade_in = true;
        g_Transition.all_in = true;
    }    
    // transition mosaic in
    if(g_LogoTimer > PPP_MOSAIC_TIMER)
    {
        g_Transition.mosaic_in = true;
        g_Transition.all_in = true;
        if (g_Transition.fade_out) {
            g_Transition.fade_out = fadeOut(1, NEUTRAL_FADE);
        }
        pppLogo_draw();
        update_light_position();
    }
    else if (g_GameOptions.mosaic_display) {
        mosaicRandom(NBG1ON);
    }
    
    if(g_LogoTimer == PPP_MOSAIC_TIMER)
    {
        g_Transition.fade_out = true;
        nbg1_rate = MAXIMUM_FADE;
        if (!g_GameOptions.debug_display) {
            slColOffsetA(nbg1_rate, nbg1_rate, nbg1_rate);
        }
        slColOffsetB(nbg1_rate, nbg1_rate, nbg1_rate);
    }
    if(g_LogoTimer > PPP_LOGO_TIMER)
    {   
        SRL::Debug::PrintClearScreen();
        g_Transition.fade_in_rate = 8;
        changeState(GAME_STATE_TITLE_SCREEN);
        return;
    }
}

static Angle lightAngle;
constexpr Angle lightAngleAdder = Angle(0.0055555555555556);
constexpr Fxp x_radius = Fxp(155);
constexpr Fxp y_radius = Fxp(80);

void pppLogo_draw(void)
{
    my_sprite_draw(&ppplogo);
    my_sprite_draw(&pppshadow);
    
    my_sprite_draw_rot(&pixel_poppy);
    SRL::Debug::Print(17, 19, "Presents...");
    #if ENABLE_DEBUG_MODE == 1
    if (g_GameOptions.debug_display) {
        SRL::Debug::Print(2, 21, "LightAngle:%d", lightAngle);
    }
    #endif
}

// draw an ellipse
void update_light_position(void) {
    lightAngle -= lightAngleAdder;
    Fxp fixedAngle = lightAngle.ToFxp();
    
    light.x = Fxp(127) + Trigonometry::Cos(fixedAngle) * x_radius;
    light.y = Fxp(127) + Trigonometry::Sin(fixedAngle) * y_radius;

    pppshadow.pos.x = -Trigonometry::Cos(fixedAngle) * Fxp(9);
    pppshadow.pos.y = Trigonometry::Sin(fixedAngle) * Fxp(6);
    
    pixel_poppy.pos.x = 2*(light.x - Fxp(127));
    pixel_poppy.pos.y = -2*(light.y - Fxp(127));
    pixel_poppy.rot.z = Angle(0.25)-Angle(fixedAngle * Fxp(2));

    do_update_ppplogo = true;
}
