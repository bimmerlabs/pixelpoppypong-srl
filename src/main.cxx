#include "main.h"

#include "core/backup.h"
#include "core/input.h"
#include "core/assets.h"
#include "vdp2/palette.h"
#include "core/screen_transition.h"
#include "game/ppp_logo.h"
#include "game/title_screen.h"
#include "game/gameplay.h"
#include "game/character_select.h"
#include "game/team_select.h"
#include "game/credits.h"
#include "game/highscores.h"
#include "game/name_entry.h"
#include "objects/player.h"
#include "vdp2/font.h"
#include "vdp2/nbg1.h"
#include "vdp2/nbg2.h"
#include "vdp2/sprite_colors.h"
#include "vdp2/ColorHelpers.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;
using namespace SRL::Input;

GAME g_Game = {};

SRL::Math::Random<int32_t> rnd = SRL::Math::Random<int32_t>(1);

int run_once_callback = 1;

GameOptions g_GameOptions = {
    .debug_mode = true,
    .debug_display = false,
    .testCollision = false,
    .mesh_display = false,
    .mosaic_display = true,
    .use_rtc = false,
    .unlockBigHeadMode = false,
    .bigHeadMode = false,
    .enableItems = true,
    .enableMeows = true,
    .reservedBool = false,
    .bombTouchCounter = 0,
    .fishTouchCounter = 0,
    .redShroomTouchCounter = 0,
    .blueShroomTouchCounter = 0,
    .craigTouchCounter = 0,
    .garfTouchCounter = 0,
    .reservedInt = 0,
};

void initGame(void) {
    g_Game.frame = 0, // frame counter
    g_Game.cursor_angle = 0, // for title & pawsed menus
    
    // current game state
    g_Game.gameState = GAME_STATE_UNINITIALIZED;
    g_Game.nextState = GAME_STATE_UNINITIALIZED;
    g_Game.lastState = GAME_STATE_UNINITIALIZED;

    // number of players
    g_Game.minPlayers = 0;
    g_Game.maxPlayers = 0;
    g_Game.numPlayers = ONE_PLAYER;
    g_Game.currentNumPlayers = 0, // this is problematic?
    
    // classic, story, battle
    g_Game.gameMode = 0;

    // easy, medium, hard
    g_Game.gameDifficulty = GAME_DIFFICULTY_MEDIUM;
        
    // TIMERS
    g_Game.endDelayTimer = 0;
    g_Game.BeginTimer = 0;
    g_Game.roundBeginTimer = 0;
    g_Game.dropBallTimer = 0;
    // g_Game.transitionOutTimer = 0;
    g_Game.time_over = false;

    // is the game loading?
    g_Game.isLoading = false;
    g_Game.isSoundLoading = false;

    // is the game is paused?
    g_Game.isPaused = false;

    // did somebody score a goal?
    g_Game.isGoalScored = false;
    g_Game.goalID = -1;

    // is the game finished?
    g_Game.isRoundOver = false;
    g_Game.countofRounds = 0;
   
    g_Game.winner = -2;
    
    // is the game playing?
    g_Game.isActive = false;
    g_Game.isBallActive = false;
    
    g_Game.explodeBall = false;
    
    // misc
    g_Game.selectStoryCharacter = false;
    
    g_Game.vblankClearScreen = false;
}

void loading_screen(void)
{
    if (g_Game.gameState == !GAME_STATE_TRANSITION) {
        return;
    }
    if (g_Game.isLoading) {
        slColOffsetOn(NBG1ON);
        
        SRL::Debug::Print(17, 12, "Loading!");
        
        if (g_Game.isSoundLoading) {
            #if ENABLE_DEBUG_MODE == 1
            if (g_GameOptions.debug_mode) {
                SRL::Debug::Print(15, 14, "SoundFX:%d  ", numberPCMs);
            }
            else {
            #endif
                SRL::Debug::Print(17, 14, "SoundFX..");
            #if ENABLE_DEBUG_MODE == 1
            }
            #endif
            // Generate dot string
            uint16_t sfx_count = numberPCMs + 6; // currently 37+6 = 43
            if (sfx_count >= 44) {
                sfx_count = 43; // Reserve 1 byte for null-terminator
            }
            char dots[44];
            for (int i = 0; i < sfx_count; i++) {
                dots[i] = '.';
            }
            dots[sfx_count] = '\0'; // Null-terminate the string
            // Display dots on screen
            SRL::Debug::Print(0, 15, "%s", dots);            
        }
        else {
            #if ENABLE_DEBUG_MODE == 1
            if (g_GameOptions.debug_mode) {
                SRL::Debug::Print(15, 14, "Sprites:%d  ", SRL::VDP1::GetTextureCount());
            }
            else {
            #endif
                SRL::Debug::Print(17, 14, "Sprites..");
            #if ENABLE_DEBUG_MODE == 1
            }
            #endif
            // loading bar      
            uint16_t sprite_count = SRL::VDP1::GetTextureCount()/3;
            // Clamp sprite count to prevent overflow
            if (sprite_count >= 44) {
                sprite_count = 43; // Reserve 1 byte for null-terminator
            }
            char dots[44];            
            // Generate dot string
            for (int i = 0; i < sprite_count; i++) {
                dots[i] = '.';
            }
            dots[sprite_count] = '\0'; // Null-terminate the string
            
            // Display dots on screen
            SRL::Debug::Print(0, 15, "%s", dots);            
        }
    }
}

static void main_loop(void) {
    g_Game.frame++; // this controls a lot of logic, drawing, & timing..
    if (g_Game.frame > 239)
        g_Game.frame = 0;
    if (g_Game.vblankClearScreen) {
        SRL::Debug::PrintClearScreen();
        g_Game.vblankClearScreen = false;
    }
    #if ENABLE_DEBUG_MODE == 1
    debux_text();
    #endif
    loading_screen();
}

// returns to title screen if player one presses ABC+Start
void abcStart_callback(void)
{
    if (Management::IsConnected(0)) {
        Digital gamepad(0);
        #if ENABLE_DEBUG_MODE == 1
        if (g_GameOptions.debug_mode) {
            // manually switch states
            if (gamepad.WasPressed(Digital::Button::Z) && g_Game.lastState != GAME_STATE_PPP_LOGO) {
                g_Game.nextState = (GAME_STATE)(g_Game.gameState + 1);
                if (g_Game.nextState == GAME_STATE_TRANSITION) {
                    g_Game.nextState = GAME_STATE_UNINITIALIZED;
                }
                transitionState(g_Game.nextState);
            }
        }
        #endif
        if(g_Game.gameState == GAME_STATE_UNINITIALIZED || g_Game.gameState == GAME_STATE_TRANSITION)
        {        
            return;
        }
        if ((gamepad.WasPressed(Digital::Button::START) || gamepad.WasPressed(Digital::Button::X)) // X for retrobit controller testing only
            && gamepad.IsHeld(Digital::Button::A)  
            && gamepad.IsHeld(Digital::Button::B) 
            && gamepad.IsHeld(Digital::Button::C)) {
            if(g_Game.gameState == GAME_STATE_PPP_LOGO)
            {
                SYS_Exit(0);
            }
            else {
                transitionState(GAME_STATE_UNINITIALIZED);
            }
        }
    }
}

void my_input_callback(void) {
    abcStart_callback();
    switch (g_Game.gameState) {
        case GAME_STATE_PPP_LOGO:
            pppLogo_input();
            break;
        case GAME_STATE_TITLE_SCREEN:
            titleScreen_input();
            break;
        case GAME_STATE_DEMO_LOOP:
            demo_input();
            break;
        case GAME_STATE_CREDITS:
            credits_input();
            break;
        case GAME_STATE_HIGHSCORES:
            score_input();
            break;
        case GAME_STATE_TITLE_MENU:
            menuScreen_input();
            break;
        case GAME_STATE_TITLE_OPTIONS:
            optionsScreen_input();
            break;
        case GAME_STATE_TEAM_SELECT:
            teamSelect_input();
            characterSelect_input();
            break;
        case GAME_STATE_CHARACTER_SELECT:
            characterSelectInput();
            break;
        case GAME_STATE_GAMEPLAY:
            gameplay_input();
            pause_input();
            break;
        case GAME_STATE_NAME_ENTRY:
            nameEntryInput();
            break;
        default:
            break;
    }
}

// cycle through HSL colors
void my_color_calc(void)
{
    switch (g_Game.gameState) {
        case GAME_STATE_PPP_LOGO: {
            if (do_update_ppplogo) {
                update_ppplogo_color();
                do_update_ppplogo = false;
                update_palette_ppplogo = true;
            }
            break;
        }
        case GAME_STATE_TITLE_SCREEN: {
            if (do_update_logo1) {
                update_palette_logo1 = update_sprites_color(&p_rangeLogo, HSL_LOGO);
                do_update_logo1 = false;
            }
            break;
        }
        case GAME_STATE_TITLE_MENU: {
            updateTitleMenuColors();
            break;
        }
        case GAME_STATE_TEAM_SELECT: {
            updateTeamSelectColors();
            break;
        }
        case GAME_STATE_CHARACTER_SELECT: {
            if (do_update_ppplogo) {
                update_ppplogo_color();
                do_update_ppplogo = false;
                update_palette_ppplogo = true;
            }
            break;
        }
        case GAME_STATE_DEMO_LOOP: {
            updateGameColors();
            break;
        }
        case GAME_STATE_GAMEPLAY: {
            updateGameColors();
            break;
        }
        case GAME_STATE_NAME_ENTRY: {
            updateNameEntryColors();
            break;
        }
        default:
        {
            return;
        }
    }
}
void my_palette_update(void)
{
    switch (g_Game.gameState) {
        case GAME_STATE_PPP_LOGO: {
            if (update_palette_ppplogo) {
                update_ppplogo_palette();
                update_palette_ppplogo = false;
            }
            break;
        }
        case GAME_STATE_TITLE_SCREEN: {
            if (update_palette_logo1) {
                update_palette_logo1 = update_sprites_palette(&p_rangeLogo);
            }
            break;
        }
        case GAME_STATE_TITLE_MENU: {
            updateTitleMenuPalette();
            break;
        }
        case GAME_STATE_TEAM_SELECT: {
            updateTeamSelectPalette();
            break;
        }
        case GAME_STATE_CHARACTER_SELECT: {
            if (update_palette_ppplogo) {
                update_ppplogo_palette();
                update_palette_ppplogo = false;
            }
            break;
        }
        case GAME_STATE_DEMO_LOOP: {
            updateGamePalette();
            break;
        }
        case GAME_STATE_GAMEPLAY: {
            updateGamePalette();
            break;
        }
        case GAME_STATE_NAME_ENTRY: {
            updateNameEntryPalette();
            break;
        }
        default:
        {
            return;
        }
    }
}

void run_once(void) {
    rnd = SRL::Math::Random<int32_t>(15);
    // load_game_backup();
    init_font();
    basePalette = init_game_palette();
    init_sprites_img(); // rename
    init_nbg1_img();
    preload_options_bg();

    // update based on time of day
    DateTime time = DateTime::Now();
    if (time.Month() == OCTOBER)
    {
        g_Game.timeSeason = S_HALLOWEEN;
    }
    
    changeState(GAME_STATE_UNINITIALIZED);
    run_once_callback = 0;
}

int main()
{
    SRL::Core::Initialize(HighColor(0,0,0));
    
    slZdspLevel(10);
    
    // pone-sound
    load_drv(ADX_MASTER_2304);
    SRL::Core::OnVblank += sdrv_vblank_rq;

    SRL::TV::TVOff();
    
    #ifdef SRL_HIGH_RES_NON_INTERLACED
        slSetSprTVMode(RESOLUTION_HIGH);
    #endif
    // CRAM mode 0 - required for VDP2 transparency in high-res
    slColRAMMode ( CRM16_1024 ); // must be set before loading any palettes
    
    initUnlockedCharacters();
    init_inputs();
    // highScore_init();
    
    SRL::Core::OnVblank += main_loop;
    SRL::Core::OnVblank += my_palette_update;
    
    while(run_once_callback)
    {
        run_once();
    }
    while(1)
    {
        screenTransition_update();
        game_state_update();
        my_input_callback();
        
        switch (g_Game.gameState)
        {
            case GAME_STATE_PPP_LOGO:
                pppLogo_update();
                break;
            case GAME_STATE_TITLE_SCREEN:
                startScreen_update();
                titleScreen_update();            
                break;
            case GAME_STATE_TITLE_MENU:
                titleScreen_update();  
                break;
            case GAME_STATE_TITLE_OPTIONS:
                optionsScreen_update();
                break;
            case GAME_STATE_GAMEPLAY:
                gameplay_update();
                break;
            case GAME_STATE_DEMO_LOOP:
                demo_update();
                break;
            case GAME_STATE_CHARACTER_SELECT:
                characterSelectUpdate();
                break;
            case GAME_STATE_TEAM_SELECT:
                teamSelect_update();
                break;
            case GAME_STATE_NAME_ENTRY:
                nameEntryUpdate();
                break;
            case GAME_STATE_CREDITS:
                display_credits();
                break;
            case GAME_STATE_HIGHSCORES:
                display_scores();
                break;
            default:
                break;
        }
    
        my_color_calc();
    
        SRL::Core::Synchronize();
    }
    return(0);
}