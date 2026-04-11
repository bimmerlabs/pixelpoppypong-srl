#include <srl.hpp>
#include "../main.h"
#include "title_screen.h"
#include "player_setup.h"
#include "../core/screen_transition.h"
// #include "../core/backup.h"
#include "../core/input.h"
#include "../core/assets.h"

#include "../vdp2/nbg1.h"
#include "../vdp2/nbg2.h"
#include "../vdp2/sprite_colors.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;
using namespace SRL::Input;

using Trig = SRL::Math::Trigonometry;

// // Sphere setup
// static const int16_t LatitudePoints = 17;
// static const int16_t Latitudes = 1;
// static const Fxp LogoRadius = 100.0;
// // Prepare sphere points, we do this before main loop, for faster performance while rendering
// static const Angle latStep = Angle::FromDegrees(360.0 / LatitudePoints);
// static const Angle longStep = Angle::FromDegrees(180.0 / (Latitudes + 1));
// static const size_t pointCount = Latitudes * LatitudePoints;
// static Vector3D points[pointCount] {};
// // Setup starting rotation
// Angle rot = 0.0;
// Angle roll = 0.0;

HighColor white = HighColor::Colors::White;
HighColor yellow = HighColor::Colors::Yellow;

// globals for menu options
TITLESCREEN titleScreen = {};

void initTitleScreenStruct(void) {
    titleScreen.timer = 0;
    titleScreen.menuChoice = TITLE_OPTION_GAME_MODE;
    titleScreen.menuLastChoice = TITLE_OPTION_GAME_MODE;
    titleScreen.optionChoice = 0;
    titleScreen.logo1_pos = -400;
    titleScreen.logo2_pos = 400;
    titleScreen.logo_velocity = 0;
    titleScreen.logo_falling = true;
    titleScreen.logo_bounce = false;
    titleScreen.increasing = true;
    titleScreen.h_value = 0;
    
    titleScreen.draw_start_text = true;
    titleScreen.draw_option_mode  = true;
    titleScreen.draw_option_players  = false;
    titleScreen.draw_option_difficulty  = false;
    titleScreen.draw_option_start  = false;
    titleScreen.draw_option_options  = true;
    titleScreen.poppy_animation = false;
    titleScreen.poppy_animation_frame = 0;
    titleScreen.poppy_animation_id = 0;
    titleScreen.poppy_scale = 0.1;
    titleScreen.poppy_velocity = 0.0;
    
    titleScreen.left_arrow_id = 0;
    titleScreen.right_arrow_id = 2;
    
    // rot = 0.0;
    // roll = 0.0;
}

//
// TITLE SCREEN
//

void titleScreen_init(void)
{
    // if (g_Game.lastState == GAME_STATE_TEAM_SELECT 
     // || g_Game.lastState == GAME_STATE_GAMEPLAY 
     // || g_Game.lastState == GAME_STATE_DEMO_LOOP 
     // || g_Game.lastState == GAME_STATE_CREDITS) {
        // // unloadGameAssets();
        // // loadTitleScreenAssets();
    // }    
    if (!g_Assets.titleAssetsLoaded) {
        loadTitleScreenAssets();
    }
    
    if (g_Game.lastState != GAME_STATE_PPP_LOGO) {
        reset_sprites();
    }

    g_Game.lastState = GAME_STATE_TITLE_SCREEN;    
    initTitleScreenStruct();
    
    // IDEA: different colors for christmas (red/white?), easter (pastel), 4th of july (red/white blue)
    // hsl_incSprites[HSL_LOGO].s = -127; // easter?
    // // hsl_incSprites[HSL_LOGO].l = -63; // halloween
    // do_update_logo1 = true;
    
    hslSprites[28].h = 60;
    hslSprites[31].h = 60;
    do_update_menu3 = true;
    do_update_menu4 = true;
    
    // set_spr_position(&logo1, 0, titleScreen.logo1_pos, 97);
    // set_spr_position(&logo2, 0, titleScreen.logo2_pos, 97);
    logo1.visible = true;
    logo2.visible = true;
    
    set_spr_scale(&pixel_poppy, titleScreen.poppy_scale, titleScreen.poppy_scale);
    pixel_poppy.rot.z = 0;
    set_spr_position(&pixel_poppy, 0, 0, 100);
    sprite_frame_reset(&pixel_poppy);
    titleScreen.poppy_animation_frame = 0;
    titleScreen.poppy_animation_id = 0;
    
    slColOffsetOn(NBG0ON | NBG1ON | SPRON);
    slColOffsetAUse(NBG0ON);
    slColOffsetBUse(NBG1ON | SPRON);
    
    // INITIAL GAME MODE
    g_Game.gameMode = GAME_MODE_STORY;
    g_Game.minPlayers = ONE_PLAYER;
    g_Game.maxPlayers = ONE_PLAYER;
    g_Game.currentNumPlayers = 0;
    g_Game.numPlayers = ONE_PLAYER;    
    g_Team.minTeams = 0;
    g_Team.maxTeams = 0;
    g_Team.numTeams = 0;    
    g_Game.gameDifficulty = GAME_DIFFICULTY_MEDIUM;
    
    g_Transition.mosaic_in = true;
    g_Transition.music_in = true;
    g_Transition.fade_in = true;
    g_Transition.all_in = true;
    
    SRL::VDP2::NBG2::ScrollDisable();
    
    // logoSphere_init();
    
    // enable Endcodes
    SRL::Scene2D::SetEffect(SRL::Scene2D::SpriteEffect::EnableECD, true);
}
    
// void logoSphere_init(void) {
    // for (int16_t longitude = 0; longitude < Latitudes; longitude++)
    // {
        // const Angle longRot = (longStep * (longitude + 1));

        // for (int16_t latitude = 0; latitude < LatitudePoints; latitude++)
        // {
            // const Angle latRoll = (latStep * latitude);

            // points[(longitude * Latitudes) + latitude] = Vector3D(
                // Trig::Sin(longRot) * Trig::Cos(latRoll),
                // Trig::Sin(longRot) * Trig::Sin(latRoll),
                // Trig::Cos(longRot)
            // );
        // }
    // }

    // // // Setup starting rotation
    // // Angle rot = 0.0;
    // // Angle roll = 0.0;
// }

static int pos_x_start1 = -286;
static int pos_x_start2 = -96;
static int pos_x1 = pos_x_start1;
static int pos_x2 = pos_x_start2;
static int pos_space = 2;
static int pos_gap = 63;

// only player one can control the title screen
void titleScreen_input(void)
{
    if (titleScreen.logo_bounce || titleScreen.logo_falling)
    {
        return;
    }
    
    PPLAYER player = &g_Players[0];    
    
    if (!player->input->isSelected)
    {
        check_ui_inputs();
    }
 
    Digital gamepad(player->input->id);
    
    if (gamepad.WasPressed(Digital::Button::START))
    {
        Pcm::Play(Sounds.Core[StartSnd], PlayMode::Volatile, 6);
        changeState(GAME_STATE_TITLE_MENU); 
        if (g_GameOptions.mosaic_display)
        {
            g_Transition.mosaic_out = true;
            g_Transition.all_out = true;
        }
    }
    
    if (gamepad.WasPressed(Digital::Button::R))
    {
        titleScreen.timer = TITLE_TIMER;
    }
    
    // if (gamepad.WasPressed(Digital::Button::Up))
    // {
        // pos_space++;
    // }
    // else if (gamepad.WasPressed(Digital::Button::Down))
    // {
        // pos_space--;
    // }
    // else if (gamepad.WasPressed(Digital::Button::Left))
    // {
        // pos_gap--;
    // }
    // else if (gamepad.WasPressed(Digital::Button::Right))
    // {
        // pos_gap++;
    // }
    
    // if (gamepad.WasPressed(Digital::Button::A))
    // {
        // pos_x_start1++;
    // }
    // else if (gamepad.WasPressed(Digital::Button::B))
    // {
        // pos_x_start1--;
    // }
    // else if (gamepad.WasPressed(Digital::Button::X))
    // {
        // pos_x_start2++;
    // }
    // else if (gamepad.WasPressed(Digital::Button::Y))
    // {
        // pos_x_start2--;
    // }

    // SRL::Debug::Print(2, 10, "pos_x_start1:%3d ", pos_x_start1);
    // SRL::Debug::Print(2, 11, "pos_x_start2:%3d ", pos_x_start2);
    // SRL::Debug::Print(2, 12, "pos_space:%3d ", pos_space);
    // SRL::Debug::Print(2, 13, "pos_gap:%3d ", pos_gap);
}

void startScreen_update(void)
{
    titleScreen.timer++;
    
    titleScreen.poppy_animation_id = rnd.GetNumber(0, 11);
    
    if (!titleScreen.logo_bounce && !titleScreen.logo_falling) {
        if (titleScreen.timer == LOGO_TIMER) {
            reset_sprites();
                
            // hsl_incSprites[HSL_LOGO].s = -127; // easter?
            // // hsl_incSprites[HSL_LOGO].l = -63; // halloween
            // do_update_logo1 = true;
            
            titleScreen.h_value = 0;
            do_update_logo1 = true;
        }
        else if (titleScreen.timer >= LOGO_TIMER2 && titleScreen.timer < LOGO_TIMER) {
            hsl_incSprites[HSL_LOGO].h -= 8;
            do_update_logo1 = true;
        }
        else if (g_Game.frame % 5 == 0 && titleScreen.timer < LOGO_TIMER) { // modulus
            hsl_incSprites[HSL_LOGO].h -= 20;
            do_update_logo1 = true;
        }
        pixel_poppy.id = pixel_poppy.anim[0].asset + 1;
    }
    // start the demo loop / attract screen mode
    if(titleScreen.timer > TITLE_TIMER)
    {
        transitionState(static_cast<GAME_STATE>(g_AttractScreen.state[g_AttractScreen.id])); // super ugly but it works?
        attract_screen_state();
        titleScreen.timer = 0;
    }
}

void titleScreen_update(void)
{
    if (attrNbg1.x_scroll > Fxp(0)) {
        attrNbg1.x_pos += attrNbg1.x_scroll;
        if (attrNbg1.x_pos > Fxp(512.0))
            attrNbg1.x_pos = Fxp(0);
    }
    slScrPosNbg1(attrNbg1.x_pos.RawValue(), attrNbg1.y_pos.RawValue());
    
    drawMenu();
    drawMenuCursor();
    drawTitle();
}

// draws title image + version number
void drawTitle(void)
{
        // experimental / future
        // // Create rotation matrix that will rotate the sphere
        // const Matrix33 matrix = Matrix33::CreateRotation(rot, 0.0, roll);
        
        // size_t characterIDx = 13;
        // // Rotate each sphere point and render sprite at its location
        // for (size_t pointIdx = 0; pointIdx < pointCount; pointIdx++)
        // {
            // if (pointIdx == 4 || pointIdx == 10 || pointIdx == 16) {
                // continue;
            // }
            
            // // Rotate point by matrix
            // const Vector3D transformed = matrix * points[pointIdx];

            // // Calculate sprite size
            // const Fxp depth = (transformed.Z + 2) >> 2;

            // // Render sphere point as a simple sprite
            // logo1.id = logo1.anim[0].asset + characterIDx;
            // SRL::Scene2D::DrawSprite(
                // logo1.id, 
                // Vector3D(
                    // (LogoRadius * transformed.X),
                    // (LogoRadius * transformed.Y),
                    // (LogoRadius * -transformed.Z) + 100),
                // Vector2D(
                    // depth,
                    // depth)
                // );
            // characterIDx--;
            
            // // SRL::Scene2D::DrawSprite(
                // // pixel_poppy.id, 
                // // Vector3D(
                    // // 0,
                    // // 0,
                    // // 100),
                // // Vector2D(
                    // // 6,
                    // // 6)
                // // );
        // }

        // // Rotate the sphere a little
        // rot += 0.001;
        // roll += 0.005;
    
    my_sprite_draw(&pixel_poppy);
        
    pos_x1 = pos_x_start1;
    logo1.zmode = _ZmCT;
    for (uint8_t i = 0; i < 5; i++) {     
        logo1.id = logo1.anim[0].asset + i;
        set_spr_position(&logo1, pos_x1, titleScreen.logo1_pos, 97);
        pos_x1 += pos_gap;
        my_sprite_draw(&logo1);
    }
    pos_x1 += pos_space;
    for (uint8_t i = 5; i < 10; i++) {     
        logo1.id = logo1.anim[0].asset + i;
        set_spr_position(&logo1, pos_x1, titleScreen.logo1_pos, 97);
        pos_x1 += pos_gap;
        my_sprite_draw(&logo1);
    }    
    pos_x2 = pos_x_start2;
    logo1.zmode = _ZmCB;
    for (uint8_t i = 10; i <= 13; i++) {     
        logo1.id = logo1.anim[0].asset + i;
        set_spr_position(&logo1, pos_x2, titleScreen.logo2_pos, 97);
        pos_x2 += pos_gap;
        my_sprite_draw(&logo1);
    }
        
    if(g_Game.gameState != GAME_STATE_TITLE_SCREEN)
    {
        return;
    }
    
    // title graphic
    if (titleScreen.poppy_scale < POPPY_MAX_SCALE) {
        if (titleScreen.poppy_velocity < 0.5) {
            titleScreen.poppy_velocity += 0.01;
        }
        titleScreen.poppy_scale += titleScreen.poppy_velocity;
        set_spr_scale(&pixel_poppy, titleScreen.poppy_scale, titleScreen.poppy_scale);
    }

    // LOGO ANIMATION
    // logo is falling
    if (titleScreen.logo_falling && !titleScreen.logo_bounce) {
        if (titleScreen.logo_velocity < LOGO_VELOCITY) {
            if (g_Game.frame % 2 == 0) { // modulus POW2
                titleScreen.logo_velocity++;
            }
        }
        if (titleScreen.logo1_pos < LOGO1_ONSCREEN_Y) {
            titleScreen.logo1_pos += titleScreen.logo_velocity;
            set_spr_position(&logo1, 0, titleScreen.logo1_pos, 97);
            titleScreen.logo2_pos -= titleScreen.logo_velocity;
            set_spr_position(&logo2, 0, titleScreen.logo2_pos, 97);
        }
        // logo has hit the "ground"
        else {
            titleScreen.logo_velocity = 0;
            titleScreen.logo_falling = false;
            titleScreen.logo_bounce = true;
        }
    }
    // logo is bouncing
    else if (titleScreen.logo_bounce && !titleScreen.logo_falling) {
        // bounce
        if (titleScreen.logo_velocity < LOGO_VELOCITY) {
            if (g_Game.frame % 2 == 0) { // modulus POW2
                titleScreen.logo_velocity++;
            }
        }
        if (titleScreen.logo1_pos > LOGO1_ONSCREEN_Y - 12) {
            titleScreen.logo1_pos -= titleScreen.logo_velocity;
            set_spr_position(&logo1, 0, titleScreen.logo1_pos, 97);
            titleScreen.logo2_pos += titleScreen.logo_velocity;
            set_spr_position(&logo2, 0, titleScreen.logo2_pos, 97);
        }
        // logo has hit it's resing spot
        else {
            titleScreen.logo_velocity = 0;
            titleScreen.logo_falling = true;
            titleScreen.logo_bounce = true;
        }
    }
    // first bounce has already happened
    else if (titleScreen.logo_bounce && titleScreen.logo_falling) {
        titleScreen.logo_falling = false;
        titleScreen.logo_bounce = false;
    }
    // falling again
    else if (!titleScreen.logo_bounce && !titleScreen.logo_falling) {
        if (titleScreen.logo_velocity < LOGO_VELOCITY) {
            titleScreen.logo_velocity++;
        }
        // final resting place
        if (titleScreen.logo1_pos < LOGO1_ONSCREEN_Y) {
            titleScreen.logo1_pos += titleScreen.logo_velocity;
            set_spr_position(&logo1, 0, titleScreen.logo1_pos, 97);
            titleScreen.logo2_pos -= titleScreen.logo_velocity;
            set_spr_position(&logo2, 0, titleScreen.logo2_pos, 97);
        }
        else {
            if (g_Game.frame % 10 == 0) { // modulus
                titleScreen.draw_start_text = !titleScreen.draw_start_text;
            }
            if (titleScreen.draw_start_text) {
                SRL::Debug::Print(16, 27, "PRESS START");
            }
            else {
                SRL::Debug::Print(16, 27, "           ");
            }
            #if ENABLE_DEBUG_MODE == 1
                SRL::Debug::Print(18, 28, "%s", VERSION); // Regular version
            #else
                SRL::Debug::Print(18, 28, "%s RC", VERSION); // release canidate
            #endif
        }
    }
}

//
// MAIN MENU
//

void titleMenu_init(void)
{
    
    g_Game.lastState = GAME_STATE_TITLE_MENU;
    if (g_GameOptions.mesh_display) {
        menu_bg1.mesh = MESHon;
    }
    else {
        menu_bg1.mesh = MESHoff;
    }
    menu_bg1.id = menu_bg1.anim[0].asset + 5;
    set_spr_position(&menu_bg1, 0, MENU_Y+5, 95);
    set_spr_scale(&menu_bg1, 0.0, 0.0);

    titleScreen.h_value = 0;
    
    g_Transition.music_in = true;
    if (!g_Transition.all_out) {
        g_Transition.fade_in = true;
        g_Transition.all_in = true;
    }
    titleScreen.poppy_animation = false;
}

void menuScreen_input(void)
{
    PPLAYER player = &g_Players[0];

    Digital gamepad(player->input->id);
    
        if (gamepad.WasPressed(Digital::Button::Up))
        {
            Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
            titleScreen.h_value = 0;
            // hack - don't know why these are off by 240 degrees?  maybe fixed/RGB rounding error?
            hslSprites[28].h = 60;
            hslSprites[31].h = 60;
            reset_sprites();
            do_update_menu3 = true;
            do_update_menu4 = true;
            switch (titleScreen.menuChoice) {
                case TITLE_OPTION_GAME_MODE:
                    titleScreen.menuLastChoice = TITLE_OPTION_GAME_MODE;
                    titleScreen.menuChoice = TITLE_OPTION_GAME_OPTIONS;
                    break;

                case TITLE_OPTION_GAME_PLAYERS:
                    titleScreen.menuLastChoice = TITLE_OPTION_GAME_PLAYERS;
                    titleScreen.menuChoice = TITLE_OPTION_GAME_OPTIONS;
                    break;
                
                case TITLE_OPTION_GAME_DIFFICULTY:
                    titleScreen.menuLastChoice = TITLE_OPTION_GAME_DIFFICULTY;
                    titleScreen.menuChoice = TITLE_OPTION_GAME_OPTIONS;
                    break;
                    
                case TITLE_OPTION_GAME_START:
                    titleScreen.menuLastChoice = TITLE_OPTION_GAME_START;
                    titleScreen.menuChoice = TITLE_OPTION_GAME_OPTIONS;
                    break;
                    
                case TITLE_OPTION_GAME_OPTIONS:
                    titleScreen.menuChoice = titleScreen.menuLastChoice;
                    break;
            }
        }

        if (gamepad.WasPressed(Digital::Button::Down))
        {
            Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
            titleScreen.h_value = 0;
            // hack - don't know why these are off by 240 degrees?  maybe fixed/RGB rounding error?
            hslSprites[28].h = 60;
            hslSprites[31].h = 60;
            reset_sprites();
            do_update_menu3 = true;
            do_update_menu4 = true;
            switch (titleScreen.menuChoice) {
                case TITLE_OPTION_GAME_MODE:
                    titleScreen.menuLastChoice = TITLE_OPTION_GAME_MODE;
                    titleScreen.menuChoice = TITLE_OPTION_GAME_OPTIONS;
                    break;

                case TITLE_OPTION_GAME_PLAYERS:
                    titleScreen.menuLastChoice = TITLE_OPTION_GAME_PLAYERS;
                    titleScreen.menuChoice = TITLE_OPTION_GAME_OPTIONS;
                    break;
                
                case TITLE_OPTION_GAME_DIFFICULTY:
                    titleScreen.menuLastChoice = TITLE_OPTION_GAME_PLAYERS;
                    titleScreen.menuChoice = TITLE_OPTION_GAME_OPTIONS;
                    break;
                    
                case TITLE_OPTION_GAME_START:
                    titleScreen.menuLastChoice = TITLE_OPTION_GAME_START;
                    titleScreen.menuChoice = TITLE_OPTION_GAME_OPTIONS;
                    break;
                    
                case TITLE_OPTION_GAME_OPTIONS:
                    titleScreen.menuChoice = titleScreen.menuLastChoice;
                    break;
            }
        }

        if (gamepad.WasPressed(Digital::Button::Left))
        {
            switch(titleScreen.menuChoice)
            {
                case TITLE_OPTION_GAME_MODE:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_Game.gameMode--;
                    sanitizeValue(&g_Game.gameMode, 0, GAME_MODE_MAX);
                    selectGameMode();
                    break;

                case TITLE_OPTION_GAME_PLAYERS:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_Game.numPlayers--;
                    sanitizeValue(&g_Game.numPlayers, g_Game.minPlayers, (g_Game.maxPlayers+1));
                    selectNumPlayers();
                    break;

                case TITLE_OPTION_GAME_DIFFICULTY:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_Game.gameDifficulty--;
                    sanitizeValue(&g_Game.gameDifficulty, 0, GAME_DIFFICULTY_MAX);
                    break;

                default:
                    break;
            }
        }
        if (titleScreen.menuChoice != TITLE_OPTION_GAME_OPTIONS) {
            if (gamepad.IsHeld(Digital::Button::Left))
            {
                titleScreen.left_arrow_id = LEFT_ARROW_DN;
            }
            else {
                titleScreen.left_arrow_id = LEFT_ARROW_UP;
            }
        }

        if (gamepad.WasPressed(Digital::Button::Right))
        {
            switch(titleScreen.menuChoice)
                {
                case TITLE_OPTION_GAME_MODE:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_Game.gameMode++;
                    sanitizeValue(&g_Game.gameMode, 0, GAME_MODE_MAX);
                    selectGameMode();
                    break;

                case TITLE_OPTION_GAME_PLAYERS:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_Game.numPlayers++;
                    sanitizeValue(&g_Game.numPlayers, g_Game.minPlayers, (g_Game.maxPlayers+1));
                    selectNumPlayers();
                    break;
                
                case TITLE_OPTION_GAME_DIFFICULTY:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_Game.gameDifficulty++;
                    sanitizeValue(&g_Game.gameDifficulty, 0, GAME_DIFFICULTY_MAX);
                    break;
                
                default:
                    break;
            }
        }
        if (titleScreen.menuChoice != TITLE_OPTION_GAME_OPTIONS) {
            if (gamepad.IsHeld(Digital::Button::Right))
            {
                titleScreen.right_arrow_id = RIGHT_ARROW_DN;
            }
            else {
                titleScreen.right_arrow_id = RIGHT_ARROW_UP;
            }
        }

        // keep title screen choice in range
        sanitizeValue(&titleScreen.menuChoice, 0, TITLE_OPTION_MAX);

        // select an option here
        if (gamepad.WasPressed(Digital::Button::START) || 
            gamepad.WasPressed(Digital::Button::A) ||
            gamepad.WasPressed(Digital::Button::C))
        {
            switch(titleScreen.menuChoice)
            {
                case TITLE_OPTION_GAME_MODE:
                    Pcm::Play(Sounds.Core[NextSnd], PlayMode::Volatile, 6);
                    titleScreen.menuLastChoice = titleScreen.menuChoice;
                    titleScreen.menuChoice++;
                    break;

                case TITLE_OPTION_GAME_PLAYERS:
                    Pcm::Play(Sounds.Core[NextSnd], PlayMode::Volatile, 6);
                    titleScreen.menuLastChoice = titleScreen.menuChoice;
                    titleScreen.menuChoice++;
                    break;
                
                case TITLE_OPTION_GAME_DIFFICULTY:
                    Pcm::Play(Sounds.Core[NextSnd], PlayMode::Volatile, 6);
                    titleScreen.menuLastChoice = titleScreen.menuChoice;
                    titleScreen.menuChoice++;
                    break;
                    
                case TITLE_OPTION_GAME_START: {
                    Pcm::Play(Sounds.Core[NextSnd], PlayMode::Volatile, 6);
                    if (g_Game.gameMode == GAME_MODE_STORY) {
                        transitionState(GAME_STATE_CHARACTER_SELECT);
                    }
                    else {
                        transitionState(GAME_STATE_TEAM_SELECT);
                    }
                    break;
                }
                    
                case TITLE_OPTION_GAME_OPTIONS:
                    Pcm::Play(Sounds.Core[NextSnd], PlayMode::Volatile, 6);
                    g_Game.nextState = GAME_STATE_TITLE_OPTIONS;
                    changeState(g_Game.nextState);
                    break;
                    
                default:
                    break;
            }
        }
        if (gamepad.WasPressed(Digital::Button::B))
        {
            switch(titleScreen.menuChoice)
            {
                case TITLE_OPTION_GAME_MODE:
                    changeState(GAME_STATE_TITLE_SCREEN);
                    if (g_GameOptions.mosaic_display) {
                        g_Transition.mosaic_in = true;
                    }
                    g_Transition.fade_in = false;
                    g_Transition.all_in = true;
                    break;

                case TITLE_OPTION_GAME_PLAYERS:
                    Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
                    titleScreen.menuChoice--;
                    break;
                
                case TITLE_OPTION_GAME_DIFFICULTY:
                    Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
                    titleScreen.menuChoice--;
                    break;
                    
                case TITLE_OPTION_GAME_START:                  
                    Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
                    titleScreen.menuChoice--;
                    break;
                    
                case TITLE_OPTION_GAME_OPTIONS:
                    Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
                    titleScreen.h_value = 0;
                    gamePalette.GetData()[28] = white;
                    titleScreen.menuChoice = titleScreen.menuLastChoice;
                    break;
                    
                default:
                    break;
            }
        }
}

void drawMenu(void)
{
    if(g_Game.gameState != GAME_STATE_TITLE_MENU)
    {
        return;
    }

    // GASP
    if (titleScreen.poppy_animation_id == 1 || titleScreen.poppy_animation_id == 2) 
    {
        // PLAY SOUND EFFECT
        titleScreen.poppy_animation = true;
        titleScreen.poppy_animation_frame += 1;
        if (titleScreen.poppy_animation && titleScreen.poppy_animation_frame % 20 == 0) // modulus
        {
            // PLAY SOUND EFFECT
            pixel_poppy.id = pixel_poppy.anim[0].asset;
            titleScreen.poppy_animation = false;
            titleScreen.poppy_animation_frame = 0;
            titleScreen.poppy_animation_id = 0;
        }
    }
    
    // wink
    else if (titleScreen.poppy_animation_id == 3 || titleScreen.poppy_animation_id == 4 || titleScreen.poppy_animation_id == 5) 
    {
        // PLAY SOUND EFFECT
        titleScreen.poppy_animation = true;
        titleScreen.poppy_animation_frame += 1;
        pixel_poppy.id = pixel_poppy.anim[0].asset + 2;
        if (titleScreen.poppy_animation && titleScreen.poppy_animation_frame % 22 == 0) // modulus
        {
            pixel_poppy.id = pixel_poppy.anim[0].asset + 1;
            titleScreen.poppy_animation = false;
            titleScreen.poppy_animation_frame = 0;
            titleScreen.poppy_animation_id = 0;
        }
    }
    // giggle
    else if (titleScreen.poppy_animation_id == 6 || titleScreen.poppy_animation_id == 7 || titleScreen.poppy_animation_id == 8) 
    {
        // PLAY SOUND EFFECT
        bool giggle = true;
        titleScreen.poppy_animation = true;
        titleScreen.poppy_animation_frame += 1;
        pixel_poppy.id = pixel_poppy.anim[0].asset + 3;
        if (titleScreen.poppy_animation && titleScreen.poppy_animation_frame % 40 == 0) // modulus
        {
            pixel_poppy.id = pixel_poppy.anim[0].asset + 4;
            set_spr_position(&pixel_poppy, 0, 0, 100);
            titleScreen.poppy_animation = false;
            titleScreen.poppy_animation_frame = 0;
            titleScreen.poppy_animation_id = 0;
        }
        if (giggle && titleScreen.poppy_animation_frame % 10 == 0) { // modulus
            set_spr_position(&pixel_poppy, 0, 2, 100);
            giggle = false;
        }
        else if (titleScreen.poppy_animation_frame % 5 == 0) { // modulus
            set_spr_position(&pixel_poppy, 0, -2, 100);
            giggle = true;
        }
    }
    // eyeroll
    else if (titleScreen.poppy_animation_id == 9) 
    {
        // PLAY SOUND EFFECT
        titleScreen.poppy_animation = true;
        titleScreen.poppy_animation_frame += 1;
        if (titleScreen.poppy_animation && titleScreen.poppy_animation_frame % 10 == 0) // modulus
        {
            pixel_poppy.id = pixel_poppy.anim[0].asset + 6;
            titleScreen.poppy_animation = false;
            titleScreen.poppy_animation_frame = 0;
            titleScreen.poppy_animation_id = 0;
        }
    }    
    // sad
    else if (titleScreen.poppy_animation_id == 10) 
    {
        // PLAY SOUND EFFECT
        titleScreen.poppy_animation = true;
        titleScreen.poppy_animation_frame += 1;
        if (titleScreen.poppy_animation && titleScreen.poppy_animation_frame % 10 == 0) // modulus
        {
            pixel_poppy.id = pixel_poppy.anim[0].asset + 5;
            titleScreen.poppy_animation = false;
            titleScreen.poppy_animation_frame = 0;
            titleScreen.poppy_animation_id = 0;
        }
    }    
    // smile
    else if (titleScreen.poppy_animation_id == 11) 
    {
        // PLAY SOUND EFFECT
        titleScreen.poppy_animation = true;
        titleScreen.poppy_animation_frame += 1;
        if (titleScreen.poppy_animation && titleScreen.poppy_animation_frame % 10 == 0) // modulus
        {
            pixel_poppy.id = pixel_poppy.anim[0].asset + 4;
            titleScreen.poppy_animation = false;
            titleScreen.poppy_animation_frame = 0;
            titleScreen.poppy_animation_id = 0;
        }
    }
    
    // make sure poppy continues to scale up if user presses start too fast
    if (titleScreen.poppy_scale < POPPY_MAX_SCALE) {
        if (titleScreen.poppy_velocity < 0.5) {
            titleScreen.poppy_velocity += 0.01;
        }
        titleScreen.poppy_scale += titleScreen.poppy_velocity;
        set_spr_scale(&pixel_poppy, titleScreen.poppy_scale, titleScreen.poppy_scale);
    }
    
    // Animate logo1 upwards
    if (titleScreen.logo1_pos > LOGO1_OFFSCREEN_Y) {
        titleScreen.logo1_pos -= 8;
        set_spr_position(&logo1, 0, titleScreen.logo1_pos, 97);
        if (titleScreen.logo1_pos <= LOGO1_OFFSCREEN_Y) {
            logo1.visible = false;
        }
    }

    // Animate logo2 downwards
    if (titleScreen.logo2_pos < LOGO2_OFFSCREEN_Y) {
        titleScreen.logo2_pos += 8;
        set_spr_position(&logo2, 0, titleScreen.logo2_pos, 97);
        if (titleScreen.logo2_pos >= LOGO2_OFFSCREEN_Y) {
            logo2.visible = false;
        }
    }
    
    if (menu_bg1.scl.x < Fxp(352)) {
        menu_bg1.scl.x += Fxp_8;
    }
    if (menu_bg1.scl.y < Fxp(32)) {
        menu_bg1.scl.y += Fxp_1;
    }

    switch (titleScreen.menuChoice) {
        case TITLE_OPTION_GAME_MODE:
                gamePalette.GetData()[28] = white;
                animateMenuColor(&do_update_menu4);
                titleScreen.draw_option_mode = true;
                titleScreen.draw_option_players = false;
                titleScreen.draw_option_difficulty = false;
                titleScreen.draw_option_start = false;
                titleScreen.draw_option_options = true;
            break;
            
        case TITLE_OPTION_GAME_PLAYERS:
                gamePalette.GetData()[28] = white;
                animateMenuColor(&do_update_menu4);
                titleScreen.draw_option_mode = false;
                titleScreen.draw_option_players = true;
                titleScreen.draw_option_difficulty = false;
                titleScreen.draw_option_start = false;
                titleScreen.draw_option_options = true;
            break;

        case TITLE_OPTION_GAME_DIFFICULTY:
                gamePalette.GetData()[28] = white;
                animateMenuColor(&do_update_menu4);
                titleScreen.draw_option_mode = false;
                titleScreen.draw_option_players = false;
                titleScreen.draw_option_difficulty = true;
                titleScreen.draw_option_start = false;
                titleScreen.draw_option_options = true;
            break;

        case TITLE_OPTION_GAME_START:
                gamePalette.GetData()[28] = white;
                animateMenuColor(&do_update_menu4);
                titleScreen.draw_option_difficulty = false;
                titleScreen.draw_option_mode = false;
                titleScreen.draw_option_players = false;
                titleScreen.draw_option_start = true;
                titleScreen.draw_option_options = true;             
            break;
            
        case TITLE_OPTION_GAME_OPTIONS:
            gamePalette.GetData()[31] = white;
            animateMenuColor(&do_update_menu3);
            titleScreen.draw_option_options = true;
            switch (titleScreen.menuLastChoice) {
                case TITLE_OPTION_GAME_MODE:
                    titleScreen.draw_option_mode = true;
                    break;
                case TITLE_OPTION_GAME_PLAYERS:
                    titleScreen.draw_option_players = true;
                    break;
                case TITLE_OPTION_GAME_DIFFICULTY:
                    titleScreen.draw_option_difficulty = true;
                    break;
                case TITLE_OPTION_GAME_START:
                    titleScreen.draw_option_start = true;
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }    

    // Options
    menu_text.pos.x = Fxp_0;
    menu_text.pos.y = Fxp(MENU_Y-10);
    menu_text.id = menu_text.anim[0].asset + 1;
    if (titleScreen.draw_option_options)
        my_sprite_draw(&menu_text); // options
        

            menu_text.pos.y = Fxp(MENU_Y+20);
            menu_arrow.pos.y = menu_text.pos.y;
            
            if (!titleScreen.draw_option_start) {
                // left
                menu_arrow.id = menu_arrow.anim[0].asset + titleScreen.left_arrow_id;
                menu_arrow.pos.x = -ARROW_X;
                my_sprite_draw(&menu_arrow);
                // right
                menu_arrow.id = menu_arrow.anim[0].asset + titleScreen.right_arrow_id;
                menu_arrow.pos.x = ARROW_X;
                my_sprite_draw(&menu_arrow);
            }
                
            menu_text.id = menu_text.anim[0].asset + g_Game.gameMode+MODE_OFFSET;
            if (titleScreen.draw_option_mode)
                my_sprite_draw(&menu_text); // classic, story, vs battle
                
            menu_text.id = menu_text.anim[0].asset + g_Game.numPlayers+PLAYER_OFFSET;
            if (titleScreen.draw_option_players)
                my_sprite_draw(&menu_text); // 1, 2, 3, 4
                
            menu_text.id = menu_text.anim[0].asset + g_Game.gameDifficulty+DIFF_OFFSET;
            if (titleScreen.draw_option_difficulty)
                my_sprite_draw(&menu_text); // easy, medium, hard
                
            menu_text.id = menu_text.anim[0].asset;
            if (titleScreen.draw_option_start)
                my_sprite_draw(&menu_text); // start


    my_sprite_draw(&menu_bg1); // shadow
}

//
// OPTIONS
//

void optionsScreen_init(void)
{    
    init_nbg2_img();
    g_Game.lastState = GAME_STATE_TITLE_OPTIONS;
    titleScreen.menuChoice     = TITLE_OPTION_GAME_MODE;
    titleScreen.menuLastChoice = TITLE_OPTION_GAME_MODE;
    slColOffsetOn(NBG1ON);
    slColOffsetAUse(OFF);
    slColOffsetBUse(NBG1ON);
    slColOffsetB(QUARTER_FADE, QUARTER_FADE, QUARTER_FADE);
    g_Audio.currentTrack = LOGO_TRACK;
    if (g_GameOptions.mesh_display) {
        menu_bg2.mesh = MESHon;
    }
    else {
        menu_bg2.mesh = MESHoff;
    }
    menu_bg2.id = menu_bg2.anim[0].asset + 4;
    menu_bg2.zmode = _ZmCC;
    set_spr_position(&menu_bg2, 0, 0, 95);
    
    #if ENABLE_DEBUG_MODE == 1
    set_spr_scale(&menu_bg2, 240.0, 480.0);
    #else
    set_spr_scale(&menu_bg2, 220.0, 480.0);
    #endif
    SRL::VDP2::NBG2::ScrollEnable();
}

void optionsScreen_input(void)
{
    PPLAYER player = &g_Players[0];

    Digital gamepad(player->input->id);
    
        if (gamepad.WasPressed(Digital::Button::Up))
        {
            Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
            titleScreen.optionChoice--;
        }

        if (gamepad.WasPressed(Digital::Button::Down))
        {
            Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
            titleScreen.optionChoice++;
        }

        if (titleScreen.optionChoice == OPTION_ANALOG) {
            analogAdjustmentScreen_input();
        }
 
        // seems like it could be incorporated below
        if (titleScreen.optionChoice == OPTION_CDDA) {
            // Change Tracks
            if (gamepad.WasPressed(Digital::Button::Right))
            {
                g_Audio.currentTrack++;
                if (g_Audio.currentTrack > LAST_TRACK)
                {
                    g_Audio.currentTrack = LOGO_TRACK;
                }
            }
            // Change Tracks
            if (gamepad.WasPressed(Digital::Button::Left))
            {
                g_Audio.currentTrack--;
                if (g_Audio.currentTrack < LOGO_TRACK)
                {
                    g_Audio.currentTrack = LAST_TRACK;
                }
            }            // Change Tracks
            if (gamepad.WasPressed(Digital::Button::A))
            {
                CD::PlaySingle(g_Audio.currentTrack);
                g_Audio.soundTest = true;
            }            // Change Tracks
            if (gamepad.WasPressed(Digital::Button::C))
            {
                CD::Stop();
                g_Audio.soundTest = true;
            }
        }
        
        else if (gamepad.WasPressed(Digital::Button::Left) || gamepad.WasPressed(Digital::Button::Right))
        {
            switch(titleScreen.optionChoice)
            {
                #if ENABLE_DEBUG_MODE == 1
                case OPTION_DEBUG_MODE:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_GameOptions.debug_mode = !g_GameOptions.debug_mode;
                    break;
                case OPTION_DEBUG_TEXT:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_GameOptions.debug_display = !g_GameOptions.debug_display;
                    if (!g_GameOptions.debug_display) {
                        g_Game.vblankClearScreen = true;
                    }
                    break;
                case OPTION_DEBUG_COLLISION:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_GameOptions.testCollision = !g_GameOptions.testCollision;
                    break;
                #endif
                case OPTION_DRAWMESH:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_GameOptions.mesh_display = !g_GameOptions.mesh_display;
                    break;
                case OPTION_DRAWMOSAIC:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_GameOptions.mosaic_display = !g_GameOptions.mosaic_display;
                    break;
                case OPTION_USE_RTC:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_GameOptions.use_rtc = !g_GameOptions.use_rtc;
                    break;
                case OPTION_BIG_HEAD:
                    if (g_GameOptions.unlockBigHeadMode) {
                        Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                        g_GameOptions.bigHeadMode = !g_GameOptions.bigHeadMode;
                    }
                    break;
                case OPTION_ITEMS:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_GameOptions.enableItems = !g_GameOptions.enableItems;
                    break;
                case OPTION_MEOW:
                    Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                    g_GameOptions.enableMeows = !g_GameOptions.enableMeows;
                    break;
                default:
                    break;
            }
        }

        // keep title screen choice in range
        sanitizeValue(&titleScreen.optionChoice, 0, OPTION_MAX);

        // GO BACK
        if (gamepad.WasPressed(Digital::Button::START) || 
            gamepad.WasPressed(Digital::Button::A) ||
            gamepad.WasPressed(Digital::Button::C))
        {
            switch(titleScreen.optionChoice)
            {
                case OPTION_EXIT:
                    Pcm::Play(Sounds.Core[NextSnd], PlayMode::Volatile, 6);
                    // save_game_backup();
                    if (g_Audio.soundTest) {
                        // SRL::Sound::Cdda::PlaySingle(TITLE_TRACK, true);
                        g_Audio.soundTest = false;
                    }
                    g_Audio.currentTrack = GOAL_SCORED_TRACK_1;
                    slColOffsetB(NEUTRAL_FADE, NEUTRAL_FADE, NEUTRAL_FADE);
                    SRL::VDP2::NBG2::ScrollDisable();
                    changeState(GAME_STATE_TITLE_MENU);
                    break;
                    
                default:
                    break;
            }
        }
        if (gamepad.WasPressed(Digital::Button::B))
        {
            Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
            // save_game_backup();
            if (g_Audio.soundTest) {
                CD::PlaySingle(TITLE_TRACK, true);
                g_Audio.soundTest = false;
            }
            g_Audio.currentTrack = GOAL_SCORED_TRACK_1;
            slColOffsetB(NEUTRAL_FADE, NEUTRAL_FADE, NEUTRAL_FADE);
            SRL::VDP2::NBG2::ScrollDisable();
            changeState(GAME_STATE_TITLE_MENU);
        }
}

void optionsScreen_update(void)
{    
    if(g_Game.gameState != GAME_STATE_TITLE_OPTIONS)
    {
        return;
    }
    
    if (attrNbg1.x_scroll > Fxp_0) {
        attrNbg1.x_pos += attrNbg1.x_scroll;
        if (attrNbg1.x_pos > Fxp(512.0))
            attrNbg1.x_pos = Fxp_0;
    }
    slScrPosNbg1(attrNbg1.x_pos.RawValue(), attrNbg1.y_pos.RawValue());
    
    drawOptions();
    drawOptionsCursor();
}

void drawOptions(void)
{
    if(g_Game.gameState != GAME_STATE_TITLE_OPTIONS)
    {
        return;
    }
    #if ENABLE_DEBUG_MODE == 1
    int title_x = 8;
    int options_x = 27;
    #else
    int title_x = 11;
    int options_x = 30;
    #endif
    int options_y = 2;
    
    SRL::Debug::Print(18, options_y, "OPTIONS");
    
    #if ENABLE_DEBUG_MODE == 1
    options_y += 2;
    SRL::Debug::Print(title_x, options_y, "Debug Mode:");
    SRL::Debug::Print(options_x, options_y, g_GameOptions.debug_mode ? "On " : "Off");
    
    options_y += 2;
    SRL::Debug::Print(title_x, options_y, "Debug Display:");
    SRL::Debug::Print(options_x, options_y, g_GameOptions.debug_display ? "On " : "Off");
    
    options_y += 2;
    SRL::Debug::Print(title_x, options_y, "Debug Collision:");
    SRL::Debug::Print(options_x, options_y, g_GameOptions.testCollision ? "On " : "Off");
    #endif
    
    options_y += 2;
    SRL::Debug::Print(title_x, options_y, "Mesh Transparency:");
    if (g_GameOptions.mesh_display) {
        menu_bg1.mesh = MESHon;
        menu_bg2.mesh = MESHon;
        SRL::Debug::Print(options_x, options_y, "On ");
    }
    else {
        menu_bg1.mesh = MESHoff;
        menu_bg2.mesh = MESHoff;
        SRL::Debug::Print(options_x, options_y, "Off");
    }

    options_y += 2;
    SRL::Debug::Print(title_x, options_y, "Mosaic Effect:");
    if (g_GameOptions.mosaic_display) {
	slScrMosSize(MOSAIC_MAX, MOSAIC_MAX);
	slScrMosaicOn(NBG1ON);
        SRL::Debug::Print(options_x, options_y, "On ");
    }
    else {
        SRL::Debug::Print(options_x, options_y, "Off");
	slScrMosSize(MOSAIC_MIN, MOSAIC_MIN);
	slScrMosaicOn(OFF);
    }
    
    options_y += 2;
    SRL::Debug::Print(title_x, options_y, "Real Time Clock:");
    SRL::Debug::Print(options_x, options_y, g_GameOptions.use_rtc ? "On " : "Off");
    
    options_y += 2;
    SRL::Debug::Print(title_x, options_y, "Big Head Mode:");
    if (g_GameOptions.unlockBigHeadMode) {
        SRL::Debug::Print(options_x, options_y, g_GameOptions.bigHeadMode ? "On " : "Off");
    }
    else {
        SRL::Debug::Print(options_x, options_y, "Off");
    }
    
    options_y += 2;
    SRL::Debug::Print(title_x, options_y, "Power-Ups:");
    SRL::Debug::Print(options_x, options_y, g_GameOptions.enableItems ? "On " : "Off");
    
    options_y += 2;
    SRL::Debug::Print(title_x, options_y, "Real-Time Meow:");
    SRL::Debug::Print(options_x, options_y, g_GameOptions.enableMeows ? "On " : "Off");
    
    options_y += 2;
    SRL::Debug::Print(title_x, options_y, "Music Test:");
    SRL::Debug::Print(options_x, options_y, "Track %02d", g_Audio.currentTrack);
    
    options_y += 2;
    SRL::Debug::Print(title_x, options_y, "Analog Adjustment:");
    options_y += 1;
    analogAdjustmentScreen_draw(title_x+5, options_y);     
    
    for(unsigned int i = 0; i < MAX_PLAYERS; i++)
    {
        if (Management::IsConnected(i)) {
            options_y += 1;
        }
    }
    options_y += 2;
    SRL::Debug::Print(title_x, options_y, "Exit");
}

//
// Title Screen Helpers
//


const Angle cursorAngleAdder = Angle(0.0222222222222222);

// menu screen cursor
void drawMenuCursor(void)
{
    if(g_Game.gameState != GAME_STATE_TITLE_MENU)
    {
        return;
    }
    Fxp offset = Trig::Sin(g_Game.cursor_angle) * Fxp_8;
    cursor.pos.x = Fxp(-140) + offset;
    if (titleScreen.menuChoice == TITLE_OPTION_GAME_OPTIONS) {
        cursor.pos.y = Fxp(MENU_Y);
    }
    else {
        cursor.pos.y = Fxp(MENU_Y+30);
    }
    my_sprite_draw(&cursor);
    g_Game.cursor_angle += cursorAngleAdder;
}

// options screen cursor
void drawOptionsCursor(void)
{
    if(g_Game.gameState != GAME_STATE_TITLE_OPTIONS)
    {
        return;
    }
    Fxp offset = Trig::Sin(g_Game.cursor_angle) * Fxp_8;
    #if ENABLE_DEBUG_MODE == 1
    cursor.pos.x = Fxp(-240) + offset;
    #else
    cursor.pos.x = Fxp(-200) + offset;
    #endif
    cursor.pos.y = Fxp::Convert(static_cast<int16_t>(-160 + (titleScreen.optionChoice * 32)));
    if (titleScreen.optionChoice == OPTION_EXIT) 
    {
        cursor.pos.y += Fxp(16); 
        for(unsigned int i = 0; i < MAX_PLAYERS; i++)
        {
            if (Management::IsConnected(i)) {
                cursor.pos.y += Fxp(16); 
            }
        }
    }
    my_sprite_draw(&cursor);
    g_Game.cursor_angle += Angle(0.0222222222222222); // need to add an actual Angle value
}

void animateMenuColor(bool *_do_update) {
    if (titleScreen.increasing) {
        if (titleScreen.h_value < 27) {
            titleScreen.h_value += 1;
            hsl_incSprites[HSL_MENU].h = -2;
            hsl_incSprites[HSL_MENU].l = 3;
            hsl_incSprites[HSL_MENU].s = -3;
        } 
        else {
            titleScreen.increasing = false;
        }
    } 
    else {
        if (titleScreen.h_value > 0) {
            titleScreen.h_value -= 1;
            hsl_incSprites[HSL_MENU].h = 2;
            hsl_incSprites[HSL_MENU].l = -3;
            hsl_incSprites[HSL_MENU].s = +3;
        } 
        else {
            titleScreen.increasing = true;
        }
    }
    *_do_update = true;
}