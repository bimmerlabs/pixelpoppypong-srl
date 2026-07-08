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
#include "../game/character_select.h"
#include "../game/credits.h"
#include "../game/name_entry.h"
#include "../game/gameplay_state.hpp"


const char *deviceName[] = { // only used for testing / this demo - not neccesary for using the Bup library
    "InternalMemory",
    "CartridgeMemory",
    "ExternalDevice"
};

const char *deviceStatus[] = { // only used for testing / this demo - not neccesary for using the Bup library
        "Success",
        "Failed",
        "Unformatted",
        "WriteProtected",
        "NotEnoughMemory",
        "NotFound",
        "Found",
        "NoMatch",
        "Broken"
};
            
const char *roundState[] = {
        "CharacterSelect",
        "Playing",
        "NextRound",
        "ShowMessage",
        "ShowResult",
        "Ending",
        "Transition"
};

void debux_text(void)
{
    if (!g_GameOptions.debug_display) {
        return;
    }
        SRL::Debug::Print(2, 2, "GameState:%2d", g_Game.gameState);
        SRL::Debug::Print(18, 2, "Last:%2d", g_Game.lastState);
        SRL::Debug::Print(29, 2, "Next:%2d", g_Game.nextState);
        // SRL::Debug::Print(2, 3, "Frame:%3d", g_Game.frame);
        // SRL::Debug::Print(2, 4, "MasterVolume:%3d", g_Audio.masterVolume);
        // SRL::Debug::Print(2, 5, "cdIsPlaying:%d", g_Audio.cdIsPlaying);
        SRL::Debug::Print(20, 3, "Sprites:%d    ", SRL::VDP1::GetTextureCount());
        SRL::Debug::Print(20, 4, "VDP1 Memory:%06d", SRL::VDP1::GetAvailableMemory());
        SRL::Debug::Print(20, 5, "HWRAM free space:%06d", SRL::Memory::HighWorkRam::GetFreeSpace());
        SRL::Debug::Print(20, 6, "HWRAM used space:%06d", SRL::Memory::HighWorkRam::GetUsedSpace());
        
        // SRL::Debug::Print(2, 11, "isBoss:%d", g_Game.isBoss);
        // SRL::Debug::Print(2, 12, "countofRounds:%d", g_Game.countofRounds);
        // PPLAYER computer = &g_Players[1];
        // SRL::Debug::Print(2, 13, "computer->isAI:%d", computer->isAI);
        
        // for (int i = 0; i < CHARACTER_MAX; i++)
        // {
            // SRL::Debug::Print(2, 10 + i, "char:%d avail:%d finished:%d", 
                // i, g_StoryProgress.available[i], g_StoryProgress.finished[i]);
        // }
                
        // SRL::Debug::Print(2, 6, "coreAssetsLoaded:%d", g_Assets.coreAssetsLoaded);
        // SRL::Debug::Print(2, 7, "titleAssetsLoaded:%d", g_Assets.titleAssetsLoaded);
        // SRL::Debug::Print(2, 8, "characterAssetsLoaded:%d", g_Assets.characterAssetsLoaded);
        // SRL::Debug::Print(2, 9, "NameEntryAssetsLoaded:%d", g_Assets.NameEntryAssetsLoaded);
        // SRL::Debug::Print(2, 10, "GameplayAssetsLoaded:%d", g_Assets.GameplayAssetsLoaded);
        
        // for(uint8_t i = 0; i < MAX_INPUTS; i++)
        // {
            // SRL::Debug::Print(2, 11+i, "Inp%2d Id:%3d isSelected:%2d", i+1, g_Inputs[i].id, g_Inputs[i].isSelected);
        // }

        // for (int i = 0; i <= g_Game.maxPlayers; i++) {
            // SRL::Debug::Print(2, 23+i, "P%d Input:%3d isSelected:%2d", i+1, g_Players[i].input->id, g_Players[i].input->isSelected);
        // }
        
        // SRL::Debug::Print(20, 3, "GameMode:%d", g_Game.gameMode);
        // SRL::Debug::Print(20, 4, "Difficulty:%d", g_Game.gameDifficulty);
        
        // DateTime time = DateTime::Now();
        // SRL::Debug::Print(2, 26, "Date:%d.%d.%d    ", time.Day(), time.Month(), time.Year());
        // SRL::Debug::Print(2, 27, "Time:%02d:%02d:%02d", time.Hour(), time.Minute(), time.Second());        
        
        // SRL::Debug::Print(20, 3, "Season:%2d", g_Game.timeSeason);
        // SRL::Debug::Print(20, 4, "Month:%2d, %2d", time.Month(), OCTOBER);
        
        // SRL::Debug::Print(20, 5, "AllIn/Out:%d,%d", g_Transition.all_in, g_Transition.all_out);
        // SRL::Debug::Print(20, 6, "FadeIn/Out:%d,%d", g_Transition.fade_in, g_Transition.fade_out);
        // SRL::Debug::Print(20, 7, "MosaicIn/Out:%d,%d", g_Transition.mosaic_in, g_Transition.mosaic_out);
        // SRL::Debug::Print(20, 8, "MusicIn/Out:%d,%d", g_Transition.music_in, g_Transition.music_out);
        // SRL::Debug::Print(2, 5, "cdIsPlaying:%d", g_Audio.cdIsPlaying);
        // SRL::Debug::Print(2, 5, "AttractScreen:%d", g_AttractScreen.id);
        
        // SRL::Debug::Print(2, 5, "numPlayers:%d", g_Game.numPlayers);
        
        
        // PPLAYER player = &g_Players[0];       
        // SRL::Debug::Print(2, 8, "inputID:%2d ",  player->input->id);
        // SRL::Debug::Print(2, 9, "isSelected:%d", player->input->isSelected);
        // SRL::Debug::Print(2, 10, "isAnalog:%d", input->isAnalog);
        // SRL::Debug::Print(2, 11, "axis_x:%d    ", input->axis_x.As<int32_t>());
        // SRL::Debug::Print(2, 12, "axis_y:%d    ", input->axis_y.As<int32_t>());
        // SRL::Debug::Print(2, 13, "left_trigger:%d    ", input->left_trigger.As<int32_t>());
        // SRL::Debug::Print(2, 14, "right_trigger:%d    ", input->right_trigger.As<int32_t>());
        // SRL::Debug::Print(2, 15, "sensitivity:%d    ", input->sensitivity.As<int32_t>());

        /* backup */
        // SRL::Debug::Print(2,12, is_cart_mem_available() 
            // ? "Cart Backup Memory Detected" : "Cart Backup Memory Not Detected");
        // SRL::Debug::Print(2,13, is_internal_mem_available() 
            // ? "Internal Backup Memory Detected" : "Internal Backup Memory Not Detected");
        // SRL::Debug::Print(2,14, currentDevice 
            // ? "CartridgeDevice" : "InternalDevice");            
        // // SRL::Debug::Print(2, 10, "Backup Memory Init: %d", bup->Initialized);
        // SRL::Debug::Print(2, 10, "LibrarySpace:     0x%08X", bup->LibrarySpace);
        // SRL::Debug::Print(2, 11, "WorkSpace:        0x%08X", bup->WorkSpace);        
            // SRL::Debug::Print(1, 12, "%s:", deviceName[currentDevice]);
            // SRL::Debug::Print(2, 13, "partition: %d", bup->BupConfig[currentDevice].partition);
            // SRL::Debug::Print(2, 14, "Status (%d): %s", bup->BupState[currentDevice].Status, deviceStatus[bup->BupState[currentDevice].Status]);
            // SRL::Debug::Print(2, 15, bup->BupState[currentDevice].isMounted ? "Mounted: True" : "Mounted: False");
            // SRL::Debug::Print(2, 16, "BupStatusTable:");
            // SRL::Debug::Print(3, 17, "TotalSize %d", bup->BupState[currentDevice].StatTable.TotalSize);
            // SRL::Debug::Print(3, 18, "TotalBlocks %d", bup->BupState[currentDevice].StatTable.TotalBlocks);
            // SRL::Debug::Print(3, 19, "BlockSize %d", bup->BupState[currentDevice].StatTable.BlockSize);
            // SRL::Debug::Print(3, 20, "FreeSize %d", bup->BupState[currentDevice].StatTable.FreeSize);
            // SRL::Debug::Print(3, 21, "FreeBlocks %d", bup->BupState[currentDevice].StatTable.FreeBlocks);
            // SRL::Debug::Print(3, 22, "WritableCount %d", bup->BupState[currentDevice].StatTable.WritableCount);
        
        /* font */
        // SRL::Debug::Print(2, 13, " !\"#$%&'()*+,-./");
        // SRL::Debug::Print(2, 14, "0123456789:;<=>?");
        // SRL::Debug::Print(2, 15, "@ABCDEFGHIJKLMNO");
        // SRL::Debug::Print(2, 16, "PQRSTUVWXYZ[\\]^_");
        // SRL::Debug::Print(2, 17, "`abcdefghijklmo");
        // SRL::Debug::Print(2, 18, "pqrstuvwxyz{|}~\177");
        
                // for(int8_t i = 0; i < MAX_PLAYERS; i++)
                // {
                    // PPLAYER player = &g_Players[i];
                    // SRL::Debug::Print(2, 10+i, "p%d isPlaying:%d", i, player->isPlaying);
                // }
                // for(int8_t i = 0; i < MAX_PLAYERS; i++)
                // {
                    // PPLAYER player = &g_Players[i];
                    // SRL::Debug::Print(2, 14+i, "p%d isActivated:%d", i, player->isActivated);
                // }
                // for(int8_t i = 0; i < MAX_PLAYERS; i++)
                // {
                    // PPLAYER player = &g_Players[i];
                    // SRL::Debug::Print(2, 18+i, "p%d isDead:%d", i, player->isDead);
                // }
        
        switch (g_Game.gameState) {
            case GAME_STATE_PPP_LOGO: // logo
                // SRL::Debug::Print(2, 6, "LogoTimer:%2d", g_LogoTimer/60);                
                break;
                
            case GAME_STATE_TITLE_SCREEN: // title
                // SRL::Debug::Print(2, 6, "TitleTimer:%2d", titleScreen.timer/60);
                // SRL::Debug::Print(2, 6, "LOGO1.SPR_ID:%d", logo1.id);
                // SRL::Debug::Print(2, 7, "LOGO2.SPR_ID:%d", logo2.id);
                
                // SRL::Debug::Print(2, 7, "LOGO1_POS:%d", logo1_pos);
                // SRL::Debug::Print(20, 7, "LOGO1:%d", logo1.pos.y);
                // SRL::Debug::Print(2, 8, "LOGO2_POS:%d", logo2_pos);
                // SRL::Debug::Print(20, 8, "LOGO2:%d", logo2.pos.y);
                // SRL::Debug::Print(20, 10, "VELOCITY:%d", logo_velocity);
                // SRL::Debug::Print(20, 11, "LOGO_FALLING:%d", logo_falling);
                // SRL::Debug::Print(20, 12, "LOGO_BOUNCE:%d", logo_bounce);
                break;      
                          
            case GAME_STATE_NAME_ENTRY: // title
                // SRL::Debug::Print(2, 6, "nameEntry.timer:%2d", nameEntry.timer/60);
                break;
                
            case GAME_STATE_TITLE_MENU: // menu
                // SRL::Debug::Print(2, 6, "GameMode:%d", g_Game.gameMode);
                // SRL::Debug::Print(2, 7, "GameDifficulty:%d", g_Game.gameDifficulty);
                SRL::Debug::Print(2, 8, "menuChoice:%d", titleScreen.menuChoice);
                SRL::Debug::Print(2, 9, "menuLastChoice:%d", titleScreen.menuLastChoice);
                // SRL::Debug::Print(2, 7, "LOGO1_POS:%d", logo1_pos);
                // SRL::Debug::Print(20, 7, "LOGO1:%d", logo1.pos.y);
                // SRL::Debug::Print(2, 8, "LOGO2_POS:%d", logo2_pos);
                // SRL::Debug::Print(20, 8, "LOGO2:%d", logo2.pos.y);
                // SRL::Debug::Print(20, 9, "VELOCITY:%d", logo_velocity);
                // SRL::Debug::Print(20, 11, "LOGO_FALLING:%d", logo_falling);
                // SRL::Debug::Print(20, 12, "LOGO_BOUNCE:%d", logo_bounce);
                // SRL::Debug::Print(2, 18, "NUM.PLAYERS:%d", g_Game.numPlayers);
                // SRL::Debug::Print(2, 19, "MIN.PLAYERS:%d", g_Game.minPlayers);
                // SRL::Debug::Print(2, 20, "MAX.PLAYERS:%d", g_Game.maxPlayers);
                // SRL::Debug::Print(20, 18, "NUM.TEAMS:%d", g_Team.numTeams);
                // SRL::Debug::Print(20, 19, "MIN.TEAMS:%d", g_Team.minTeams);
                // SRL::Debug::Print(2, 11, "MaxTeams:%d", g_Team.maxTeams);
                break;
                
            // case GAME_STATE_TITLE_OPTIONS: // menu
                // SRL::Debug::Print(2, 5, "GAMEMODE:%d", g_Game.gameMode);
                // SRL::Debug::Print(2, 6, "OPTION CHOICE:%d", g_OptionScreenChoice);
                // break;
                
            case GAME_STATE_CHARACTER_SELECT: 
                // SRL::Debug::Print(2, 8, "pressedLeft:%d", characterSelect.pressedLeft);
                // SRL::Debug::Print(2, 9, "pressedRight:%d", characterSelect.pressedRight);
                // SRL::Debug::Print(2, 10, "Rad:X=%3d", characterSelect.xRadius.As<int32_t>());
                // SRL::Debug::Print(2, 11, "Rad:Y=%3d", characterSelect.yRadius.As<int32_t>());
                // SRL::Debug::Print(2, 12, "Pos:X=%3d", light.x.As<int32_t>());
                // SRL::Debug::Print(2, 13, "Pos:Y=%3d", light.y.As<int32_t>());
                // SRL::Debug::Print(2, 10, "inputSelected:%d", player->input->isSelected);
                // SRL::Debug::Print(2, 11, "startSelection:%d", player->startSelection);
                // SRL::Debug::Print(2, 12, "spr_id:%2d", characterSelect.spr_id);
                SRL::Debug::Print(2, 14, "Angle:%3d", characterSelect.angle);
                SRL::Debug::Print(2, 15, "character.choice:%2d", g_Players[0].character.choice);
                // SRL::Debug::Print(2, 15, "sprID:%3d", characterSelect.spr_id);
                SRL::Debug::Print(2, 16, "characterSelect.end:%d", characterSelect.end);
                SRL::Debug::Print(2, 17, "selection:%d", characterSelect.selection);
                SRL::Debug::Print(2, 18, "isAngleSnapped:%d", characterSelect.isAngleSnapped);
                SRL::Debug::Print(2, 19, "finished:%d", characterSelect.finished);
                SRL::Debug::Print(2, 20, "characterSelect.start:%d", characterSelect.start);
                SRL::Debug::Print(2, 21, "characterSelect.snapEnd:%d", characterSelect.snapEnd);
                
                // for (int i = 0; i < CHARACTER_MAX; i++) {
                    // SRL::Debug::Print(2, (8+i), "Unlocked:%d", characterUnlocked[i]);
                // }
                // for (int i = 0; i < CHARACTER_MAX; i++) {
                    // SRL::Debug::Print(20, (8+i), "Available:%d", characterAvailable[i]);
                // }
                break;
                              
            case GAME_STATE_TEAM_SELECT: // menu
                // SRL::Debug::Print(2, 5, "GAMEMODE:%d", g_Game.gameMode);
                
                // SRL::Debug::Print(2, 8, "NUMPLAYERS:%d", g_Game.currentNumPlayers);
                // SRL::Debug::Print(2, 9, "NUMTEAMS:%d", g_Team.numTeams);
                
                // for (int i = 0; i < CHARACTER_MAX; i++) {
                    // SRL::Debug::Print(2, (8+i), "Unlocked:%d", characterUnlocked[i]);
                // }
                // for (int i = 0; i < CHARACTER_MAX; i++) {
                    // SRL::Debug::Print(20, (8+i), "Available:%d", characterAvailable[i]);
                // }
                
                // for(uint8_t i = 0; i < MAX_INPUTS; i++)
                // {
                    // SRL::Debug::Print(2, 11+i, "Inp%2d Id:%3d isSelected:%2d", i+1, g_Inputs[i].id, g_Inputs[i].isSelected);
                // }
                
                // for (int i = 0; i <= g_Game.maxPlayers; i++) {
                    // SRL::Debug::Print(2, 23+i, "P%d Input:%3d isSelected:%2d", i+1, g_Players[i].input->id, g_Players[i].input->isSelected);
                // }
                
                // SRL::Debug::Print(2, 10, "TEAM 1 AVAILABLE:%d", g_Team.isAvailable[TEAM_1]);
                // SRL::Debug::Print(2, 11, "TEAM 2 AVAILABLE:%d", g_Team.isAvailable[TEAM_2]);
                // SRL::Debug::Print(2, 12, "TEAM 3 AVAILABLE:%d", g_Team.isAvailable[TEAM_3]);
                // SRL::Debug::Print(2, 13, "TEAM 4 AVAILABLE:%d", g_Team.isAvailable[TEAM_4]);
                
                // SRL::Debug::Print(2, 7, "CHARACTER_MAX:%d",  CHARACTER_MAX);
                // SRL::Debug::Print(2, 24, "P1 CHAR CHOICE:%3d ", g_Players[0].character.choice);
                // SRL::Debug::Print(2, 25, "P1 SPRITE:%3d", g_Players[0]._sprite->id);
                
                // SRL::Debug::Print(20, 7, "P1 STARTSELECT:%d",  g_Players[0].startSelection);
                // SRL::Debug::Print(20, 8, "P1 CHAR SELECT:%d", g_Players[0].character.selected);
                // SRL::Debug::Print(20, 9, "P1 TEAM SELECT:%d", g_Players[0].teamSelected);
                
                // SRL::Debug::Print(2, 10, "P1 TeamChoice:%d ", g_Players[0].teamChoice);
                // SRL::Debug::Print(2, 11, "MaxTeams:%d ", g_Team.maxTeams);
                
                // SRL::Debug::Print(20, 11, "P1 READY:%d", g_Players[0].isReady);
                
                // // SRL::Debug::Print(2, 13, "P2 STARTSELECT:%d",  g_Players[1].startSelection);
                // // SRL::Debug::Print(2, 14, "P2 CHAR SELECT:%d", g_Players[1].character.selected);
                // // SRL::Debug::Print(2, 15, "P2 TEAM SELECT:%d", g_Players[1].teamSelected);
                // // SRL::Debug::Print(2, 16, "P2 TEAM CHOICE:%d", g_Players[1].teamChoice);
                // // SRL::Debug::Print(2, 17, "P2 READY:%d", g_Players[1].isReady);
                
                // // SRL::Debug::Print(20, 7, "P3 STARTSELECT:%d",  g_Players[2].startSelection);
                // // SRL::Debug::Print(20, 8, "P3 CHAR SELECT:%d", g_Players[2].character.selected);
                // // SRL::Debug::Print(20, 9, "P3 TEAM SELECT:%d", g_Players[2].teamSelected);
                // // SRL::Debug::Print(20, 10, "P3 TEAM CHOICE:%d", g_Players[2].teamChoice);
                // // SRL::Debug::Print(20, 11, "P3 READY:%d", g_Players[2].isReady);
                
                // // SRL::Debug::Print(20, 13, "P4 STARTSELECT:%d",  g_Players[3].startSelection);
                // // SRL::Debug::Print(20, 14, "P4 CHAR SELECT:%d", g_Players[3].character.selected);
                // // SRL::Debug::Print(20, 15, "P4 TEAM SELECT:%d", g_Players[3].teamSelected);
                // // SRL::Debug::Print(20, 16, "P4 TEAM CHOICE:%d", g_Players[3].teamChoice);
                // // SRL::Debug::Print(20, 17, "P4 READY:%d", g_Players[3].isReady);
                
                
                // SRL::Debug::Print(2, 18, "NUM.TEAMS %d:", g_Team.numTeams);
                // SRL::Debug::Print(2, 19, "MIN.TEAMS %d:", g_Team.minTeams);
                // SRL::Debug::Print(2, 20, "MAX.TEAMS %d:", g_Team.maxTeams);
                // // SRL::Debug::Print(2, 19, "ALL READY:%d", all_players_ready);
                // // SRL::Debug::Print(2, 20, "PRESSEDSTART:%d",  g_TeamSelectPressedStart);
                
                break;
                
            case GAME_STATE_DEMO_LOOP:
                // SRL::Debug::Print(2, 5, "GAMEACTIVE:%d", g_Game.isActive);
                // SRL::Debug::Print(2, 6, "BALLACTIVE:%d", g_Game.isBallActive);
                // // SRL::Debug::Print(2, 5, "DEMOTIMER:%d", g_DemoTimer/60);
                // // SRL::Debug::Print(2, 8, "MACCHI.X:%d", macchi.pos.x);
                // // SRL::Debug::Print(2, 9, "MACCHI.Y:%d", macchi.pos.y);
                // // SRL::Debug::Print(2, 10, "COLLIDING:%d", macchi.isColliding);
                // // SRL::Debug::Print(2, 11, "JELLY.X:%d", jelly.pos.x);
                // // SRL::Debug::Print(2, 12, "JELLY.Y:%d", jelly.pos.y);
                // // SRL::Debug::Print(2, 13, "COLLIDING:%d", jelly.isColliding);
                // // SRL::Debug::Print(20, 8, "POPPY.X:%d", pixel_poppy.pos.x);
                // // SRL::Debug::Print(20, 9, "POPPY.Y:%d", pixel_poppy.pos.y);
                
                // SRL::Debug::Print(20, 12, "PlayerColliding:%d",  g_Players[0]._sprite->isColliding);
                // SRL::Debug::Print(20, 13, "BallColliding:%d", pixel_poppy.isColliding);
                
                // // SRL::Debug::Print(2, 12, "PLAYER1 RAD:%d", JO_FIXED_TO_INT(g_Players[0]._sprite->pos.r));
                // // SRL::Debug::Print(2, 13, "PLAYER1 RAD:%d", JO_FIXED_TO_INT(g_Players[1]._sprite->pos.r));
                // // SRL::Debug::Print(2, 14, "PLAYER1 RAD:%d", JO_FIXED_TO_INT(g_Players[2]._sprite->pos.r));
                // // SRL::Debug::Print(2, 15, "PLAYER1 RAD:%d", JO_FIXED_TO_INT(g_Players[3]._sprite->pos.r));
                                
                // SRL::Debug::Print(2, 14, "NumPlayers:%d", g_Game.currentNumPlayers);
                // SRL::Debug::Print(2, 15, "RoundOver:%d", g_Game.isRoundOver);
                // SRL::Debug::Print(2, 16, "Winner:%d", g_Game.winner);
                // // SRL::Debug::Print(2, 17, "DelayTimer:%3d", g_Game.endDelayTimer);
                // SRL::Debug::Print(2, 17, "maxTeams:%d", g_Team.maxTeams);
                // SRL::Debug::Print(2, 18, "NumTeams:%d", g_Team.numTeams);
                
                // for(int8_t i = 0; i <= MAX_PLAYERS; i++)
                // {
                    // PPLAYER player = &g_Players[i];
                    // SRL::Debug::Print(2, 10+i, "p%d isPlaying:%d", i, player->isPlaying);
                // }
                // SRL::Debug::Print(2, 10, "Team1 Available:%d", g_Team.isAvailable[TEAM_1]);
                // SRL::Debug::Print(2, 11, "Team2 Available:%d", g_Team.isAvailable[TEAM_2]);
                // SRL::Debug::Print(2, 12, "Team3 Available:%d", g_Team.isAvailable[TEAM_3]);
                // SRL::Debug::Print(2, 13, "Team4 Available:%d", g_Team.isAvailable[TEAM_4]);
                
                // SRL::Debug::Print(22, 10, "Team1 Active:%d", g_Team.isActive[TEAM_1]);
                // SRL::Debug::Print(22, 11, "Team2 Active:%d", g_Team.isActive[TEAM_2]);
                // SRL::Debug::Print(22, 12, "Team3 Active:%d", g_Team.isActive[TEAM_3]);
                // SRL::Debug::Print(22, 13, "Team4 Active:%d", g_Team.isActive[TEAM_4]);   
                
                // // SRL::Debug::Print(2, 12, "TOUCHEDBY 1:%d", touchedBy[0].hasTouched);
                // // SRL::Debug::Print(2, 13, "TOUCHEDBY 2:%d", touchedBy[1].hasTouched);
                // // SRL::Debug::Print(2, 14, "TOUCHEDBY 3:%d", touchedBy[2].hasTouched);
                // // SRL::Debug::Print(2, 15, "TOUCHEDBY 4:%d", touchedBy[3].hasTouched);
                                                                 
                // if (g_Game.numPlayers == ONE_PLAYER)
                    // SRL::Debug::Print(2, 21, "ONE_PLAYER");
                // else if (g_Game.numPlayers == TWO_PLAYER)
                    // SRL::Debug::Print(2, 21, "TWO_PLAYER");
                // else if (g_Game.numPlayers == THREE_PLAYER)
                    // SRL::Debug::Print(2, 21, "THREE_PLAYER");
                // else
                    // SRL::Debug::Print(2, 21, "FOUR_PLAYER");
                // SRL::Debug::Print(2, 22, "NumTeams:%d", g_Team.numTeams);
                break;
                
            case GAME_STATE_GAMEPLAY:
            {
                // for (int i = 0; i < CHARACTER_MAX; i++) {
                    // SRL::Debug::Print(2, (8+i), "Unlocked:%d", characterUnlocked[i]);
                // }
                // for (int i = 0; i < CHARACTER_MAX; i++) {
                    // SRL::Debug::Print(20, (8+i), "Available:%d", characterAvailable[i]);
                // }
                // for (int i = 0; i < 4; i++) {
                    // SRL::Debug::Print(2, 21+i, "P%d Character:%d", i, g_Players[i].character.choice);
                // }
                // SRL::Debug::Print(2, 25, "Rounds:%d", g_Game.countofRounds);
                
                // SRL::Debug::Print(2, 8,  "P1 score.points:%d", g_Players[0].score.points);
                // SRL::Debug::Print(2, 9,  "P1 score.stars:%d", g_Players[0].score.stars);
                // SRL::Debug::Print(2, 10, "P1 score.continues:%d", g_Players[0].score.continues);
                
                // SRL::Debug::Print(2, 12, "P2 numLives:%d", g_Players[1].numLives);
                // SRL::Debug::Print(2, 13, "P2 score.points:%d", g_Players[1].score.points);
                // SRL::Debug::Print(2, 14, "P2 score.stars:%d", g_Players[1].score.stars);
                // SRL::Debug::Print(2, 15, "P2 score.continues:%d", g_Players[1].score.continues);
                // SRL::Debug::Print(2, 16, "P2 character.choice:%d", g_Players[1].character.choice);
                
                // SRL::Debug::Print(2, 18, "endDelayTimer:%d", g_Game.endDelayTimer);
                // SRL::Debug::Print(2, 19, "currentNumPlayers:%d", g_Game.currentNumPlayers);
                
                SRL::Debug::Print(2, 8, "Winner:%2d", Gameplay::g_GameState.winner);
                SRL::Debug::Print(2, 9, "endDelayTimer:%2d", Gameplay::g_GameState.endDelayTimer);
                SRL::Debug::Print(2, 10, "timeOver:%d", Gameplay::g_GameState.timeOver);
                SRL::Debug::Print(2, 11, "roundState:%s", roundState[Gameplay::g_GameState.roundState]);
                SRL::Debug::Print(2, 12, "GameOverTimer:%2d", Gameplay::g_GameState.GameOverTimer);
                SRL::Debug::Print(2, 13, "gameOverSndPlayed:%d", Gameplay::g_GameState.gameOverSndPlayed);
                SRL::Debug::Print(2, 15, "textFramesRemaining:%3d", g_item.textFramesRemaining);
                
                // SRL::Debug::Print(2, 8, "isBoss:%d", g_Game.isBoss);
                // // SRL::Debug::Print(2, 9, "initialLives:%d", g_BossState.initialLives);
                // SRL::Debug::Print(2, 10, "emitFramesRemaining:%d", g_BossState.emitFramesRemaining);
                // SRL::Debug::Print(2, 11, "phase1Triggered:%d", g_BossState.phase1Triggered);
                // SRL::Debug::Print(2, 12, "phase2Triggered:%d", g_BossState.phase2Triggered);
                // SRL::Debug::Print(2, 13, "phase3Triggered:%d", g_BossState.phase3Triggered);
                        
                // SRL::Debug::Print(2, 10, "countofRounds:%d", g_Game.countofRounds);
                // SRL::Debug::Print(2, 11, "isBoss:%d", g_Game.isBoss);
                // SRL::Debug::Print(2, 12, "gameMode:%2d", g_Game.gameMode);
                
                // if (g_Game.gameMode == GAME_MODE_STORY)
                // {
                    // SRL::Debug::Print(2, 13, "AI Character:%2d", g_Players[1].character.choice);                    
                // }
                
                // SRL::Debug::Print(2, 10, "P2 isBig:  %d", g_Players[1].isBig);
                // SRL::Debug::Print(2, 11, "P2 isSmall:%d", g_Players[1].isSmall);
                
                // // SRL::Debug::Print(2, 8, "P1 CHAR CHOICE:%d", g_Players[0].character.choice);
                // SRL::Debug::Print(2, 9, "P1 SPRITE:%d", g_Players[0]._sprite->id);
                // // if (g_Game.isPaused == true) {
                    // // SRL::Debug::Print(2, 5, "PAUSECHOICE:%d", g_PauseChoice);
                // // }
                // SRL::Debug::Print(2, 5, "GAMEACTIVE:%d", g_Game.isActive);
                // SRL::Debug::Print(2, 6, "BALLACTIVE:%d", g_Game.isBallActive);
                // SRL::Debug::Print(2, 8, "curPos.DX:%d", g_Players[0].curPos.dx);
                // SRL::Debug::Print(2, 9, "curPos.DY:%d", g_Players[0].curPos.dy);
                
                // SRL::Debug::Print(2, 14, "NumPlayers:%d", g_Game.currentNumPlayers);
                // SRL::Debug::Print(2, 15, "RoundOver:%d", g_Game.isRoundOver);
                // SRL::Debug::Print(2, 16, "Winner:%d", g_Game.winner);
                // SRL::Debug::Print(2, 17, "DelayTimer:%3d", g_Game.endDelayTimer);
                // SRL::Debug::Print(2, 18, "NumTeams:%d", g_Team.numTeams);
                
                // SRL::Debug::Print(2, 10, "Ball.Vel.X:%3d", pixel_poppy.vel.x.As<int16_t>());
                // SRL::Debug::Print(2, 11, "Ball.Vel.Y:%3d", pixel_poppy.vel.y.As<int16_t>());
                // SRL::Debug::Print(2, 12, "Ball.Vel.Z:%3d", pixel_poppy.vel.z.As<int16_t>());
                // SRL::Debug::Print(22, 10, "Ball.Pos.X:%3d", pixel_poppy.pos.x.As<int16_t>());
                // SRL::Debug::Print(22, 11, "Ball.Pos.Y:%3d", pixel_poppy.pos.y.As<int16_t>());
                // Fxp RotZ = pixel_poppy.rot.z.ToDegrees();
                // SRL::Debug::Print(22, 12, "Ball.Rot.Z:%3d", RotZ.As<int16_t>());

                // SRL::Debug::Print(22, 15, "BallColliding:%d", pixel_poppy.isColliding);
                // // SRL::Debug::Print(2,  16, "P1.COLLIDING:%d", g_Players[0]._sprite->isColliding);
                // // SRL::Debug::Print(2,  17, "P1.LEFTSIDE:%d", g_Players[0].onLeftSide);
                // // SRL::Debug::Print(22, 16, "P2.COLLIDING:%d", g_Players[1]._sprite->isColliding);
                // // SRL::Debug::Print(22, 17, "P2.LEFTSIDE:%d", g_Players[1].onLeftSide);
                
                
                // // SRL::Debug::Print(2,  16, "P1.COLLIDING:%d", g_Players[0]._sprite->isColliding);
                // // SRL::Debug::Print(2,  17, "ITEM.COLLIDE:%d", g_item._sprite->isColliding);
                // // SRL::Debug::Print(2,  18, "ITEM.ID:%d", g_item.id);
                // // SRL::Debug::Print(2,  19, "ITEM.TIMER:%d", g_item.timer[0]);
                
                // // SRL::Debug::Print(22, 16, "EXPLODE_BOMB:%d", g_Game.explodeBomb);
                // // SRL::Debug::Print(22, 17, "SHROOM_ANGLE:%d", hslSprites.color[p_rangeShroom.lower].h);
                // // SRL::Debug::Print(22, 18, "VISIBLE:%d", g_item._sprite->active);
                // // SRL::Debug::Print(22, 19, "TOTALLIVES:%d", (g_Players[0].totalLives * 2));
                // // SRL::Debug::Print(22, 20, "NUMLIVES:%d", g_Players[0].numLives);
                         
                // // if (g_Players[0].isPlaying && g_GameOptions.testCollision) {
                    // // SRL::Debug::Print(2, 11, "ISCOLLIDING:%d", g_Players[0]._sprite->isColliding);
                // // }
                // // if (g_Players[1].isPlaying && g_GameOptions.testCollision) {
                    // // SRL::Debug::Print(22, 11, "ISCOLLIDING:%d", g_Players[1]._sprite->isColliding);
                // // } 
                                         
                // // if (g_Players[0].isPlaying) {
                    // // SRL::Debug::Print(2, 16, "POWER:%d, %d", JO_FIXED_TO_INT(g_Players[0].power), g_Players[0].power);
                // // }
                // // if (g_Players[1].isPlaying) {
                    // // SRL::Debug::Print(20, 16, "POWER:%d, %d", JO_FIXED_TO_INT(g_Players[1].power), g_Players[1].power);
                // // }  
                      
                // if (g_Players[0].isPlaying) {
                    // SRL::Debug::Print(2, 12, "P1 SUBSTATE:%d", g_Players[0].subState);
                // }
                // if (g_Players[1].isPlaying) {
                    // SRL::Debug::Print(2, 13, "P2 SUBSTATE:%d", g_Players[1].subState);
                // }
                // if (g_Players[2].isPlaying) {
                    // SRL::Debug::Print(2, 14, "P3 SUBSTATE:%d", g_Players[2].subState);
                // }
                // if (g_Players[3].isPlaying) {
                    // SRL::Debug::Print(2, 15, "P4 SUBSTATE:%d", g_Players[3].subState);
                // }
                
                // if (g_Players[0].isPlaying) {
                    // SRL::Debug::Print(2, 17, "P1 OBJECTSTATE:%d", g_Players[0].objectState);
                // }
                // if (g_Players[1].isPlaying) {
                    // SRL::Debug::Print(2, 18, "P2 OBJECTSTATE:%d", g_Players[1].objectState);
                // }
                // if (g_Players[2].isPlaying) {
                    // SRL::Debug::Print(2, 19, "P3 OBJECTSTATE:%d", g_Players[2].objectState);
                // }
                // if (g_Players[3].isPlaying) {
                    // SRL::Debug::Print(2, 20, "P4 OBJECTSTATE:%d", g_Players[3].objectState);
                // }
                // if (g_Game.numPlayers == ONE_PLAYER)
                    // SRL::Debug::Print(2, 21, "NumPlayers:%d", 1);
                // else if (g_Game.numPlayers == TWO_PLAYER)
                    // SRL::Debug::Print(2, 21, "NumPlayers:%d", 2);
                // else if (g_Game.numPlayers == THREE_PLAYER)
                    // SRL::Debug::Print(2, 21, "NumPlayers:%d", 3);
                // else
                    // SRL::Debug::Print(2, 21, "NumPlayers:%d", g_Game.currentNumPlayers);
                
                // SRL::Debug::Print(2, 22, "NumTeams:%d", g_Team.numTeams);
                // // SRL::Debug::Print(2, 23, "PLAYERID:%d", g_Players[0].playerID);
                                                
                // SRL::Debug::Print(2, 10, "Team1 Available:%d", g_Team.isAvailable[TEAM_1]);
                // SRL::Debug::Print(2, 11, "Team2 Available:%d", g_Team.isAvailable[TEAM_2]);
                // SRL::Debug::Print(2, 12, "Team3 Available:%d", g_Team.isAvailable[TEAM_3]);
                // SRL::Debug::Print(2, 13, "Team4 Available:%d", g_Team.isAvailable[TEAM_4]);
                
                // SRL::Debug::Print(22, 10, "Team1 Active:%d", g_Team.isActive[TEAM_1]);
                // SRL::Debug::Print(22, 11, "Team2 Active:%d", g_Team.isActive[TEAM_2]);
                // SRL::Debug::Print(22, 12, "Team3 Active:%d", g_Team.isActive[TEAM_3]);
                // SRL::Debug::Print(22, 13, "Team4 Active:%d", g_Team.isActive[TEAM_4]);  
                
                // SRL::Debug::Print(22, 14, "P1 TeamChoice:%d", g_Players[0].teamChoice);
                // SRL::Debug::Print(22, 15, "P2 TeamChoice:%d", g_Players[1].teamChoice);
                
                // SRL::Debug::Print(20, 13, "isGameActive:%d", g_Game.isActive);
                // // SRL::Debug::Print(20, 11, "BEGINTIMER:%d", g_Game.BeginTimer);
                // // SRL::Debug::Print(20, 12, "ROUNDS:%d", g_Game.countofRounds);
                // // SRL::Debug::Print(20, 13, "STARTTIMER:%d", start_gameplay_timer);
                // SRL::Debug::Print(20, 14, "IsBallActive:%d", g_Game.isBallActive);
                // // SRL::Debug::Print(20, 15, "ROUND_START:%d", round_start);
                
                // // SRL::Debug::Print(2, 12, "PLAYER1 RAD:%d", JO_FIXED_TO_INT(g_Players[0]._sprite->pos.r));
                // // SRL::Debug::Print(2, 13, "PLAYER1 RAD:%d", JO_FIXED_TO_INT(g_Players[1]._sprite->pos.r));
                // // SRL::Debug::Print(2, 14, "PLAYER1 RAD:%d", JO_FIXED_TO_INT(g_Players[2]._sprite->pos.r));
                // // SRL::Debug::Print(2, 15, "PLAYER1 RAD:%d", JO_FIXED_TO_INT(g_Players[3]._sprite->pos.r));
                
                // // SRL::Debug::Print(2, 12, "TOUCHEDBY 1:%d", touchedBy[0].hasTouched);
                // // SRL::Debug::Print(2, 13, "TOUCHEDBY 2:%d", touchedBy[1].hasTouched);
                // // SRL::Debug::Print(2, 14, "TOUCHEDBY 3:%d", touchedBy[2].hasTouched);
                // // SRL::Debug::Print(2, 15, "TOUCHEDBY 4:%d", touchedBy[3].hasTouched);
                                             
                // // SRL::Debug::Print(20, 12, "TOUCHCOUNT 1:%d", touchedBy[0].touchCount);
                // // SRL::Debug::Print(20, 13, "TOUCHCOUNT 2:%d", touchedBy[1].touchCount);
                // // SRL::Debug::Print(20, 14, "TOUCHCOUNT 3:%d", touchedBy[2].touchCount);
                // // SRL::Debug::Print(20, 15, "TOUCHCOUNT 4:%d", touchedBy[3].touchCount);
                                             
                
                break;
            }
                
            case GAME_STATE_CREDITS: // transition
                // SRL::Debug::Print(2, 6, "CreditsTimer:%d  ", credits.timer/60);
                // SRL::Debug::Print(2, 7, "display_timer:%d  ", credits.display_timer);
                // SRL::Debug::Print(2, 8, "delay_timer:%d  ", credits.delay_timer);
                // SRL::Debug::Print(2, 19, credits.fade_in ? "fade_in: TRUE " : "fade_in: FALSE ");
                // SRL::Debug::Print(2, 20, credits.fade_out ? "fade_out: TRUE " : "fade_out: FALSE ");
                // SRL::Debug::Print(2, 21, credits.display ? "display: TRUE " : "display: FALSE ");
                // SRL::Debug::Print(2, 22, "id:%d  ", credits.id);
                // SRL::Debug::Print(2, 23, "bg_id:%d  ", credits.bg_id);
                // SRL::Debug::Print(2, 24, "transparency_rate:%d  ", credits.transparency_rate);
                break;
                
            // case GAME_STATE_TRANSITION: // transition
                // SRL::Debug::Print(2, 5, "TRANSITIONTIMER:%d", g_Transition.timer/60);
                // break;
                
            default:
                return;
        }
}
