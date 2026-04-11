#include "../main.h"
#include "storymode.h"
#include "../core/assets.h"
#include "../core/screen_transition.h"
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
    g_StartStoryFrames = CHARACTER_SELECT_TIMER;

    initTeams();
    g_Game.currentNumPlayers = 2;              
    player->teamChoice = TEAM_1;
    player->teamSelected = true;
    g_Team.isAvailable[player->teamChoice] = false;
    g_Team.numTeams = ONE_TEAM;
    
    set_spr_position_fxp(player->_cursor[0], Fxp_0, Fxp_0, CURSOR_DEPTH);
    set_spr_position_fxp(player->_cursor[1], Fxp(46), Fxp_0, CURSOR_DEPTH);
    player->isActivated = true;
    player->isDead = false;
    player->isPlaying = true;
    player->isAI = false;
    boundPlayer(player);
    draw_story_cursor = false;
    
    initStoryCharacters();
    initVsModePlayers();
    resetPawScale();
        
    g_Transition.fade_in = true;
    SRL::Debug::PrintClearScreen();
}

void initContinue(void) {
    PPLAYER player = &g_Players[0];
    PPLAYER computer = &g_Players[1];
    
    setGameTimer();
    player->numLives = getLives(player);
    computer->numLives = getLives(computer);
    player->isDead = false;
    computer->isDead = false;
    player->score.points = 0;
    computer->score.points = 0;
    player->score.stars = 0;
    computer->score.stars = 0;
    g_Game.endDelayTimer = GAME_END_DELAY_TIMEOUT;
    g_Game.currentNumPlayers = 2;
    initVsModePlayers();
    resetTeamState();

    initPixelPoppy();
    g_Gameplay.start_gameplay_timer = false;
    g_Gameplay.round_start = false;
    g_Game.isBallActive = false;
    g_Game.isActive = false;
    g_Game.BeginTimer = 0;
    g_Game.winner = -2;
    initTouchCounter(1);

    boundPlayer(player);
    boundPlayer(computer);
    g_StartStoryFrames = CHARACTER_SELECT_TIMER;
    g_Game.selectStoryCharacter = true;
    reset_sprites(); // doesn't do anything yet
    initGoalColors();
    g_Game.time_over = false;
    g_Game.isRoundOver = false;
    
    playCDTrack(BEGIN_GAME_TRACK, false);
    
    SRL::Debug::PrintClearScreen();
}

void initNextRound(void) {
    PPLAYER player = &g_Players[0];
    PPLAYER computer = &g_Players[1];
    
    setGameTimer();
    computer->numLives = getLives(computer);
    player->score.points = 0;
    computer->score.points = 0;
    player->score.stars = 0;
    computer->score.stars = 0;
    computer->score.continues = 0;
    g_Game.endDelayTimer = GAME_END_DELAY_TIMEOUT;
    g_Game.currentNumPlayers = 2;
    nextStoryCharacter();
    sprite_frame_reset(&pixel_poppy);
    g_StartStoryFrames = CHARACTER_SELECT_TIMER;
    g_Game.selectStoryCharacter = true;
    reset_sprites(); // doesn't do anything yet // ??
    initGoalColors();
    
    g_Game.time_over = false;
    g_Game.isRoundOver = false;
    g_Game.winner = -2;
    
    playCDTrack(BEGIN_GAME_TRACK, false);
    
    SRL::VDP2::NBG2::ScrollDisable(); // zzz
    
    SRL::Debug::PrintClearScreen();
}

// main logic loop
void storySelectUpdate(void)
{
    PPLAYER player = &g_Players[0];
    PPLAYER computer = &g_Players[1];
    
    character_offset = ((g_Game.countofRounds) * CHARACTER_POS_OFFSET);
    SRL::Debug::Print(6, 10, "%s", characterNames[player->character.choice]);
    SRL::Debug::Print(26, 14, "%s", characterNames[computer->character.choice]); // needs updated
    
        character_portrait.id = character_portrait.anim[0].asset + player->character.choice;
        set_spr_position_fxp(&character_portrait, Fxp(-200), Fxp_0, PORTRAIT_DEPTH);
        set_spr_scale(&character_portrait, 2.0, 2.0);
        my_sprite_draw(&character_portrait);
        
    // scroll up list of characters
    if (character_pos_selected < character_offset) {
        character_pos_selected++;
    }
    else {
        SRL::Debug::Print(2, 19, "%s", characterQuotes[player->character.choice]);
        SRL::Debug::Print(21, 19, "vs.");
        SRL::Debug::Print(26, 16, "%s", characterQuotes[computer->character.choice]); // needs updated
    }
    if (g_StartStoryFrames == 0)
    {
        g_Game.roundBeginTimer = ROUND_BEGIN_TIME_FAST;
        g_Game.dropBallTimer = DROP_BALL_TIME_FAST;
        g_Transition.all_in = true;
        if (g_GameOptions.mosaic_display) {
            g_Transition.mosaic_in = true;
        }
        g_Transition.fade_in = true;
        // g_Transition.story_fade_in = true;
        g_Game.selectStoryCharacter = false;
        SRL::Debug::PrintClearScreen();
        if (g_Game.isBoss) {
            playCDTrack(BOSS_TRACK, true);
        }
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
    SRL::Debug::Print(10, 12, "Round Score:%09d", player->score.points);
    SRL::Debug::Print(10, 14, "Total Score:%09d", player->score.total);
    if (g_Game.countofRounds < MAX_ROUNDS) {
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
    if (g_Game.endDelayTimer < LIFE_COUNT_DELAY_TIMEOUT && g_Game.countofRounds < MAX_ROUNDS) {
        unsigned int millions = player->score.total / 1000000;
        if (millions > player->score.lastMillion) {
            unsigned int livesToAdd = millions - player->score.lastMillion;
            for (unsigned int i = 0; i < livesToAdd; i++) {
                if (player->numLives < player->totalLives * 2) {
                    player->numLives += 1;
                }
            }
            player->score.lastMillion = millions;      
        }
    }
    // additional time;
    if (g_Game.endDelayTimer < LIFE_COUNT_DELAY_TIMEOUT && g_Game.countofRounds < MAX_ROUNDS) {
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
        SRL::Debug::Print(14, 18, "Extra Time:%d ", addedTime);
    }
    if (g_Game.endDelayTimer == LIFE_COUNT_DELAY_TIMEOUT && g_Game.countofRounds < MAX_ROUNDS) {
        Pcm::Play(Sounds.Core[StartSnd]);
        SRL::Debug::PrintClearScreen();
    }  
    else if (g_Game.endDelayTimer == WIN_GAME_DELAY_TIMEOUT && g_Game.countofRounds == MAX_ROUNDS) {
        Pcm::Play(Sounds.Game[WinSnd]);
        SRL::Debug::PrintClearScreen();
    }  

    if (player->score.points > 0) {
        Pcm::Play(Sounds.Game[ScoreTotalSnd]);
        player->score.points--;
        player->score.total++;
    } 
    else {
        g_Game.endDelayTimer--;
    }
}