#include "../main.h"
#include "credits.h"
#include "player_setup.h"
#include "../core/assets.h"
#include "../core/screen_transition.h"
#include "../objects/player.h"
#include "../vdp2/nbg1.h"

CREDITS credits = {};

Fxp bg_height = Fxp(48);

void initCreditsStruct(void) {
    credits.timer = 0;
    credits.fade_in = false;
    credits.display = false;
    credits.fade_out = false;
    credits.id = 0;
    credits.display_timer = 0;
    credits.delay_timer = 0;
    credits.bg_id = 4;
    credits.transparency_rate = TRANSPARENCY_MAX;
};

void init_credits(void)
{
    if (g_GameOptions.mosaic_display) {
        g_Transition.mosaic_in = true;
    }
    g_Transition.music_in = true;
    g_Transition.fade_in = true;
    g_Transition.all_in = true;

    initCreditsStruct();
    
    // text transparency (maybe use SRL here)
    slColorCalc(CC_RATE | CC_TOP | NBG0ON | SPRON);
    slColorCalcOn(NBG0ON | SPRON);
    slColRateNbg0 ( credits.transparency_rate );
    
    g_Transition.mosaic_in_rate = MOSAIC_SLOW_RATE;
    menu_bg1.mesh = MESHoff;
    
    
    menu_bg1.id = menu_bg1.anim[0].asset + credits.bg_id;
    set_spr_position(&menu_bg1, 0, 0, 95);
    set_spr_scale(&menu_bg1, 0, 0);

    g_Game.lastState = GAME_STATE_CREDITS;
    playCDTrack(CREDITS_TRACK, false);
}

void display_credits(void)
{
    credits.timer++;
    if (attrNbg1.x_scroll > Fxp(0)) {
        attrNbg1.x_pos += attrNbg1.x_scroll;
        if (attrNbg1.x_pos > Fxp(512.0))
            attrNbg1.x_pos = Fxp(0);
    }
    slScrPosNbg1(attrNbg1.x_pos.RawValue(), attrNbg1.y_pos.RawValue());   
    
    // wait to start credits
    if (credits.timer == CREDITS_BEGIN) {
        if (!g_GameOptions.debug_display && g_GameOptions.mosaic_display) {
            mosaicInit(NBG0ON);
        }
        credits.display = true;
        credits.fade_in = true;
    }
    
    if (credits.display) {
        if (credits.fade_in) {
            if (!g_GameOptions.debug_display && g_GameOptions.mosaic_display) {
                g_Transition.mosaic_in = mosaicIn(NBG0ON);
            }
            if (g_Game.frame % 4 == 0 && credits.transparency_rate > TRANSPARENCY_MIN) { // modulus
                credits.transparency_rate -= 1;
                slColRateNbg0(credits.transparency_rate); // Fade in effect
            }
            else if (credits.transparency_rate == TRANSPARENCY_MIN) { // Fully faded in
                credits.display_timer = CREDITS_DISPLAY_TIME;
                credits.fade_in = false;
            }
            if (credits.transparency_rate > TRANSPARENCY_MIN) {
                if (menu_bg1.scl.x < Fxp(704)) {
                    menu_bg1.scl.x += Fxp_8;
                }
                if (menu_bg1.scl.y < bg_height) {
                    menu_bg1.scl.y += Fxp_1;
                }
            }
        }

        else if (credits.fade_out) {
            if (!g_GameOptions.debug_display && g_GameOptions.mosaic_display) {
                g_Transition.mosaic_out = mosaicOut(NBG0ON);
            }
            if (g_Game.frame % 2 == 0 && credits.transparency_rate < TRANSPARENCY_MAX) { // modulus
                credits.transparency_rate += 1;
                slColRateNbg0(credits.transparency_rate); // Fade out effect
            }
            else if (credits.transparency_rate == TRANSPARENCY_MAX) { // Fully faded out
                credits.delay_timer = CREDITS_DELAY_TIME; // Set delay before the next text
                credits.fade_out = false;
                g_Game.vblankClearScreen = true;
                credits.id++; // Move to the next text
            }
            if (credits.transparency_rate < TRANSPARENCY_MAX) {
                if (menu_bg1.scl.y > Fxp_0) {
                    menu_bg1.scl.y -= Fxp_HALF;
                }
            }
        }

        if (credits.display_timer > 0) { // Display text
            credits.display_timer--;
            if (credits.display_timer == 0) {
                credits.fade_out = true; // Start fading out
            }
        }
        else if (credits.delay_timer > 0) { // Delay before fading in
            credits.delay_timer--;
            if (menu_bg1.scl.y > Fxp_0) {
                menu_bg1.scl.y -= Fxp_1;
            }
            if (credits.delay_timer == 0) {
                menu_bg1.scl.x = Fxp_0;
                menu_bg1.scl.y = bg_height; // test
                menu_bg1.id = menu_bg1.anim[0].asset + credits.bg_id;
                if (!g_GameOptions.debug_display && g_GameOptions.mosaic_display) {
                    g_Transition.mosaic_in = true;
                }
                credits.fade_in = true; // Start fading in
            }
        }

        if (credits.id == 0) {
            bg_height = Fxp(48);
            SRL::Debug::Print(CREDITS_X2, 14, "Pixel Poppy Pong 2026");
            SRL::Debug::Print(19, 15, "Credits...");
        }
        else if (credits.id == 1) {
            bg_height = Fxp(48);
            SRL::Debug::Print(CREDITS_X1, 14, "Programming/Graphics:");
            SRL::Debug::Print(CREDITS_X2, 15, "C.Seigman \"Hassmaschine\"");
        }

        else if (credits.id == 2) {
            bg_height = Fxp(48);
            SRL::Debug::Print(CREDITS_X1, 14, "Original Soundtrack By:");
            SRL::Debug::Print(CREDITS_X2, 15, "Random");
        }

        else if (credits.id == 3) {
            bg_height = Fxp(48);
            SRL::Debug::Print(CREDITS_X1, 14, "Featuring:");
            SRL::Debug::Print(CREDITS_X2, 15, "Ponesound");
        }

        else if (credits.id == 4) {
            bg_height = Fxp(48);
            SRL::Debug::Print(CREDITS_X1, 14, "Built with Saturn Rings Library");
            SRL::Debug::Print(CREDITS_X2, 15, "srl.reye.me");
        }

        else if (credits.id == 5) {
            bg_height = Fxp(48);
            slScrPosNbg0(toFIXED(0), toFIXED(-4));
            SRL::Debug::Print(CREDITS_X1, 13, "Original Background Art:");
            SRL::Debug::Print(CREDITS_X2, 14, "Tatiana Sherbul");
            SRL::Debug::Print(CREDITS_X2, 15, "www.behance.net/t-sherbul");
        }

        else if (credits.id == 6) {
            bg_height = Fxp(56);
            slScrPosNbg0(toFIXED(0), toFIXED(0));
            SRL::Debug::Print(CREDITS_X1, 13, "Special Thanks:");
            SRL::Debug::Print(CREDITS_X2, 14, "The SRL team");
            SRL::Debug::Print(CREDITS_X2, 15, "SegaXtreme Discord");
            SRL::Debug::Print(CREDITS_X2, 16, "Sega Saturn Shiro!");
        }

        else if (credits.id == 7) {
            bg_height = Fxp(32);
            slScrPosNbg0(toFIXED(0), toFIXED(-4));
            SRL::Debug::Print(18, 14, "THE END!");
        }

        else if (credits.id == 8)
        {
            g_Game.vblankClearScreen = true;
            slColorCalcOn(OFF);
            slScrMosaicOn(OFF);
            slScrMosSize(MOSAIC_MIN, MOSAIC_MIN);
            slScrPosNbg0(toFIXED(0), toFIXED(0));
            g_Game.lastState = GAME_STATE_CREDITS;
            transitionState(GAME_STATE_UNINITIALIZED);
        }

        my_sprite_draw(&menu_bg1); // shadow

    }
}

void credits_input(void)	{
    PPLAYER player = &g_Players[0];
    
    if (!player->input->isSelected)
    {
        check_ui_inputs();
    }

    Digital gamepad(player->input->id);
    
    if (gamepad.WasPressed(Digital::Button::START)) {
        g_Game.vblankClearScreen = true;
        slColorCalcOn(OFF);
        slScrMosaicOn(OFF);
        slScrMosSize(MOSAIC_MIN, MOSAIC_MIN);
        slScrPosNbg0(toFIXED(0), toFIXED(0));
        g_Game.lastState = GAME_STATE_CREDITS;
        transitionState(GAME_STATE_UNINITIALIZED);
    }
}