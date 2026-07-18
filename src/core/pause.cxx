#include <srl.hpp>
#include "../main.h"
#include "input.h"
#include "assets.h"
#include "backup.h"
#include "screen_transition.h"
#include "../game/gameplay.h"
#include "../game/gameplay_state.hpp"
#include "../objects/player.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;
using namespace Gameplay;

int8_t pauseChoice = 0;

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

static void drawPauseMenuCursor(void);
static void drawPauseMenu(int options_y);
static void checkForPausePress(void);
static void checkForPauseMenu(void);

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
            
            if (g_Players[0].score.continues > 0) {
                SRL::Debug::Print(15, options_y, "Continues:");
                draw_star_element(&star, g_Players[0].score.continues, Fxp(56), Fxp(-72), Fxp(16));
            }
            else {
                SRL::Debug::Print(15, options_y, "Continues:%d", g_Players[0].score.continues);
            }
            
            options_y += 2;
        }
        else {
            options_y = 10; 
            SRL::Debug::Print(19, options_y, "Pawsed");
            options_y += 2;
        }            
        drawPauseMenu(options_y);
        drawPauseMenuCursor();

        displayParticleFx();
    }
}

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
    switch_nbg2_img();
    g_Transition.mosaic_in_rate = MOSAIC_FAST_RATE;
    Pcm::Play(Sounds.Core[StartSnd], PlayMode::Volatile, 6);
}

// check if player 1 paused the game
static void checkForPausePress(void)
{
    // if (g_Game.selectStoryCharacter)
    if (g_GameState.roundState != ROUND_STATE_PLAYING)
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

static void checkForPauseMenu(void)
{
    PPLAYER player = &g_Players[0];

    Digital gamepad(player->input->id);
    
    if (gamepad.WasPressed(Digital::Button::Up))
    {
        Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
        pauseChoice--;
    }

    if (gamepad.WasPressed(Digital::Button::Down))
    {
        Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
        pauseChoice++;
    } 
     
    #if ENABLE_DEBUG_MODE == 1
    if (gamepad.WasPressed(Digital::Button::Left))
    {
        switch(pauseChoice)
        {
            case PAUSE_OPTIONS_DEBUG:
                Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                g_GameOptions.debug_display = !g_GameOptions.debug_display;
                g_Game.vblankClearScreen = true;
                break;
            default:
                break;
        }
    }
    else if (gamepad.WasPressed(Digital::Button::Right))
    {
        switch(pauseChoice)
        {
            case PAUSE_OPTIONS_DEBUG:
                Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                g_GameOptions.debug_display = !g_GameOptions.debug_display;
                g_Game.vblankClearScreen = true;
                break;
            default:
                break;
        }
    }
    #endif
    
    sanitizeValue(&pauseChoice, 0, PAUSE_OPTION_MAX);

    if (gamepad.WasPressed(Digital::Button::START) || gamepad.WasPressed(Digital::Button::A)|| gamepad.WasPressed(Digital::Button::C))
    {
        save_game_backup();
        switch(pauseChoice)
        {
            case PAUSE_OPTIONS_RESUME:
                SRL::Debug::PrintClearScreen();
                Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
                g_Transition.mosaic_in_rate = MOSAIC_FAST_RATE;
                if (g_GameOptions.mosaic_display) {
                    g_Transition.mosaic_in = true;
                }
                g_Game.isPaused = false;
                switch_nbg2_img();
                slColOffsetB(NEUTRAL_FADE, NEUTRAL_FADE, NEUTRAL_FADE);
                break;

            case PAUSE_OPTIONS_RESTART:
                SRL::Debug::PrintClearScreen();
                Pcm::Play(Sounds.Core[NextSnd], PlayMode::Volatile, 6);
                g_Game.isPaused = false;
                switch_nbg2_img();
                slColOffsetB(NEUTRAL_FADE, NEUTRAL_FADE, NEUTRAL_FADE);
                changeState(GAME_STATE_GAMEPLAY);
                break;

            case PAUSE_OPTIONS_QUIT:
                SRL::Debug::PrintClearScreen();
                SRL::VDP2::NBG2::ScrollDisable();
                Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
                transitionState(GAME_STATE_UNINITIALIZED);
                g_Game.isPaused = false;
                break;
            #if ENABLE_DEBUG_MODE == 1
            case PAUSE_OPTIONS_DEBUG:
                SRL::Debug::PrintClearScreen();
                Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
                g_Transition.mosaic_in_rate = MOSAIC_FAST_RATE;
                if (g_GameOptions.mosaic_display) {
                    g_Transition.mosaic_in = true;
                }
                g_Game.isPaused = false;
                switch_nbg2_img();
                slColOffsetB(NEUTRAL_FADE, NEUTRAL_FADE, NEUTRAL_FADE);
                break;
            #endif
            case PAUSE_OPTIONS_ANALOG:
                SRL::Debug::PrintClearScreen();
                Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
                g_Transition.mosaic_in_rate = MOSAIC_FAST_RATE;
                if (g_GameOptions.mosaic_display) {
                    g_Transition.mosaic_in = true;
                }
                g_Game.isPaused = false;
                switch_nbg2_img();
                slColOffsetB(NEUTRAL_FADE, NEUTRAL_FADE, NEUTRAL_FADE);
                break;

            default:
                break;
        }
    }
    else if (gamepad.WasPressed(Digital::Button::B))
    {
        SRL::Debug::PrintClearScreen();
        save_game_backup();
        Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
        g_Game.isPaused = false;
        switch_nbg2_img();
        g_Transition.mosaic_in_rate = MOSAIC_FAST_RATE;
        if (g_GameOptions.mosaic_display) {
        g_Transition.mosaic_in = true;
        }
        slColOffsetB(NEUTRAL_FADE, NEUTRAL_FADE, NEUTRAL_FADE);
    }
}

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
    Fxp offset = SRL::Math::Trigonometry::Sin(g_Game.cursor_angle) * 8;
    cursor.pos.x = Fxp(-124) + offset;
    Fxp choice = Fxp::Convert(pauseChoice);
    cursor.pos.y = Fxp(-32) + (choice * Fxp(32));
    my_sprite_draw(&cursor);
    g_Game.cursor_angle += cursorAngleAdder;
}
