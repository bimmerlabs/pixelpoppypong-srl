#include <srl.hpp>
using namespace SRL::Types;

#include "../main.h"
#include "backup.h"
#include "screen_transition.h"
#include "pause.h"
#include "assets.h"
#include "input.h"
#include "../game/ppp_logo.h"
#include "../game/title_screen.h"
// #include "../game/team_select.h"
// #include "../game/gameplay.h"
// #include "../game/physics.h"
#include "../game/credits.h"
#include "../game/name_entry.h"
// #include "../objects/player.h"
// #include "../vdp2/nbg1.h"

// extern PLAYER g_Players[MAX_PLAYERS];

void debux_text(void)
{
    if (!g_GameOptions.debug_display) {
        return;
    }
        SRL::Debug::Print(2, 2, "GameState:%2d", g_Game.gameState);
        SRL::Debug::Print(18, 2, "Last:%2d", g_Game.lastState);
        SRL::Debug::Print(29, 2, "Next:%2d", g_Game.nextState);
        SRL::Debug::Print(2, 3, "Frame:%3d", g_Game.frame);
        SRL::Debug::Print(2, 4, "MasterVolume:%3d", g_Audio.masterVolume);
        SRL::Debug::Print(20, 3, "Sprites:%d    ", SRL::VDP1::GetTextureCount());
        SRL::Debug::Print(20, 4, "VDP1 Memory:%6d", SRL::VDP1::GetAvailableMemory());
        SRL::Debug::Print(20, 5, "HWRAM free space:%6d", SRL::Memory::HighWorkRam::GetFreeSpace());
        SRL::Debug::Print(20, 6, "HWRAM used space:%6d", SRL::Memory::HighWorkRam::GetUsedSpace());
        // SRL::Debug::Print(20, 3, "GameMode:%d", g_Game.gameMode);
        // SRL::Debug::Print(20, 4, "Difficulty:%d", g_Game.gameDifficulty);
        
        DateTime time = DateTime::Now();
        SRL::Debug::Print(2, 26, "Date:%d.%d.%d    ", time.Day(), time.Month(), time.Year());
        SRL::Debug::Print(2, 27, "Time:%02d:%02d:%02d", time.Hour(), time.Minute(), time.Second());        
        
        // SRL::Debug::Print(20, 3, "Season:%2d", g_Game.timeSeason);
        // SRL::Debug::Print(20, 4, "Month:%2d, %2d", time.Month(), OCTOBER);
        
        // SRL::Debug::Print(20, 5, "AllIn/Out:%d,%d", g_Transition.all_in, g_Transition.all_out);
        // SRL::Debug::Print(20, 6, "FadeIn/Out:%d,%d", g_Transition.fade_in, g_Transition.fade_out);
        // SRL::Debug::Print(20, 7, "MosaicIn/Out:%d,%d", g_Transition.mosaic_in, g_Transition.mosaic_out);
        // SRL::Debug::Print(20, 8, "MusicIn/Out:%d,%d", g_Transition.music_in, g_Transition.music_out);
        // SRL::Debug::Print(2, 5, "cdIsPlaying:%d", g_Audio.cdIsPlaying);
        // SRL::Debug::Print(2, 5, "AttractScreen:%d", g_AttractScreen.id);
        
        
        PPLAYER player = &g_Players[0];       
        SRL::Debug::Print(2, 8, "inputID:%2d ",  player->input->id);
        SRL::Debug::Print(2, 9, "isSelected:%i", player->input->isSelected);
        // SRL::Debug::Print(2, 10, "isAnalog:%i", input->isAnalog);
        // SRL::Debug::Print(2, 11, "axis_x:%d    ", input->axis_x.As<int32_t>());
        // SRL::Debug::Print(2, 12, "axis_y:%d    ", input->axis_y.As<int32_t>());
        // SRL::Debug::Print(2, 13, "left_trigger:%d    ", input->left_trigger.As<int32_t>());
        // SRL::Debug::Print(2, 14, "right_trigger:%d    ", input->right_trigger.As<int32_t>());
        // SRL::Debug::Print(2, 15, "sensitivity:%d    ", input->sensitivity.As<int32_t>());

        
        // SRL::Debug::Print(2,10, is_cart_mem_available() 
            // ? "Cart Backup Memory Detected" : "Cart Backup Memory Not Detected");
        // SRL::Debug::Print(2,11, is_internal_mem_available() 
            // ? "Internal Backup Memory Detected" : "Internal Backup Memory Not Detected");
            
        // SRL::Debug::Print(2, 13, " !\"#$%&'()*+,-./");
        // SRL::Debug::Print(2, 14, "0123456789:;<=>?");
        // SRL::Debug::Print(2, 15, "@ABCDEFGHIJKLMNO");
        // SRL::Debug::Print(2, 16, "PQRSTUVWXYZ[\\]^_");
        // SRL::Debug::Print(2, 17, "`abcdefghijklmo");
        // SRL::Debug::Print(2, 18, "pqrstuvwxyz{|}~\177");
        
                // for(int8_t i = 0; i < MAX_PLAYERS; i++)
                // {
                    // PPLAYER player = &g_Players[i];
                    // SRL::Debug::Print(2, 10+i, "p%i isPlaying:%i", i, player->isPlaying);
                // }
                // for(int8_t i = 0; i < MAX_PLAYERS; i++)
                // {
                    // PPLAYER player = &g_Players[i];
                    // SRL::Debug::Print(2, 14+i, "p%i isActivated:%i", i, player->isActivated);
                // }
                // for(int8_t i = 0; i < MAX_PLAYERS; i++)
                // {
                    // PPLAYER player = &g_Players[i];
                    // SRL::Debug::Print(2, 18+i, "p%i isDead:%i", i, player->isDead);
                // }
        
        switch (g_Game.gameState) {
            case GAME_STATE_PPP_LOGO: // logo
                SRL::Debug::Print(2, 6, "LogoTimer:%2d", g_LogoTimer/60);
                break;
                
            case GAME_STATE_TITLE_SCREEN: // title
                SRL::Debug::Print(2, 6, "TitleTimer:%2d", titleScreen.timer/60);
                // SRL::Debug::Print(2, 6, "LOGO1.SPR_ID:%i", logo1.id);
                // SRL::Debug::Print(2, 7, "LOGO2.SPR_ID:%i", logo2.id);
                
                // SRL::Debug::Print(2, 7, "LOGO1_POS:%i", logo1_pos);
                // SRL::Debug::Print(20, 7, "LOGO1:%i", logo1.pos.y);
                // SRL::Debug::Print(2, 8, "LOGO2_POS:%i", logo2_pos);
                // SRL::Debug::Print(20, 8, "LOGO2:%i", logo2.pos.y);
                // SRL::Debug::Print(20, 10, "VELOCITY:%i", logo_velocity);
                // SRL::Debug::Print(20, 11, "LOGO_FALLING:%i", logo_falling);
                // SRL::Debug::Print(20, 12, "LOGO_BOUNCE:%i", logo_bounce);
                break;      
                          
            case GAME_STATE_NAME_ENTRY: // title
                SRL::Debug::Print(2, 6, "nameEntry.timer:%2d", nameEntry.timer/60);
                break;
                
            case GAME_STATE_TITLE_MENU: // menu
                SRL::Debug::Print(2, 6, "GameMode:%i", g_Game.gameMode);
                SRL::Debug::Print(2, 7, "GameDifficulty:%i", g_Game.gameDifficulty);
                // SRL::Debug::Print(2, 7, "TITLE CHOICE:%i", g_TitleScreenChoice);
                // SRL::Debug::Print(2, 7, "LOGO1_POS:%i", logo1_pos);
                // SRL::Debug::Print(20, 7, "LOGO1:%i", logo1.pos.y);
                // SRL::Debug::Print(2, 8, "LOGO2_POS:%i", logo2_pos);
                // SRL::Debug::Print(20, 8, "LOGO2:%i", logo2.pos.y);
                // SRL::Debug::Print(20, 9, "VELOCITY:%i", logo_velocity);
                // SRL::Debug::Print(20, 11, "LOGO_FALLING:%i", logo_falling);
                // SRL::Debug::Print(20, 12, "LOGO_BOUNCE:%i", logo_bounce);
                // SRL::Debug::Print(2, 18, "NUM.PLAYERS:%i", g_Game.numPlayers);
                // SRL::Debug::Print(2, 19, "MIN.PLAYERS:%i", g_Game.minPlayers);
                // SRL::Debug::Print(2, 20, "MAX.PLAYERS:%i", g_Game.maxPlayers);
                // SRL::Debug::Print(20, 18, "NUM.TEAMS:%i", g_Team.numTeams);
                // SRL::Debug::Print(20, 19, "MIN.TEAMS:%i", g_Team.minTeams);
                SRL::Debug::Print(2, 11, "MaxTeams:%i", g_Team.maxTeams);
                break;
                
            // case GAME_STATE_TITLE_OPTIONS: // menu
                // SRL::Debug::Print(2, 5, "GAMEMODE:%i", g_Game.gameMode);
                // SRL::Debug::Print(2, 6, "OPTION CHOICE:%i", g_OptionScreenChoice);
                // break;
                
            case GAME_STATE_TEAM_SELECT: // menu
                // SRL::Debug::Print(2, 5, "GAMEMODE:%i", g_Game.gameMode);
                
                // SRL::Debug::Print(2, 8, "NUMPLAYERS:%i", g_Game.currentNumPlayers);
                // SRL::Debug::Print(2, 9, "NUMTEAMS:%i", g_Team.numTeams);
                
                // for (int i = 0; i < CHARACTER_MAX; i++) {
                    // SRL::Debug::Print(2, (8+i), "UNLOCKED:%d", characterUnlocked[i]);
                // }
                // for (int i = 0; i < CHARACTER_MAX; i++) {
                    // SRL::Debug::Print(20, (8+i), "AVAILABLE:%d", characterAvailable[i]);
                // }
                
                // for (int i = 0; i <= g_Game.maxPlayers; i++) {
                    // SRL::Debug::Print(2, 9+i, "P%d Input:%3d", i+1, g_Players[i].input->id);
                    // SRL::Debug::Print(22, 9+i, "is Selected:%3d", g_Players[i].input->isSelected);
                // }
                
                // SRL::Debug::Print(2, 10, "TEAM 1 AVAILABLE:%i", g_Team.isAvailable[TEAM_1]);
                // SRL::Debug::Print(2, 11, "TEAM 2 AVAILABLE:%i", g_Team.isAvailable[TEAM_2]);
                // SRL::Debug::Print(2, 12, "TEAM 3 AVAILABLE:%i", g_Team.isAvailable[TEAM_3]);
                // SRL::Debug::Print(2, 13, "TEAM 4 AVAILABLE:%i", g_Team.isAvailable[TEAM_4]);
                
                // SRL::Debug::Print(2, 7, "CHARACTER_MAX:%i",  CHARACTER_MAX);
                // SRL::Debug::Print(2, 24, "P1 CHAR CHOICE:%3d ", g_Players[0].character.choice);
                // SRL::Debug::Print(2, 25, "P1 SPRITE:%3d", g_Players[0]._sprite->id);
                
                // SRL::Debug::Print(20, 7, "P1 STARTSELECT:%i",  g_Players[0].startSelection);
                // SRL::Debug::Print(20, 8, "P1 CHAR SELECT:%i", g_Players[0].character.selected);
                // SRL::Debug::Print(20, 9, "P1 TEAM SELECT:%i", g_Players[0].teamSelected);
                SRL::Debug::Print(2, 10, "P1 TeamChoice:%d ", g_Players[0].teamChoice);
                SRL::Debug::Print(2, 11, "MmaxTeams:%d ", g_Team.maxTeams);
                // SRL::Debug::Print(20, 11, "P1 READY:%i", g_Players[0].isReady);
                
                // // SRL::Debug::Print(2, 13, "P2 STARTSELECT:%i",  g_Players[1].startSelection);
                // // SRL::Debug::Print(2, 14, "P2 CHAR SELECT:%i", g_Players[1].character.selected);
                // // SRL::Debug::Print(2, 15, "P2 TEAM SELECT:%i", g_Players[1].teamSelected);
                // // SRL::Debug::Print(2, 16, "P2 TEAM CHOICE:%i", g_Players[1].teamChoice);
                // // SRL::Debug::Print(2, 17, "P2 READY:%i", g_Players[1].isReady);
                
                // // SRL::Debug::Print(20, 7, "P3 STARTSELECT:%i",  g_Players[2].startSelection);
                // // SRL::Debug::Print(20, 8, "P3 CHAR SELECT:%i", g_Players[2].character.selected);
                // // SRL::Debug::Print(20, 9, "P3 TEAM SELECT:%i", g_Players[2].teamSelected);
                // // SRL::Debug::Print(20, 10, "P3 TEAM CHOICE:%i", g_Players[2].teamChoice);
                // // SRL::Debug::Print(20, 11, "P3 READY:%i", g_Players[2].isReady);
                
                // // SRL::Debug::Print(20, 13, "P4 STARTSELECT:%i",  g_Players[3].startSelection);
                // // SRL::Debug::Print(20, 14, "P4 CHAR SELECT:%i", g_Players[3].character.selected);
                // // SRL::Debug::Print(20, 15, "P4 TEAM SELECT:%i", g_Players[3].teamSelected);
                // // SRL::Debug::Print(20, 16, "P4 TEAM CHOICE:%i", g_Players[3].teamChoice);
                // // SRL::Debug::Print(20, 17, "P4 READY:%i", g_Players[3].isReady);
                
                
                // SRL::Debug::Print(2, 18, "NUM.TEAMS %i:", g_Team.numTeams);
                // SRL::Debug::Print(2, 19, "MIN.TEAMS %i:", g_Team.minTeams);
                // SRL::Debug::Print(2, 20, "MAX.TEAMS %i:", g_Team.maxTeams);
                // // SRL::Debug::Print(2, 19, "ALL READY:%i", all_players_ready);
                // // SRL::Debug::Print(2, 20, "PRESSEDSTART:%i",  g_TeamSelectPressedStart);
                
                break;
                
            case GAME_STATE_DEMO_LOOP:
                // SRL::Debug::Print(2, 5, "GAMEACTIVE:%i", g_Game.isActive);
                // SRL::Debug::Print(2, 6, "BALLACTIVE:%i", g_Game.isBallActive);
                // // SRL::Debug::Print(2, 5, "DEMOTIMER:%i", g_DemoTimer/60);
                // // SRL::Debug::Print(2, 8, "MACCHI.X:%i", macchi.pos.x);
                // // SRL::Debug::Print(2, 9, "MACCHI.Y:%i", macchi.pos.y);
                // // SRL::Debug::Print(2, 10, "COLLIDING:%i", macchi.isColliding);
                // // SRL::Debug::Print(2, 11, "JELLY.X:%i", jelly.pos.x);
                // // SRL::Debug::Print(2, 12, "JELLY.Y:%i", jelly.pos.y);
                // // SRL::Debug::Print(2, 13, "COLLIDING:%i", jelly.isColliding);
                // // SRL::Debug::Print(20, 8, "POPPY.X:%i", pixel_poppy.pos.x);
                // // SRL::Debug::Print(20, 9, "POPPY.Y:%i", pixel_poppy.pos.y);
                // // SRL::Debug::Print(20, 10, "COLLIDING:%i", pixel_poppy.isColliding);
                
                // // SRL::Debug::Print(2, 12, "PLAYER1 RAD:%i", JO_FIXED_TO_INT(g_Players[0]._sprite->pos.r));
                // // SRL::Debug::Print(2, 13, "PLAYER1 RAD:%i", JO_FIXED_TO_INT(g_Players[1]._sprite->pos.r));
                // // SRL::Debug::Print(2, 14, "PLAYER1 RAD:%i", JO_FIXED_TO_INT(g_Players[2]._sprite->pos.r));
                // // SRL::Debug::Print(2, 15, "PLAYER1 RAD:%i", JO_FIXED_TO_INT(g_Players[3]._sprite->pos.r));
                                
                // SRL::Debug::Print(2, 14, "NumPlayers:%d", g_Game.currentNumPlayers);
                // SRL::Debug::Print(2, 15, "RoundOver:%d", g_Game.isRoundOver);
                // SRL::Debug::Print(2, 16, "Winner:%d", g_Game.winner);
                // // SRL::Debug::Print(2, 17, "DelayTimer:%3d", g_Game.endDelayTimer);
                // SRL::Debug::Print(2, 17, "maxTeams:%i", g_Team.maxTeams);
                // SRL::Debug::Print(2, 18, "NumTeams:%i", g_Team.numTeams);
                
                // for(int8_t i = 0; i <= MAX_PLAYERS; i++)
                // {
                    // PPLAYER player = &g_Players[i];
                    // SRL::Debug::Print(2, 10+i, "p%i isPlaying:%i", i, player->isPlaying);
                // }
                // SRL::Debug::Print(2, 10, "Team1 Available:%i", g_Team.isAvailable[TEAM_1]);
                // SRL::Debug::Print(2, 11, "Team2 Available:%i", g_Team.isAvailable[TEAM_2]);
                // SRL::Debug::Print(2, 12, "Team3 Available:%i", g_Team.isAvailable[TEAM_3]);
                // SRL::Debug::Print(2, 13, "Team4 Available:%i", g_Team.isAvailable[TEAM_4]);
                
                // SRL::Debug::Print(22, 10, "Team1 Active:%i", g_Team.isActive[TEAM_1]);
                // SRL::Debug::Print(22, 11, "Team2 Active:%i", g_Team.isActive[TEAM_2]);
                // SRL::Debug::Print(22, 12, "Team3 Active:%i", g_Team.isActive[TEAM_3]);
                // SRL::Debug::Print(22, 13, "Team4 Active:%i", g_Team.isActive[TEAM_4]);   
                
                // // SRL::Debug::Print(2, 12, "TOUCHEDBY 1:%i", touchedBy[0].hasTouched);
                // // SRL::Debug::Print(2, 13, "TOUCHEDBY 2:%i", touchedBy[1].hasTouched);
                // // SRL::Debug::Print(2, 14, "TOUCHEDBY 3:%i", touchedBy[2].hasTouched);
                // // SRL::Debug::Print(2, 15, "TOUCHEDBY 4:%i", touchedBy[3].hasTouched);
                                                                 
                // if (g_Game.numPlayers == ONE_PLAYER)
                    // SRL::Debug::Print(2, 21, "ONE_PLAYER");
                // else if (g_Game.numPlayers == TWO_PLAYER)
                    // SRL::Debug::Print(2, 21, "TWO_PLAYER");
                // else if (g_Game.numPlayers == THREE_PLAYER)
                    // SRL::Debug::Print(2, 21, "THREE_PLAYER");
                // else
                    // SRL::Debug::Print(2, 21, "FOUR_PLAYER");
                // SRL::Debug::Print(2, 22, "NumTeams:%i", g_Team.numTeams);
                // break;
                
            case GAME_STATE_GAMEPLAY:
            {
            
                // SRL::Debug::Print(2, 8, "P1 CHAR CHOICE:%i", g_Players[0].character.choice);
                // SRL::Debug::Print(2, 9, "P1 SPRITE:%i", g_Players[0]._sprite->id);
                // // if (g_Game.isPaused == true) {
                    // // SRL::Debug::Print(2, 5, "PAUSECHOICE:%i", g_PauseChoice);
                // // }
                // SRL::Debug::Print(2, 5, "GAMEACTIVE:%i", g_Game.isActive);
                // SRL::Debug::Print(2, 6, "BALLACTIVE:%i", g_Game.isBallActive);
                // SRL::Debug::Print(2, 8, "curPos.DX:%i", g_Players[0].curPos.dx);
                // SRL::Debug::Print(2, 9, "curPos.DY:%i", g_Players[0].curPos.dy);
                
                // SRL::Debug::Print(2, 14, "NumPlayers:%d", g_Game.currentNumPlayers);
                // SRL::Debug::Print(2, 15, "RoundOver:%d", g_Game.isRoundOver);
                // SRL::Debug::Print(2, 16, "Winner:%d", g_Game.winner);
                // SRL::Debug::Print(2, 17, "DelayTimer:%3d", g_Game.endDelayTimer);
                // SRL::Debug::Print(2, 18, "NumTeams:%i", g_Team.numTeams);
                
                // SRL::Debug::Print(2, 10, "Ball.Vel.X:%3d", pixel_poppy.vel.x.As<int16_t>());
                // SRL::Debug::Print(2, 11, "Ball.Vel.Y:%3d", pixel_poppy.vel.y.As<int16_t>());
                // SRL::Debug::Print(2, 12, "Ball.Vel.Z:%3d", pixel_poppy.vel.z.As<int16_t>());
                // SRL::Debug::Print(22, 10, "Ball.Pos.X:%3d", pixel_poppy.pos.x.As<int16_t>());
                // SRL::Debug::Print(22, 11, "Ball.Pos.Y:%3d", pixel_poppy.pos.y.As<int16_t>());
                // Fxp RotZ = pixel_poppy.rot.z.ToDegrees();
                // SRL::Debug::Print(22, 12, "Ball.Rot.Z:%3d", RotZ.As<int16_t>());

                // // SRL::Debug::Print(22, 15, "BALL.COLLIDING:%i", pixel_poppy.isColliding);
                // // SRL::Debug::Print(2,  16, "P1.COLLIDING:%i", g_Players[0]._sprite->isColliding);
                // // SRL::Debug::Print(2,  17, "P1.LEFTSIDE:%i", g_Players[0].onLeftSide);
                // // SRL::Debug::Print(22, 16, "P2.COLLIDING:%i", g_Players[1]._sprite->isColliding);
                // // SRL::Debug::Print(22, 17, "P2.LEFTSIDE:%i", g_Players[1].onLeftSide);
                
                
                // // SRL::Debug::Print(2,  16, "P1.COLLIDING:%i", g_Players[0]._sprite->isColliding);
                // // SRL::Debug::Print(2,  17, "ITEM.COLLIDE:%i", g_item._sprite->isColliding);
                // // SRL::Debug::Print(2,  18, "ITEM.ID:%i", g_item.id);
                // // SRL::Debug::Print(2,  19, "ITEM.TIMER:%i", g_item.timer[0]);
                
                // // SRL::Debug::Print(22, 16, "EXPLODE_BOMB:%i", g_Game.explodeBomb);
                // // SRL::Debug::Print(22, 17, "SHROOM_ANGLE:%i", hslSprites.color[p_rangeShroom.lower].h);
                // // SRL::Debug::Print(22, 18, "VISIBLE:%i", g_item._sprite->visible);
                // // SRL::Debug::Print(22, 19, "TOTALLIVES:%i", (g_Players[0].totalLives * 2));
                // // SRL::Debug::Print(22, 20, "NUMLIVES:%i", g_Players[0].numLives);
                         
                // // if (g_Players[0].isPlaying && g_GameOptions.testCollision) {
                    // // SRL::Debug::Print(2, 11, "ISCOLLIDING:%i", g_Players[0]._sprite->isColliding);
                // // }
                // // if (g_Players[1].isPlaying && g_GameOptions.testCollision) {
                    // // SRL::Debug::Print(22, 11, "ISCOLLIDING:%i", g_Players[1]._sprite->isColliding);
                // // } 
                                         
                // // if (g_Players[0].isPlaying) {
                    // // SRL::Debug::Print(2, 16, "POWER:%i, %d", JO_FIXED_TO_INT(g_Players[0].power), g_Players[0].power);
                // // }
                // // if (g_Players[1].isPlaying) {
                    // // SRL::Debug::Print(20, 16, "POWER:%i, %d", JO_FIXED_TO_INT(g_Players[1].power), g_Players[1].power);
                // // }  
                      
                // if (g_Players[0].isPlaying) {
                    // SRL::Debug::Print(2, 12, "P1 SUBSTATE:%i", g_Players[0].subState);
                // }
                // if (g_Players[1].isPlaying) {
                    // SRL::Debug::Print(2, 13, "P2 SUBSTATE:%i", g_Players[1].subState);
                // }
                // if (g_Players[2].isPlaying) {
                    // SRL::Debug::Print(2, 14, "P3 SUBSTATE:%i", g_Players[2].subState);
                // }
                // if (g_Players[3].isPlaying) {
                    // SRL::Debug::Print(2, 15, "P4 SUBSTATE:%i", g_Players[3].subState);
                // }
                
                // if (g_Players[0].isPlaying) {
                    // SRL::Debug::Print(2, 17, "P1 OBJECTSTATE:%i", g_Players[0].objectState);
                // }
                // if (g_Players[1].isPlaying) {
                    // SRL::Debug::Print(2, 18, "P2 OBJECTSTATE:%i", g_Players[1].objectState);
                // }
                // if (g_Players[2].isPlaying) {
                    // SRL::Debug::Print(2, 19, "P3 OBJECTSTATE:%i", g_Players[2].objectState);
                // }
                // if (g_Players[3].isPlaying) {
                    // SRL::Debug::Print(2, 20, "P4 OBJECTSTATE:%i", g_Players[3].objectState);
                // }
                // if (g_Game.numPlayers == ONE_PLAYER)
                    // SRL::Debug::Print(2, 21, "NumPlayers:%i", 1);
                // else if (g_Game.numPlayers == TWO_PLAYER)
                    // SRL::Debug::Print(2, 21, "NumPlayers:%i", 2);
                // else if (g_Game.numPlayers == THREE_PLAYER)
                    // SRL::Debug::Print(2, 21, "NumPlayers:%i", 3);
                // else
                    // SRL::Debug::Print(2, 21, "NumPlayers:%i", g_Game.currentNumPlayers);
                
                // SRL::Debug::Print(2, 22, "NumTeams:%i", g_Team.numTeams);
                // // SRL::Debug::Print(2, 23, "PLAYERID:%i", g_Players[0].playerID);
                                                
                // SRL::Debug::Print(2, 10, "Team1 Available:%i", g_Team.isAvailable[TEAM_1]);
                // SRL::Debug::Print(2, 11, "Team2 Available:%i", g_Team.isAvailable[TEAM_2]);
                // SRL::Debug::Print(2, 12, "Team3 Available:%i", g_Team.isAvailable[TEAM_3]);
                // SRL::Debug::Print(2, 13, "Team4 Available:%i", g_Team.isAvailable[TEAM_4]);
                
                SRL::Debug::Print(22, 10, "Team1 Active:%i", g_Team.isActive[TEAM_1]);
                SRL::Debug::Print(22, 11, "Team2 Active:%i", g_Team.isActive[TEAM_2]);
                SRL::Debug::Print(22, 12, "Team3 Active:%i", g_Team.isActive[TEAM_3]);
                SRL::Debug::Print(22, 13, "Team4 Active:%i", g_Team.isActive[TEAM_4]);  
                
                // SRL::Debug::Print(22, 14, "P1 TeamChoice:%i", g_Players[0].teamChoice);
                // SRL::Debug::Print(22, 15, "P2 TeamChoice:%i", g_Players[1].teamChoice);
                
                // // SRL::Debug::Print(20, 10, "GAMEISACTIVE:%i", g_Game.isActive);
                // // SRL::Debug::Print(20, 11, "BEGINTIMER:%i", g_Game.BeginTimer);
                // // SRL::Debug::Print(20, 12, "ROUNDS:%i", g_Game.countofRounds);
                // // SRL::Debug::Print(20, 13, "STARTTIMER:%i", start_gameplay_timer);
                // // SRL::Debug::Print(20, 14, "ISBALLACTIVE:%i", g_Game.isBallActive);
                // // SRL::Debug::Print(20, 15, "ROUND_START:%i", round_start);
                
                // // SRL::Debug::Print(2, 12, "PLAYER1 RAD:%i", JO_FIXED_TO_INT(g_Players[0]._sprite->pos.r));
                // // SRL::Debug::Print(2, 13, "PLAYER1 RAD:%i", JO_FIXED_TO_INT(g_Players[1]._sprite->pos.r));
                // // SRL::Debug::Print(2, 14, "PLAYER1 RAD:%i", JO_FIXED_TO_INT(g_Players[2]._sprite->pos.r));
                // // SRL::Debug::Print(2, 15, "PLAYER1 RAD:%i", JO_FIXED_TO_INT(g_Players[3]._sprite->pos.r));
                
                // // SRL::Debug::Print(2, 12, "TOUCHEDBY 1:%i", touchedBy[0].hasTouched);
                // // SRL::Debug::Print(2, 13, "TOUCHEDBY 2:%i", touchedBy[1].hasTouched);
                // // SRL::Debug::Print(2, 14, "TOUCHEDBY 3:%i", touchedBy[2].hasTouched);
                // // SRL::Debug::Print(2, 15, "TOUCHEDBY 4:%i", touchedBy[3].hasTouched);
                                             
                // // SRL::Debug::Print(20, 12, "TOUCHCOUNT 1:%i", touchedBy[0].touchCount);
                // // SRL::Debug::Print(20, 13, "TOUCHCOUNT 2:%i", touchedBy[1].touchCount);
                // // SRL::Debug::Print(20, 14, "TOUCHCOUNT 3:%i", touchedBy[2].touchCount);
                // // SRL::Debug::Print(20, 15, "TOUCHCOUNT 4:%i", touchedBy[3].touchCount);
                                             
                
                break;
            }
                
            case GAME_STATE_CREDITS: // transition
                // SRL::Debug::Print(2, 6, "CreditsTimer:%i  ", credits.timer/60);
                // SRL::Debug::Print(2, 7, "display_timer:%i  ", credits.display_timer);
                // SRL::Debug::Print(2, 8, "delay_timer:%i  ", credits.delay_timer);
                // SRL::Debug::Print(2, 19, credits.fade_in ? "fade_in: TRUE " : "fade_in: FALSE ");
                // SRL::Debug::Print(2, 20, credits.fade_out ? "fade_out: TRUE " : "fade_out: FALSE ");
                // SRL::Debug::Print(2, 21, credits.display ? "display: TRUE " : "display: FALSE ");
                // SRL::Debug::Print(2, 22, "id:%d  ", credits.id);
                // SRL::Debug::Print(2, 23, "bg_id:%d  ", credits.bg_id);
                // SRL::Debug::Print(2, 24, "transparency_rate:%d  ", credits.transparency_rate);
                break;
                
            // case GAME_STATE_TRANSITION: // transition
                // SRL::Debug::Print(2, 5, "TRANSITIONTIMER:%i", g_Transition.timer/60);
                // break;
                
            default:
                return;
        }
}

void gameplayDebugText(void) {
    if (g_GameOptions.debug_display) {
        // SRL::Debug::Print(2, 5, "GAMEACTIVE:%i", g_Game.isActive);
        // SRL::Debug::Print(2, 6, "BALLACTIVE:%i", g_Game.isBallActive);
        // SRL::Debug::Print(2, 8, "CURPOS.DX:%i", g_Players[0].curPos.dx);
        // SRL::Debug::Print(2, 9, "CURPOS.DY:%i", g_Players[0].curPos.dy);

        // SRL::Debug::Print(22, 10, "NUMPLAYERS:%i", g_Game.currentNumPlayers);
        // SRL::Debug::Print(22, 11, "ROUNDOVER:%i", g_Game.isRoundOver);
        // SRL::Debug::Print(22, 12, "WINNER:%i", g_Game.winner);
        // SRL::Debug::Print(22, 13, "NUMTEAMS:%i", g_Team.numTeams+1);
        // SRL::Debug::Print(22, 10, "DOUPDATE1:%i", do_update_Goals[0]);
        // SRL::Debug::Print(22, 11, "DOUPDATE2:%i", do_update_Goals[1]);
        // SRL::Debug::Print(22, 12, "ANIMATEGOAL:%i", g_AnimateGoal);
        // SRL::Debug::Print(22, 13, "GOALID:%i", g_Game.goalID);
        // SRL::Debug::Print(22, 14, "PALETTE1:%i", update_palette_Goals[0]);
        // SRL::Debug::Print(22, 15, "PALETTE2:%i", update_palette_Goals[1]);

        // SRL::Debug::Print(4, 10, "P2 SUBSTATE:%i", g_Players[1].subState);
        // SRL::Debug::Print(4, 11, "P2 LIVES:%i", g_Players[1].numLives);
        // SRL::Debug::Print(4, 12, "P1 CONTINUES:%i", g_Players[0].score.continues);
        // SRL::Debug::Print(4, 10, "LASTTOUCHED:%i", lastTouchedBy);
        // SRL::Debug::Print(4, 11, "PREVIOUSTOUCH:%i", previouslyTouchedBy[0]);
        // SRL::Debug::Print(4, 12, "PREVIOUSTOUCH:%i", previouslyTouchedBy[1]);
        // SRL::Debug::Print(4, 13, "PREVIOUSTOUCH:%i", previouslyTouchedBy[2]);
        
        // SRL::Debug::Print(2, 10, "NUMPLAYERS:%i", g_Game.numPlayers);
        // SRL::Debug::Print(2, 11, "CURPLAYERS:%i", g_Game.currentNumPlayers);
        
                // if (g_Players[0].isPlaying) {
                    // SRL::Debug::Print(2, 12, "P1 SUBSTATE:%i", g_Players[0].subState);
                    // SRL::Debug::Print(20, 12, "P1 TEAMCHOICE:%i", g_Players[0].teamChoice);
                // }
                // if (g_Players[1].isPlaying) {
                    // SRL::Debug::Print(2, 13, "P2 SUBSTATE:%i", g_Players[1].subState);
                    // SRL::Debug::Print(20, 13, "P2 TEAMCHOICE:%i", g_Players[1].teamChoice);
                // }
                // if (g_Players[2].isPlaying) {
                    // SRL::Debug::Print(2, 14, "P3 SUBSTATE:%i", g_Players[2].subState);
                    // SRL::Debug::Print(20, 14, "P3 TEAMCHOICE:%i", g_Players[2].teamChoice);
                // }
                // if (g_Players[3].isPlaying) {
                    // SRL::Debug::Print(2, 15, "P4 SUBSTATE:%i", g_Players[3].subState);
                    // SRL::Debug::Print(20, 15, "P4 TEAMCHOICE:%i", g_Players[3].teamChoice);
                // }
        
        // SRL::Debug::Print(20, 18, "NUM.TEAMS:%i", g_Team.numTeams);
        // SRL::Debug::Print(20, 19, "MIN.TEAMS:%i", g_Team.minTeams);
        // SRL::Debug::Print(20, 20, "MAX.TEAMS:%i", g_Team.maxTeams);
    }
}