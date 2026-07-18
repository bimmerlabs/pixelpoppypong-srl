#include "../main.h"
#include "storymode.h"
#include "ai.h"
#include "gameplay_state.hpp"
#include "../core/assets.h"
#include "../core/screen_transition.h"
#include "../core/vdp1print.h"
#include "../objects/player.h"
#include "../objects/characters.h"
#include "../vdp2/nbg1.h"

int character_pos_x = CHARACTER_POS_X;
int character_pos_y = 0;
int character_pos_selected = CHARACTER_POS_Y;
int character_offset = 0;
int g_StartStoryFrames = 0;
bool draw_story_cursor = false;

void initStoryMode(void)
{
    PPLAYER player = &g_Players[0];
    
    g_Game.selectStoryCharacter = true;
    character_pos_selected = CHARACTER_POS_Y;
    character_offset = (g_Game.countofRounds * CHARACTER_POS_OFFSET); // starts as 0
    
    menu_bg2.mesh = MESHoff;
    menu_bg2.zmode = _ZmCC;
    menu_bg2.id = menu_bg2.anim[0].asset + 4;
    set_spr_position_fxp(&menu_bg2, Fxp_0, Fxp_0, MENU_BG2_DEPTH);
    set_spr_scale(&menu_bg2, 54, 352);
    
    g_Game.countofRounds = 0;
    g_StartStoryFrames = STORY_MODE_TIMER;

    initTeams();
    g_Game.currentNumPlayers = 2;              
    player->teamChoice = TEAM_1;
    player->teamSelected = true;
    g_Team.isAvailable[player->teamChoice] = false;
    g_Team.numTeams = ONE_TEAM;
    
    set_spr_position(player->_cursor[0], character_pos_x, 0, 80);
    set_spr_position(player->_cursor[1], (character_pos_x + 46), 0, 80);
    player->isActivated = true;
    player->isDead = false;
    player->isPlaying = true;
    player->isAI = false;
    boundPlayer(player);
    draw_story_cursor = false;
    
    initBossQuotes();
    initStoryCharacters();
    initVsModePlayers();
    resetPawScale();
    
    init_nbg2_img();
    SRL::VDP2::NBG2::ScrollEnable();
    
    SRL::Debug::PrintClearScreen();    
}

void initContinue(void) {
    PPLAYER player = &g_Players[0];
    PPLAYER computer = &g_Players[1];
    
    player->numLives = getLives(player);
    
    player->isDead = false;
    computer->isDead = false;
    
    g_Gameplay.start_gameplay_timer = false;
    g_Gameplay.round_start = false;
    g_Game.isBallActive = false;
    g_Game.isActive = false;
    g_Game.BeginTimer = 0;
    
    initTouchCounter(1);

    boundPlayer(player);
    boundPlayer(computer);
}

void initNextRound(void) {
    PPLAYER player = &g_Players[0];
    PPLAYER computer = &g_Players[1];
    
    initPixelPoppy();
    setGameTimer();
    player->score.points = 0;
    computer->score.points = 0;
    player->score.stars = 0;
    computer->score.stars = 0;
    computer->score.continues = 0;
    Gameplay::g_GameState.endDelayTimer = Gameplay::GAME_END_DELAY_TIMEOUT;
    Gameplay::g_GameState.GameOverTimer = Gameplay::GAME_OVER_DELAY_TIMEOUT;
    
    g_Game.currentNumPlayers = 2;
    nextStoryCharacter();

    sprite_frame_reset(&pixel_poppy);
    g_StartStoryFrames = STORY_MODE_TIMER;
    g_Game.selectStoryCharacter = true;
    reset_sprites(); // doesn't do anything yet // ??
    initGoalColors();
    
    Gameplay::g_GameState.timeOver = false;
    g_Game.isRoundOver = false;
    Gameplay::g_GameState.winner = -2;
    
    init_nbg2_img();
    SRL::VDP2::NBG2::ScrollEnable();
    
    SRL::Debug::PrintClearScreen();    
}

// main logic loop
void storySelectUpdate(void)
{    
    
    PPLAYER player = &g_Players[0];
    PPLAYER computer = &g_Players[1];
    
    // SRL::Debug::Print(2, 9, "g_StartStoryFrames:%3d", g_StartStoryFrames);
    
    character_offset = ((g_Game.countofRounds) * CHARACTER_POS_OFFSET);
    
    // player 1 portrait
    character_portrait.id = character_portrait.anim[0].asset + player->character.choice;
    set_spr_position_fxp(&character_portrait, -256, 0, PORTRAIT_DEPTH);
    set_spr_scale(&character_portrait, 2.0, 2.0);
    character_portrait.mesh = MESHoff;
    my_sprite_draw(&character_portrait);
        
    // scroll up list of characters
    if (character_pos_selected < character_offset) {
        character_pos_selected++;
    }
    if (g_StartStoryFrames == 0)
    {
        SRL::Debug::PrintClearScreen();
        g_Game.roundBeginTimer = ROUND_BEGIN_TIME_FAST;
        g_Game.dropBallTimer = DROP_BALL_TIME_FAST;
        
        g_Transition.all_in = true;
        g_Transition.fade_in = true;
        
        g_Game.selectStoryCharacter = false;
        
        if (g_Game.isBoss) { // if I want this to play constantly, I need to check if it's already playing or something
            playCDTrack(BOSS_TRACK, true);
        }
        
        
        SRL::VDP2::NBG2::ScrollDisable();
        init_nbg2_img();
        
        Gameplay::SetRoundState(Gameplay::ROUND_STATE_PLAYING);
    }
    
    if (g_Game.frame % 3 == 0) { // modulus
        draw_story_cursor = !draw_story_cursor;
    }
    if (draw_story_cursor) {
        player->_cursor[0]->mesh = MESHon;
        player->_cursor[1]->mesh = MESHon;
    }
    else {
        player->_cursor[0]->mesh = MESHoff;
        player->_cursor[1]->mesh = MESHoff;
    }
    drawCharacterList();
    
    if (!g_GameOptions.debug_display && Gameplay::g_GameState.roundState != Gameplay::ROUND_STATE_PLAYING) {
        uint8_t playerid   = player->character.choice;
        uint8_t computerid = computer->character.choice;
        
        int32_t xpos = -40;
        int32_t zpos = 50;
        const int32_t offset = 24;
        const int32_t space = 28;
        
        DrawSpriteText(&font, fullCharacterNames[playerid],   xpos, -126, zpos, offset, space);     
        DrawSpriteText(&font, fullCharacterNames[computerid], xpos,  66, zpos, offset, space);     
        DrawSpriteText(&font, "V.S.", xpos+70, 0, zpos, offset, space);
        
        PrintWrapped(20, 8, 23, Dialog::quotes[playerid][computerid].player1);
        PrintWrapped(20, 20, 23, Dialog::quotes[playerid][computerid].player2);
    }
    
    g_StartStoryFrames--;
    
    if (attrNbg1.x_scroll > Fxp_0) {
        attrNbg1.x_pos += attrNbg1.x_scroll;
        if (attrNbg1.x_pos > Fxp(512.0))
            attrNbg1.x_pos = Fxp_0;
    }
    slScrPosNbg1(attrNbg1.x_pos.RawValue(), attrNbg1.y_pos.RawValue());   
}

void tallyScore(void) {
    PPLAYER player = &g_Players[0];
    
    unsigned int thresholds[] = {100000, 10000, 1000, 50, 1};
    if (!g_GameOptions.debug_display) {
        SRL::Debug::Print(10, 12, "Round Score:%09d", player->score.points);
        SRL::Debug::Print(10, 14, "Total Score:%09d", player->score.total);
    }
    if (!allOpponentsBeaten()) {
        draw_heart_element(&heart, player, -64, 24, 16);
    }
    
    for (uint8_t i = 0; i < 5; i++) {
        unsigned int threshold = thresholds[i];
        if (player->score.points > threshold) {
            Pcm::Play(Sounds.Game[ScoreAddSnd]);
            player->score.points -= threshold;
            player->score.total += threshold;
            return;
        }
    }
    // additional lives    
    if (Gameplay::g_GameState.endDelayTimer < Gameplay::LIFE_COUNT_DELAY_TIMEOUT && !allOpponentsBeaten()) {
        unsigned int millions = player->score.total / 1000000; // change to only give extra life if the current score is over 1 million?
        if (millions > player->score.lastMillion) {
            unsigned int livesToAdd = millions - player->score.lastMillion;
            for (unsigned int i = 0; i < livesToAdd; i++) {
                if (player->numLives < player->totalLives * 2) {
                    player->numLives += 1;
                }
            }
            player->score.lastMillion += millions;      
        }
    }
    // additional time;
    if (Gameplay::g_GameState.endDelayTimer < Gameplay::LIFE_COUNT_DELAY_TIMEOUT && !allOpponentsBeaten()) {
        uint16_t addedTime = 0;
        switch(g_Game.gameDifficulty)
        {
            case GAME_DIFFICULTY_EASY:
                addedTime = 30;
                break;
            case GAME_DIFFICULTY_MEDIUM:
                addedTime = 20;
                break;
            case GAME_DIFFICULTY_HARD:
                addedTime = 10;
                break;
            default:
                break;
        }
        if (touchedBy[0].touchCount > addedTime) {
            addedTime = touchedBy[0].touchCount;     
        }
        if (!g_GameOptions.debug_display) {
            SRL::Debug::Print(14, 18, "Extra Time:%d ", addedTime);
        }
    }
    if (Gameplay::g_GameState.endDelayTimer == Gameplay::LIFE_COUNT_DELAY_TIMEOUT && !allOpponentsBeaten()) {
        Pcm::Play(Sounds.Core[StartSnd]);
        SRL::Debug::PrintClearScreen();
    }  
    else if (Gameplay::g_GameState.endDelayTimer == Gameplay::WIN_GAME_DELAY_TIMEOUT && allOpponentsBeaten()) {
        Pcm::Play(Sounds.Game[WinSnd]);
        SRL::Debug::PrintClearScreen();
    }  

    if (player->score.points > 0) {
        Pcm::Play(Sounds.Game[ScoreTotalSnd]);
        player->score.points--;
        player->score.total++;
    } 
    else {
        Gameplay::g_GameState.endDelayTimer--;
    }
}

void drawCharacterList(void)
{
    PPLAYER player = &g_Players[0];
    PPLAYER computer = &g_Players[1];
    
    my_sprite_draw(player->_cursor[0]);
    my_sprite_draw(player->_cursor[1]);
    character_pos_y = character_pos_selected;

    // first pass - find the next opponent (first available unfinished character)
    for (uint8_t i = 0; i < CHARACTER_MAX; i++)
    {
        if (!g_StoryProgress.available[i])
            continue;
        if (!g_StoryProgress.finished[i])
        {
            computer->character.choice = i;
            if (character_pos_selected >= character_offset && !Gameplay::g_GameState.spriteAssigned)
            {
                computer->character.choice = i;
                
                auto getBossCharacter = [](CHARACTER_SELECT playerChoice) -> CHARACTER_SELECT
                {
                    switch (playerChoice)
                    {
                        case CHARACTER_WUPPY:   return CHARACTER_WALRUS;
                        case CHARACTER_WALRUS:  return CHARACTER_GARF;
                        case CHARACTER_GARF:    return CHARACTER_NONE;
                        case CHARACTER_NONE:    return CHARACTER_GARF;  // both walrus and garf are bosses
                        default:                return CHARACTER_WUPPY; // normal character
                    }
                };

                CHARACTER_SELECT bossChar = getBossCharacter((CHARACTER_SELECT)g_Players[0].character.choice);
                
                if (g_GameOptions.bossMode)
                {
                    g_Game.isBoss = true;
                }
                else
                {
                    g_Game.isBoss = ((CHARACTER_SELECT)i == bossChar) ||
                                    (g_Players[0].character.choice == CHARACTER_NONE && 
                                    ((CHARACTER_SELECT)i == CHARACTER_WALRUS || 
                                     (CHARACTER_SELECT)i == CHARACTER_GARF));
                }
                
                if (g_Game.isBoss)
                {
                    g_BossState.phase1Triggered = false;
                    g_BossState.phase2Triggered = false;
                    g_BossState.phase3Triggered = false;
                }
                
                computer->numLives = getLives(computer);
                
                assignCharacterSprite(computer);
                assignCharacterStats(computer);
                computer->_sprite->flip = sprHflip;
                computer->onLeftSide = false;
                computer->goalCenterThresholdMax = LARGE_GOAL_THRESHOLD_MAX;
                computer->goalCenterThresholdMin = LARGE_GOAL_THRESHOLD_MIN;
                set_spr_position(computer->_sprite, PLAYER_X, 0, PLAYER_DEPTH);
                computer->shield_pos = -SHIELD_OFFSET;
                shield[1].flip = sprHflip;
                Gameplay::g_GameState.spriteAssigned = true;
            }
            break;  // stop after finding the first unfinished character
        }
    }

    // second pass - draw entire available roster
    for (uint8_t i = 0; i < CHARACTER_MAX; i++)
    {
        if (!g_StoryProgress.available[i])
            continue;
        character_portrait.id = character_portrait.anim[0].asset + i;
        set_spr_position(&character_portrait, character_pos_x , character_pos_y, 90);
        set_spr_scale(&character_portrait, 2.0, 2.0);
        
        if (computer->character.choice == i)
        {
            character_portrait.mesh = MESHoff;
        }
        else
        {
            character_portrait.mesh = MESHon; // causes mesh effect to stick after this loop ends.  hack is to force it off in drawGameUI()
        }
        
        my_sprite_draw(&character_portrait);
        character_pos_y -= CHARACTER_POS_OFFSET;
    }
}

// helper function - returns true if all available opponents have been beaten
bool allOpponentsBeaten(void)
{
    for (int i = 0; i < CHARACTER_MAX; i++)
    {
        if (g_StoryProgress.available[i] && !g_StoryProgress.finished[i])
            return false;
    }
    return true;
}