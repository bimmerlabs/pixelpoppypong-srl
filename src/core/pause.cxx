#include <srl.hpp>
//#include <stdlib.h>
//#include <string.h>
#include "../main.h"
#include "input.h"
#include "assets.h"
#include "backup.h"
#include "util.h"
#include "screen_transition.h"
#include "../game/gameplay.h"
#include "../objects/player.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;

int8_t pauseChoice = 0;

// typedef enum _PAUSE_OPTIONS
// {
#define PAUSE_OPTIONS_RESUME  (0)
#define PAUSE_OPTIONS_RESTART (1)
#define PAUSE_OPTIONS_QUIT    (2)
    #if ENABLE_DEBUG_MODE == 1
#define PAUSE_OPTIONS_DEBUG   (3)
#define PAUSE_OPTIONS_ANALOG  (4)
#define PAUSE_OPTION_MAX      (5)
    #else
#define PAUSE_OPTIONS_ANALOG  (3)
#define PAUSE_OPTION_MAX      (4)
    #endif
// } PAUSE_OPTIONS;

static void drawPauseMenuCursor(void);
static void drawPauseMenu(int options_y);
static void checkForPausePress(void);
static void checkForPauseMenu(void);

//
// Pause callbacks
//

// input for handling pause
void pause_input(void)
{
    if(g_Game.gameState != GAME_STATE_GAMEPLAY || g_Game.isRoundOver || g_Gameplay.isGameOver)
    {
        return;
    }
    if (g_Transition.mosaic_out) {
        g_Transition.mosaic_out = mosaicOut(NBG1ON);
        return;
    }
    if (g_Transition.mosaic_in) {
        g_Transition.mosaic_in = mosaicIn(NBG1ON);
        return;
    }
    if(!g_Game.isPaused) {
        // only check for pause press if the game is unpaused
        checkForPausePress();
    }
    else {
        // only check for pause menu presses if the game is paused
        checkForPauseMenu();
        if (pauseChoice == PAUSE_OPTIONS_ANALOG) {
            analogAdjustmentScreen_input();
        }
    }
}

// need to add background switching for pause screen
void pause_draw(void)
{
    if(g_Game.isPaused == true)
    {
        int options_y = 6;
        if (g_Game.gameMode == GAME_MODE_STORY) {
            SRL::Debug::Print(19, options_y, "Pawsed");
            options_y += 2;
            SRL::Debug::Print(15, options_y, "Score:%09d", g_Players[0].score.points + g_Players[0].score.total);
            options_y += 2;
            SRL::Debug::Print(15, options_y, "Continues:%i", g_Players[0].score.continues);
            options_y += 2;
        }
        else {
            options_y = 10; 
            SRL::Debug::Print(19, options_y, "Pawsed");
            options_y += 2;
        }            
        drawPauseMenu(options_y);
        drawPauseMenuCursor();
    }
}

//
// Pause private functions
//

// pause the game
void pauseGame(void)
{
    pauseChoice = 0;
    slColOffsetOn(NBG1ON);
    slColOffsetAUse(OFF);
    slColOffsetBUse(NBG1ON);
    nbg1_rate = PAUSE_FADE;
    slColOffsetB(nbg1_rate, nbg1_rate, nbg1_rate);
    if (g_GameOptions.mosaic_display) {
        g_Transition.mosaic_out = true;
    }
    g_Game.vblankClearScreen = true;
    g_Game.isPaused = true;
    g_Transition.mosaic_in_rate = MOSAIC_FAST_RATE;
    pcm_play(g_Assets.startPcm8, PCM_VOLATILE, 6);
    SRL::VDP2::NBG2::ScrollEnable();
}

// check if player 1 paused the game
static void checkForPausePress(void)
{
    if (g_Game.selectStoryCharacter)
    {
        return;
    }
    
    PPLAYER player = &g_Players[0];

    Digital gamepad(player->input->id);
    
    if (gamepad.WasPressed(Digital::Button::START))
    {
        pauseGame();
    }
}

// pause menu options
static void checkForPauseMenu(void)
{
    PPLAYER player = &g_Players[0];

    Digital gamepad(player->input->id);
    
    if (gamepad.WasPressed(Digital::Button::Up))
    {
        pcm_play(g_Assets.cursorPcm8, PCM_VOLATILE, 6);
        pauseChoice--;
    }

    if (gamepad.WasPressed(Digital::Button::Down))
    {
        pcm_play(g_Assets.cursorPcm8, PCM_VOLATILE, 6);
        pauseChoice++;
    } 
     
    if (gamepad.WasPressed(Digital::Button::Left))
    {
        switch(pauseChoice)
        {
            #if ENABLE_DEBUG_MODE == 1
            case PAUSE_OPTIONS_DEBUG:
                pcm_play(g_Assets.cursorPcm8, PCM_VOLATILE, 6);
                g_GameOptions.debug_display = !g_GameOptions.debug_display;
                g_Game.vblankClearScreen = true;
                break;
            #endif
            default:
                break;
        }
    }
    else if (gamepad.WasPressed(Digital::Button::Right))
    {
        switch(pauseChoice)
        {
            #if ENABLE_DEBUG_MODE == 1
            case PAUSE_OPTIONS_DEBUG:
                pcm_play(g_Assets.cursorPcm8, PCM_VOLATILE, 6);
                g_GameOptions.debug_display = !g_GameOptions.debug_display;
                g_Game.vblankClearScreen = true;
                break;
            #endif
            default:
                break;
        }
    }
    
    // keep pause screen choice in range
    sanitizeValue(&pauseChoice, 0, PAUSE_OPTION_MAX);

    if (gamepad.WasPressed(Digital::Button::START) || gamepad.WasPressed(Digital::Button::A)|| gamepad.WasPressed(Digital::Button::C))
    {
        SRL::VDP2::NBG2::ScrollDisable();
        // save_game_backup();
        switch(pauseChoice)
        {
            case PAUSE_OPTIONS_RESUME:
                SRL::Debug::PrintClearScreen();
                pcm_play(g_Assets.cancelPcm8, PCM_VOLATILE, 6);
                // simply unpause
                g_Transition.mosaic_in_rate = MOSAIC_FAST_RATE;
                if (g_GameOptions.mosaic_display) {
                    g_Transition.mosaic_in = true;
                }
                slColOffsetB(NEUTRAL_FADE, NEUTRAL_FADE, NEUTRAL_FADE);
                g_Game.isPaused = false;
                break;

            case PAUSE_OPTIONS_RESTART:
                SRL::Debug::PrintClearScreen();
                pcm_play(g_Assets.nextPcm8, PCM_VOLATILE, 6);
                // start a new game without going to title or team select
                g_Transition.mosaic_in_rate = MOSAIC_FAST_RATE;
                if (g_GameOptions.mosaic_display) {
                    g_Transition.mosaic_in = true;
                }
                slColOffsetB(NEUTRAL_FADE, NEUTRAL_FADE, NEUTRAL_FADE);
                changeState(GAME_STATE_GAMEPLAY);
                break;

            case PAUSE_OPTIONS_QUIT:
                SRL::Debug::PrintClearScreen();
                pcm_play(g_Assets.cancelPcm8, PCM_VOLATILE, 6);
                transitionState(GAME_STATE_UNINITIALIZED);
                break;
            #if ENABLE_DEBUG_MODE == 1
            case PAUSE_OPTIONS_DEBUG:
                pcm_play(g_Assets.cancelPcm8, PCM_VOLATILE, 6);
                // simply unpause
                g_Transition.mosaic_in_rate = MOSAIC_FAST_RATE;
                if (g_GameOptions.mosaic_display) {
                    g_Transition.mosaic_in = true;
                }
                slColOffsetB(NEUTRAL_FADE, NEUTRAL_FADE, NEUTRAL_FADE);
                g_Game.isPaused = false;
                break;
            #endif
            case PAUSE_OPTIONS_ANALOG:
                pcm_play(g_Assets.cancelPcm8, PCM_VOLATILE, 6);
                // simply unpause
                g_Transition.mosaic_in_rate = MOSAIC_FAST_RATE;
                if (g_GameOptions.mosaic_display) {
                    g_Transition.mosaic_in = true;
                }
                slColOffsetB(NEUTRAL_FADE, NEUTRAL_FADE, NEUTRAL_FADE);
                g_Game.isPaused = false;
                break;

            default:
                break;
        }
    }
    else if (gamepad.WasPressed(Digital::Button::B))
    {
        SRL::VDP2::NBG2::ScrollDisable();
        SRL::Debug::PrintClearScreen();
        // save_game_backup();
        pcm_play(g_Assets.cancelPcm8, PCM_VOLATILE, 6);
        // simply unpause
        g_Transition.mosaic_in_rate = MOSAIC_FAST_RATE;
        if (g_GameOptions.mosaic_display) {
        g_Transition.mosaic_in = true;
        }
        slColOffsetB(NEUTRAL_FADE, NEUTRAL_FADE, NEUTRAL_FADE);
        g_Game.isPaused = false;
    }
}

// Options menu + values
static void drawPauseMenu(int options_y)
{                
    int options_x = 15;
    SRL::Debug::Print(options_x, options_y, "Resume");
    options_y += 2;
    SRL::Debug::Print(options_x, options_y, "Restart");
    options_y += 2;
    SRL::Debug::Print(options_x, options_y, "Quit");
    #if ENABLE_DEBUG_MODE == 1
    options_y += 2;
    SRL::Debug::Print(options_x, options_y, g_GameOptions.debug_display ? "Debug:On " : "Debug:Off");
    #endif
    options_y += 2;
    SRL::Debug::Print(options_x, options_y, "Analog Adjustment:");
    options_y += 1;
    analogAdjustmentScreen_draw(options_x, options_y);    
}

const Angle cursorAngleAdder = Angle(0.0222222222222222);

static void drawPauseMenuCursor(void)
{
    Fxp offset = SRL::Math::Trigonometry::Sin(g_Game.cursor_angle) * Fxp_8;
    cursor.pos.x = Fxp(-124) + offset;
    Fxp choice = Fxp::Convert(pauseChoice);
    cursor.pos.y = Fxp(-32) + (choice * Fxp(32));
    my_sprite_draw(&cursor);
    g_Game.cursor_angle += cursorAngleAdder;
}
