#include "../main.h"
#include "team_select.h"
#include "physics.h"
#include "player_setup.h"
#include "../core/assets.h"
#include "../core/input.h"
#include "../core/screen_transition.h"
#include "../objects/player.h"
#include "../objects/characters.h"
#include "../vdp2/nbg1.h"
#include "../vdp2/sprite_colors.h"

using namespace SRL::Input;

extern PLAYER g_Players[MAX_PLAYERS];

int g_StartGameFrames = 0;
uint8_t currentNumPlayers = 0;
bool g_TeamSelectPressedStart = false;
bool draw_cursor = false;
bool draw_portrait = false;
bool all_players_ready = false;

void teamSelect_init(void)
{
    g_Game.lastState = GAME_STATE_TEAM_SELECT;
    if (g_Assets.titleAssetsLoaded) {
        unloadTitleAssets();
    }
    if (!g_Assets.characterAssetsLoaded) {
        loadCharacterAssets();
    }
        
    init_nbg2_img();
    
    reset_inputs();
    initPlayers(true);
    initAvailableCharacters();

    initTeams();
    all_players_ready = false;
    g_TeamSelectPressedStart = false;
    g_StartGameFrames = TEAM_SELECT_TIMER;
    g_Team.numTeams = 0;
    g_Team.minTeams = TEAM_1;
    
    if (g_GameOptions.mesh_display) {
        menu_bg1.mesh = MESHon;
        menu_bg2.mesh = MESHon;
        player_bg.mesh = MESHon;
    }
    else {
        menu_bg1.mesh = MESHoff;
        menu_bg2.mesh = MESHoff;
        player_bg.mesh = MESHoff;
    }
    
    // some assets don't change in scale
    menu_bg1.id = menu_bg1.anim[0].asset + 4;
    set_spr_scale(&menu_bg1, 48, 48);
    menu_bg2.id = menu_bg2.anim[0].asset + 5;
    menu_bg2.zmode = _ZmCC;
    set_spr_position_fxp(&menu_bg2, MENU_BG2_X, Fxp_0, MENU_BG2_DEPTH);
    set_spr_scale_fxp(&menu_bg2, MENU_BG2_WIDTH, MENU_BG2_HEIGHT);
    
    SRL::VDP2::NBG2::ScrollEnable();
    
    g_Transition.mosaic_in = true;
    g_Transition.music_in = true;
    g_Transition.fade_in = true;
    g_Transition.all_in = true;
}

// main logic loop
void teamSelect_update(void)
{
    check_player_inputs();
    
    // EVERYONE PRESSED START
    if(g_TeamSelectPressedStart == true)
    {
        g_StartGameFrames--;
        
        if(g_StartGameFrames <= 0)
        {
            for(unsigned int i = 0; i < COUNTOF(g_Players); i++)
            {
                PPLAYER player = &g_Players[i];
                if(!player->isPlaying)
                {
                    if (g_Game.numPlayers >= g_Game.currentNumPlayers) {
                        initAiPlayers();               
                    }
                    else {
                        // player didn't pick a team and thus isn't playing
                        player->isActivated = false;
                    }
                }
            }
            SRL::Debug::PrintClearScreen();
            SRL::VDP2::NBG2::ScrollDisable(); // should fade out instead
            transitionState(GAME_STATE_GAMEPLAY);
        }
    }
    
    if(g_StartGameFrames > 0)
    {
        teamSelect_draw();
    }
}

// main draw routine
void teamSelect_draw(void)
{
    if (attrNbg1.x_scroll > Fxp(0)) {
        attrNbg1.x_pos += attrNbg1.x_scroll;
        if (attrNbg1.x_pos > Fxp(512.0))
            attrNbg1.x_pos = Fxp(0);
    }
    slScrPosNbg1(attrNbg1.x_pos.RawValue(), attrNbg1.y_pos.RawValue());
    
    drawCharacterSelectGrid();
}

void drawCharacterSelectGrid(void)
{    

    Fxp portrait_y = PORTRAIT_Y;

    int text_x = 2;
    int text_y = 2;
    
    if (g_Game.numPlayers == ONE_PLAYER) {
        portrait_y = Fxp(-6);
        text_y = 12;
    }
    else if (g_Game.numPlayers == TWO_PLAYER) {
        portrait_y = Fxp(-70);
        text_y = 8;
    }
    else if (g_Game.numPlayers == THREE_PLAYER) {
        portrait_y = Fxp(-118);
        text_y = 5;
    }
    if (g_Game.frame % 2 == 0) { // modulus
        draw_cursor = !draw_cursor;
    }
    if (g_Game.frame % 16 == 0) { // modulus
        draw_portrait = !draw_portrait;
    }
    
    looped_animation_pow(&paw[CHARACTER_NONE], 4);
    
    for(int8_t i = 0; i < (g_Game.numPlayers+1); i++)
    {
        PPLAYER player = &g_Players[i];
        
        if (!g_GameOptions.debug_display) {
            SRL::Debug::Print(text_x, text_y, "Player %d:   ", i+1);
            if (player->character.choice != CHARACTER_NONE || g_Game.numPlayers > ONE_PLAYER) {
                SRL::Debug::Print(text_x, text_y+CHARACTER_TEXT_Y, "%s", characterNames[player->character.choice]);
            }           
            if (player->teamSelected && g_Game.numPlayers > ONE_PLAYER) {
                SRL::Debug::Print(text_x, text_y+CHARACTER_TEXT_Y+2, "Team %d ", player->teamChoice);
            }
        }
        if (player->character.selected && !g_GameOptions.debug_display) {
            if (player->isReady) {
                SRL::Debug::Print(text_x+TEAM_TEXT_X1, text_y, "Ready");
            }
            else if (player->teamSelected && g_Team.numTeams >= g_Team.minTeams && !player->isReady && !draw_portrait) {
                SRL::Debug::Print(text_x+TEAM_TEXT_X1, text_y, "Press");
            }
            else if (player->teamSelected && g_Team.numTeams >= g_Team.minTeams && !player->isReady && draw_portrait) {
                SRL::Debug::Print(text_x+TEAM_TEXT_X1, text_y, "     ");
            }
            else if (!player->teamSelected && g_Game.numPlayers > ONE_PLAYER) {
                validateTeam(player);
                SRL::Debug::Print(text_x+TEAM_TEXT_X1, text_y, "Team: ");
            }

            if (player->teamSelected && g_Team.numTeams >= g_Team.minTeams && !player->isReady && !draw_portrait) {
                SRL::Debug::Print(text_x+TEAM_TEXT_X1, text_y+TEAM_TEXT_Y, "Start ");
            }
            else if (player->teamSelected && g_Team.numTeams >= g_Team.minTeams && !player->isReady && draw_portrait) {
                SRL::Debug::Print(text_x+TEAM_TEXT_X1, text_y+TEAM_TEXT_Y, "     ");
            }
            else if (player->teamSelected && g_Team.numTeams < g_Team.minTeams) {
                SRL::Debug::Print(text_x+TEAM_TEXT_X1, text_y+TEAM_TEXT_Y, "Wait. ");
            }
            else if (!player->teamSelected && g_Game.numPlayers > ONE_PLAYER) {
                SRL::Debug::Print(text_x+TEAM_TEXT_X2, text_y+TEAM_TEXT_Y, "%d        ", player->teamChoice);
            }
        }
        // SELECTION BOX
        switch (player->character.selected) {
            case false: // SELECT CHARACTER
                set_spr_position_fxp(player->_cursor[0], PORTRAIT_X, portrait_y, CURSOR_DEPTH);
                set_spr_position_fxp(player->_cursor[1], PORTRAIT_X+Fxp(46), portrait_y, CURSOR_DEPTH);
                // PAW
                set_spr_position_fxp(player->_sprite, PAW_X, portrait_y, PORTRAIT_DEPTH);
                my_sprite_draw(player->_sprite);
                break;
            case true: // SELECT TEAM
                set_spr_position_fxp(player->_cursor[0], PAW_X, portrait_y, CURSOR_DEPTH);                
                set_spr_position_fxp(player->_cursor[1], PAW_X+Fxp(46), portrait_y, CURSOR_DEPTH);                
                // CURSOR BACKGROUND
                set_spr_position_fxp(&menu_bg1, PAW_X, portrait_y, MENU_BG1_DEPTH);
                menu_bg1.mesh = MESHon;
                my_sprite_draw(&menu_bg1);
                // PAW
                set_spr_position_fxp(player->_sprite, PAW_X, portrait_y, PORTRAIT_DEPTH);
                looped_animation_pow(player->_sprite, 4);
                my_sprite_draw(player->_sprite);
                break;
        }
        
        // CURSOR
        if (draw_cursor) {
            player->_cursor[0]->mesh = MESHon;
            player->_cursor[1]->mesh = MESHon;
        }
        else {
            player->_cursor[0]->mesh = MESHoff;
            player->_cursor[1]->mesh = MESHoff;
        }
        player->_cursor[0]->id = player->_cursor[0]->anim[0].asset + i;
        my_sprite_draw(player->_cursor[0]);
        player->_cursor[1]->id = player->_cursor[1]->anim[0].asset + i ;
        my_sprite_draw(player->_cursor[1]);
        
        // PORTRAIT
        player->_portrait->id = player->_portrait->anim[0].asset + player->character.choice;
        set_spr_position_fxp(player->_portrait, PORTRAIT_X, portrait_y, PORTRAIT_DEPTH);
        if (player->character.choice == CHARACTER_NONE && !g_GameOptions.debug_display) {
            if (draw_portrait) {                
                SRL::Debug::Print(text_x+10, text_y+1, "Press");
                SRL::Debug::Print(text_x+10, text_y+3, "Start");
            }
            else {                
                SRL::Debug::Print(text_x+10, text_y+1, "     ");
                SRL::Debug::Print(text_x+10, text_y+3, "     ");
            }
            // CURSOR BACKGROUND
            set_spr_position_fxp(&menu_bg1, PORTRAIT_X, portrait_y, MENU_BG1_DEPTH);
            menu_bg1.mesh = MESHoff;
            my_sprite_draw(&menu_bg1);
        }
        else {
                my_sprite_draw(player->_portrait);
        }
        
        // CHARACTER METER
        if (player->startSelection) {
            // SPEED
            if (!g_GameOptions.debug_display) {
                if (g_GameOptions.debug_mode) {
                    SRL::Debug::Print(text_x+METER_TEXT_X, text_y,   "Speed:%d    ", player->maxSpeed.As<uint8_t>());
                }
                else {
                    SRL::Debug::Print(text_x+METER_TEXT_X, text_y,   "Speed    ");
                }
            }
            // yellow
            meter.id = meter.anim[0].asset;
            Fxp speed = player->maxSpeed / 4;
            set_spr_scale_fxp(&meter, speed, METER_HEIGHT);
            set_spr_position_fxp(&meter, METER_X, portrait_y-METER_Y1, PORTRAIT_DEPTH);
            my_sprite_draw(&meter);
            // red
            meter.id = meter.anim[0].asset + 1;
            set_spr_scale_fxp(&meter, (METER_WIDTH-speed), METER_HEIGHT);
            set_spr_position_fxp(&meter, (METER_X+(Fxp_2 * player->maxSpeed)), portrait_y-METER_Y1, PORTRAIT_DEPTH);
            my_sprite_draw(&meter);
            // ACCELERATION
            if (!g_GameOptions.debug_display) {
                if (g_GameOptions.debug_mode) {
                    SRL::Debug::Print(text_x+METER_TEXT_X, text_y+METER_TEXT_Y2, "Accel:%d    ", player->acceleration.As<uint8_t>()); 
                }
                else {
                    SRL::Debug::Print(text_x+METER_TEXT_X, text_y+METER_TEXT_Y2, "Accel.    "); 
                }
            }
            // yellow       
            meter.id = meter.anim[0].asset;
            Fxp acceleration = player->acceleration / 4;
            set_spr_scale_fxp(&meter, acceleration, METER_HEIGHT);
            set_spr_position_fxp(&meter, METER_X, portrait_y-METER_Y2, PORTRAIT_DEPTH);
            my_sprite_draw(&meter);
            // red
            meter.id = meter.anim[0].asset + 1;
            set_spr_scale_fxp(&meter, (METER_WIDTH-acceleration), METER_HEIGHT);
            set_spr_position_fxp(&meter, (METER_X+(Fxp_2 * player->acceleration)), portrait_y-METER_Y2, PORTRAIT_DEPTH);
            my_sprite_draw(&meter);
            // POWER
            if (!g_GameOptions.debug_display) {
                if (g_GameOptions.debug_mode) {
                    SRL::Debug::Print(text_x+METER_TEXT_X, text_y+METER_TEXT_Y3, "Power:%d    ", player->power.As<uint8_t>());
                }
                else {
                    SRL::Debug::Print(text_x+METER_TEXT_X, text_y+METER_TEXT_Y3, "Power    ");
                }
            }
            // yellow
            meter.id = meter.anim[0].asset;
            Fxp power = player->power / 4;
            set_spr_scale_fxp(&meter, power, METER_HEIGHT);
            set_spr_position_fxp(&meter, METER_X, portrait_y+METER_Y3, PORTRAIT_DEPTH);
            my_sprite_draw(&meter);
            // red
            meter.id = meter.anim[0].asset + 1;
            set_spr_scale_fxp(&meter, (METER_WIDTH-power), METER_HEIGHT);
            set_spr_position_fxp(&meter, (METER_X+(Fxp_2 * player->power)), portrait_y+METER_Y3, PORTRAIT_DEPTH);
            my_sprite_draw(&meter);
        }
        
        portrait_y += PLAYER_OFFSET_Y;
        text_y += PLAYER_TEXT_OFFSET_Y;
    }
}

void characterSelect_input(void)
{   
    // ONLY PLAYER 1 CAN EXIT TO TITLE SCREEN
    Digital player1(0);
    if (player1.WasPressed(Digital::Button::B) && g_Players[0].startSelection == false && g_Players[0].pressedB == false)
    {
        g_Game.vblankClearScreen = true;
        SRL::VDP2::NBG2::ScrollDisable();
        g_Game.lastState = GAME_STATE_TEAM_SELECT;
        transitionState(GAME_STATE_TITLE_SCREEN);
    }
    
    for(int8_t i = 0; i < (g_Game.numPlayers+1); i++)
    {
        PPLAYER player = &g_Players[i];
        
        Digital port(player->input->id);
        
        if (player->startSelection && !player->character.selected) {
            // CHOOSE CHARACTER
            if (port.WasPressed(Digital::Button::Left))
            {
                Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                do
                {
                    player->character.choice--;
                    if (player->character.choice < CHARACTER_MACCHI)
                    {
                        player->character.choice = CHARACTER_GARF;
                    }
                } while (!characterAvailable[player->character.choice]);
            }
            if (port.WasPressed(Digital::Button::Right))
            {
                Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                do
                {
                    player->character.choice++;
                    if (player->character.choice > CHARACTER_GARF)
                    {
                        player->character.choice = CHARACTER_MACCHI;
                    }
                } while (!characterAvailable[player->character.choice]);
            }

            // ASSIGN STATS
            assignPlayerStats(player);
            
            // GO BACK
            if (port.WasPressed(Digital::Button::B) && player->pressedB == false)
            {
                g_Game.vblankClearScreen = true;
                Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
                player->teamChoice = TEAM_COUNT;
                player->startSelection = false;
                characterAvailable[player->character.choice] = true;
                player->character.choice = CHARACTER_NONE;
                player->maxSpeed = Fxp_0;
                player->acceleration = Fxp_0;
                player->power = Fxp_0;
                player->input->id = 32;
                player->input->isSelected = false;
                player->input = nullptr;
                assignCharacterSprite(player);
                return;
            }
            
            // SELECT CHARACTER
            if (port.WasPressed(Digital::Button::START) ||
                port.WasPressed(Digital::Button::A) ||
                port.WasPressed(Digital::Button::C))
            {
                g_Game.vblankClearScreen = true;
                Pcm::Play(Sounds.Core[NextSnd], PlayMode::Volatile, 6);
                // assign to a default team (left vs right)
                if (i %2 == 0) { // modulus
                    player->teamChoice = TEAM_1;
                    player->_sprite->flip = sprNoflip;
                }
                else {
                    player->teamChoice = TEAM_2;
                    player->_sprite->flip = sprHflip;
                }
                player->character.selected = true;
                characterAvailable[player->character.choice] = false;
            }
            assignCharacterSprite(player);
            // make sure the scale is normal
            set_spr_scale(player->_sprite, 2, 2);
        }
        // BEGIN CHARACTER SELECTION
        if (!player->startSelection) {
            // Once a player starts selection, they shouldn't be able to assign a new id
            if (player->input->isSelected && port.WasPressed(Digital::Button::START)) {
                g_Game.vblankClearScreen = true;
                Pcm::Play(Sounds.Core[StartSnd], PlayMode::Volatile, 6);
                player->startSelection = true;
                player->character.choice = CHARACTER_MACCHI;
                validateCharacters(player);
                assignCharacterSprite(player);
            }
            else {
                for(unsigned int ip = 0; ip < COUNTOF(g_Inputs); ip++)
                {
                    // Once a player starts selection, they shouldn't be able to assign a new id
                    if (g_Inputs[ip].isSelected) {
                        continue;
                    }
                    if (port.WasPressed(Digital::Button::START))
                    {
                        g_Game.vblankClearScreen = true;
                        Pcm::Play(Sounds.Core[StartSnd], PlayMode::Volatile, 6);
                        player->input = &g_Inputs[ip];
                        player->input->id = ip;
                        player->input->isSelected = true;
                        
                        player->startSelection = true;
                        player->character.choice = CHARACTER_MACCHI;
                        validateCharacters(player);
                        assignCharacterSprite(player);
                        
                        player->teamChoice = TEAM_1;
                        validateTeam(player);
                       return;
                    }
                }
            }
        }
        // DEFAULT CHARACTER SETUP
        if (!player->character.selected) {
            player->_sprite->flip = sprNoflip;
            // make sure 2 people don't have the same character selected
            if (player->startSelection) {
                validateCharacters(player);
           }
        }
    }
    g_Players[0].pressedB = false; // button press expires
}            

// once a character has been selected all players can select their teams
void teamSelect_input(void)
{    
    // already pressed start, nothing to do
    if(g_TeamSelectPressedStart == true)
    {
        return;
    }

    for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PPLAYER player = &g_Players[i];
        
        Digital port(player->input->id);
        
        player->pressedB = false; // button press expires
        
        if (player->teamSelected == false && player->character.selected) {
            if (g_Game.numPlayers == ONE_PLAYER) {
                // default team
                player->teamChoice = TEAM_1;
                g_Team.numTeams++;
            }
            // CHOOSE A TEAM
            if (port.WasPressed(Digital::Button::Left) && g_Game.numPlayers != ONE_PLAYER) {
                Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                do {
                    player->teamChoice--;
                    if (player->teamChoice < TEAM_1) {
                        player->teamChoice = g_Team.maxTeams;
                    }
                } while (!g_Team.isAvailable[player->teamChoice]); // Skip full teams // replace with teamAvailable
                
                // Flip the sprite based on even/odd team
                if (player->teamChoice == TEAM_2 || player->teamChoice == TEAM_4) {
                    player->_sprite->flip = sprHflip;
                } else {
                    player->_sprite->flip = sprNoflip;
                }

                return;
            }
            if (port.WasPressed(Digital::Button::Right) && g_Game.numPlayers != ONE_PLAYER) {
                Pcm::Play(Sounds.Core[CursorSnd], PlayMode::Volatile, 6);
                do {
                    player->teamChoice++;
                    if (player->teamChoice > g_Team.maxTeams) {
                        player->teamChoice = TEAM_1;
                    }
                } while (!g_Team.isAvailable[player->teamChoice]); // Skip full teams // replace with teamAvailable

                // Flip the sprite based on even/odd team
                if (player->teamChoice == TEAM_2 || player->teamChoice == TEAM_4) {
                    player->_sprite->flip = sprHflip;
                } else {
                    player->_sprite->flip = sprNoflip;
                }

                return;
            }

            // GO BACK
            if (port.WasPressed(Digital::Button::B))
            {
                g_Game.vblankClearScreen = true;
                Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
                player->pressedB = true;
                player->teamChoice = TEAM_COUNT;
                characterAvailable[player->character.choice] = true;
                player->character.selected = false;
                return;
            }
            
            // SELECT TEAM
            if (port.WasPressed(Digital::Button::START) ||
                port.WasPressed(Digital::Button::A) ||
                port.WasPressed(Digital::Button::C))
            {
                g_Game.vblankClearScreen = true;
                Pcm::Play(Sounds.Core[NextSnd], PlayMode::Volatile, 6);
                player->teamSelected = true;
                g_Team.isAvailable[player->teamChoice] = false;
                g_Team.isActive[player->teamChoice] = true;
                g_Team.numTeams++;
                return;
            }
        }
        
        if (player->teamSelected == true) {
            // START GAME
            if (playerReadyState())
            {
                g_TeamSelectPressedStart = true;
                SRL::Debug::PrintClearScreen();
                return;
            }
            
            // PRESS START TO BE "READY"
            if (port.WasPressed(Digital::Button::START))
            {
                if(!validateTeamCount() || player->isReady)
                {
                    return;
                }
                g_Game.vblankClearScreen = true;
                Pcm::Play(Sounds.Core[NextSnd], PlayMode::Volatile, 6);
                player->isReady = true;
                g_Game.currentNumPlayers++;
                return;
            }
            
            // GO BACK
            if (port.WasPressed(Digital::Button::B))
            {   
                g_Game.vblankClearScreen = true;
                Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
                resetReadyState();
                all_players_ready = false;
                player->isReady = false;
                player->isPlaying = false;
                player->teamSelected = false;
                g_Team.isAvailable[player->teamChoice] = true;
                g_Team.isActive[player->teamChoice] = true;
                player->pressedB = true;
                g_Team.numTeams--;
                if (g_Game.currentNumPlayers > 0)
                    g_Game.currentNumPlayers--;
                return;
            }
        }
    }
}

// DON'T START GAME UNTIL EVERONE IS READY
bool playerReadyState(void) {
     for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PPLAYER player = &g_Players[i];

        if (player->startSelection && !player->isReady)
        {
            all_players_ready = false;
            return false;
        }
    }
    all_players_ready = true;
    return true;
}

void resetReadyState(void) {
    for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PPLAYER player = &g_Players[i];
        player->isReady = false;
    }
}

// AT LEAST 2 TEAMS ARE REQUIRED
bool validateTeamCount(void)
{
    if(g_Team.numTeams < g_Team.minTeams)
    {
        return false;
    }
    
    for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PPLAYER player = &g_Players[i];

        if(player->teamChoice == TEAM_COUNT)
        {
            player->numLives = 0;
            player->isPlaying = false;
            continue;
        }
        else
        {
            player->isPlaying = true;
        }
    }
    return true;
}
