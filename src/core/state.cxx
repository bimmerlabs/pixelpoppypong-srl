#include "../main.h"
#include "state.h"
#include "assets.h"
#include "screen_transition.h"
#include "../core/input.h" // this was included somewhere else (gameplay?)
#include "../game/gameplay.h"
#include "../game/ppp_logo.h"
#include "../game/title_screen.h"
#include "../game/character_select.h"
#include "../game/team_select.h"
#include "../game/credits.h"
#include "../game/highscores.h"
#include "../game/name_entry.h"
#include "../objects/player.h"
#include "../vdp2/nbg1.h"

uint16_t state_fade_timer = STATE_FADE_TIMER;

AttractScreenState g_AttractScreen = {
    .state = { ATTRACT_SCREEN_1, ATTRACT_SCREEN_2, ATTRACT_SCREEN_3, ATTRACT_SCREEN_4 },
    .id = 0,
};

// transistions between game states
void changeState(GAME_STATE newState)
{
    switch(newState)
    {
        case GAME_STATE_PPP_LOGO:
        {
            SRL::Debug::PrintClearScreen();
            pppLogo_init();
            reset_audio(MAX_VOLUME);
            playCDTrack(LOGO_TRACK, false);
            g_Game.gameState = GAME_STATE_PPP_LOGO;
            break;
        }
        case GAME_STATE_TITLE_SCREEN:
        {
            SRL::Debug::PrintClearScreen();
            g_Game.nextState = GAME_STATE_TITLE_SCREEN;            
            titleScreen_init();
            reset_audio(HALF_VOLUME);
            playCDTrack(TITLE_TRACK, true);
            g_Game.gameState = g_Game.nextState;
            break;
        }
        case GAME_STATE_TITLE_MENU:
        {
            SRL::Debug::PrintClearScreen();
            titleMenu_init();
            g_Game.nextState = GAME_STATE_TITLE_MENU;
            if (g_Game.gameState == GAME_STATE_GAMEPLAY || g_Game.gameState == GAME_STATE_TEAM_SELECT || g_Game.gameState == GAME_STATE_CHARACTER_SELECT) {
                reset_audio(HALF_VOLUME);
                playCDTrack(TITLE_TRACK, true);
            }
            g_Game.gameState = g_Game.nextState;
            break;
        }
        case GAME_STATE_TITLE_OPTIONS:
        {
            SRL::Debug::PrintClearScreen();
            optionsScreen_init();
            g_Game.gameState = GAME_STATE_TITLE_OPTIONS;
            break;
        }
        case GAME_STATE_DEMO_LOOP:
        {
            SRL::Debug::PrintClearScreen();
            g_Game.nextState = GAME_STATE_DEMO_LOOP;
            demo_init();
            gameplay_init();
            SRL::VDP2::NBG2::ScrollEnable();
            g_Game.gameState = g_Game.nextState;
            break;
        }
        // case GAME_STATE_CHARACTER_PORTRAITS:
        // {
            // SRL::Debug::PrintClearScreen();
            // changeState(GAME_STATE_UNINITIALIZED);
            // break;
        // }
        case GAME_STATE_TEAM_SELECT:
        {
            SRL::Debug::PrintClearScreen();
            reset_audio(MAX_VOLUME);
            teamSelect_init();
            playCDTrack(SELECT_TRACK, true);
            g_Game.gameState = GAME_STATE_TEAM_SELECT;
            break;
        }
        case GAME_STATE_CHARACTER_SELECT:
        {
            SRL::Debug::PrintClearScreen();
            reset_audio(MAX_VOLUME);
            characterSelectInit();
            playCDTrack(SELECT_TRACK, true);
            g_Game.gameState = GAME_STATE_CHARACTER_SELECT;
            break;
        }
        case GAME_STATE_GAMEPLAY:
        {
            SRL::Debug::PrintClearScreen();
            g_Game.nextState = GAME_STATE_GAMEPLAY;
            gameplay_init();
            g_Game.gameState = g_Game.nextState;
            break;
        }
        case GAME_STATE_NAME_ENTRY:
        {
            SRL::Debug::PrintClearScreen();
            g_Game.nextState = GAME_STATE_NAME_ENTRY;
            nameEntryInit();
            g_Game.gameState = g_Game.nextState;
            break;
        }
        case GAME_STATE_HIGHSCORES:
        {
            SRL::Debug::PrintClearScreen();
            g_Game.nextState = GAME_STATE_HIGHSCORES;
            init_game_palette();
            init_scores();
            g_Game.gameState = g_Game.nextState;
            break;
        }
        case GAME_STATE_CREDITS:
        {
            SRL::Debug::PrintClearScreen();
            g_Game.nextState = GAME_STATE_CREDITS;
            init_credits();
            g_Game.gameState = g_Game.nextState;
            break;
        }
        case GAME_STATE_UNINITIALIZED:
        {
            SRL::Debug::PrintClearScreen();
            SRL::VDP2::NBG2::ScrollDisable();
            SRL::VDP2::NBG3::ScrollDisable();
            SRL::TV::TVOff();
            initGame();
            init_game_palette();
            update_nbg1_time_slot();
            reset_audio(MAX_VOLUME);
            initTransitionStruct();
            reset_inputs();
            slColorCalcOn(OFF);
            slColRateNbg0(TRANSPARENCY_MIN);
            slScrPosNbg0(toFIXED(0), toFIXED(0)); // ERROR: Fxp to FIXED conversion
            g_Game.nextState = GAME_STATE_PPP_LOGO;
            changeState(g_Game.nextState);
            break;
        }
        default:
        {
            return;
        }
    }
}

void transitionState(GAME_STATE newState)
{
    
    g_Game.gameState = GAME_STATE_TRANSITION;
    g_Game.nextState = newState;
    g_Transition.timer = 0;

    // transition in has to be false
    g_Transition.mosaic_in = false;
    g_Transition.music_in = false;
    g_Transition.fade_in = false;
    g_Transition.all_in = false;
    
    if (g_GameOptions.mosaic_display) {
        g_Transition.mosaic_out = true;
    }
    g_Transition.music_out = true;
    g_Transition.fade_out = true;
    g_Transition.all_out = true;
    
    screenTransition_init(0, 0, 0);
    
    
    if (!g_GameOptions.debug_display) {
        slColOffsetOn(NBG0ON | NBG1ON | SPRON);
        slColOffsetAUse(NBG0ON);
        slColOffsetBUse(NBG1ON | SPRON);
        slColOffsetA(nbg1_rate, nbg1_rate, nbg1_rate);
    }
    else {
        slColOffsetOn(NBG1ON | SPRON);
        slColOffsetAUse(OFF);
        slColOffsetBUse(NBG1ON | SPRON);
        slColOffsetB(nbg1_rate, nbg1_rate, nbg1_rate);
    }
}

void game_state_update(void)
{
    if(g_Game.gameState != GAME_STATE_TRANSITION)
    {
        return;
    }
    
    if (!g_Transition.all_out) {
        changeState(g_Game.nextState);
    }
}

void attract_screen_state(void)
{
    g_AttractScreen.id++;
    if (g_AttractScreen.id >= ATTRACT_SCREEN_MAX) {
        g_AttractScreen.id = 0; // this will be 0 when demo mode is enabled
    }
}

