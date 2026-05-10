#include "player.h"
#include "../main.h"
#include "../core/sprites.h"
#include "../core/backup.h"
#include "../core/screen_transition.h"
#include "../game/gameplay.h"
#include "../game/storymode.h"
#include "../game/AI.h"
#include "../game/physics.h"
#include "../game/player_setup.h"
#include "../game/gameplay_state.hpp"
#include "../vdp2/sprite_colors.h"

PLAYER g_Players[MAX_PLAYERS] = {};

StoryProgressData g_StoryProgress = {};

void resetPlayerScores(void)
{
    initTouchCounter(1);
    for(unsigned int i = 0; i < MAX_PLAYERS; i++)
    {
        PPLAYER player = &g_Players[i];
        player->shield.power = SHIELD_POWER;
        player->score.stars  = 0;
        player->score.continues = 0;
        player->score.total  = 0;
        player->score.points = 0;
        player->score.lastMillion = 0;
        player->totalLives = getLives(player);
        player->numLives = player->totalLives;
        assignCharacterSprite(player);
        set_spr_scale(&shield[i], 2, 2);
        player->isBig = false;
        player->isSmall = false;
        player->shroomFrames = SHROOM_TIMER;
    }
}

void resetPlayerAttacks(void)
{
    for(unsigned int i = 0; i < MAX_PLAYERS; i++)
    {
        PPLAYER player = &g_Players[i];

        player->shield.activate = false;
        if (!player->isBig && !player->isSmall)
        {
            player->_sprite->pos.r = PLAYER_RADIUS;
        }
        sprite_frame_reset(&shield[i]);
        player->isExploded = false;
        
        if (player->attack1) {
            if (player->onLeftSide) {
                player->_sprite->pos.x -= ATTACK1;
            }
            else {
                player->_sprite->pos.x += ATTACK1;
            }
            player->attack1 = false;
            player->attack1Frames = 0;
        }
        if (player->attack2) {
            if (player->onLeftSide) {
                player->_sprite->pos.x -= ATTACK2;
            }
            else {
                player->_sprite->pos.x += ATTACK2;
            }
            player->attack2 = false;
            player->attack2Frames = 0;
        }
        
    }
}

int getLives(PPLAYER player)
{
    int numLives = 0;
    switch(g_Game.gameMode)
    {
        case GAME_MODE_BATTLE:
            numLives = 9;
            // numLives = 3;
            break;
        case GAME_MODE_CLASSIC:
            switch(g_Game.gameDifficulty)
            {
                case GAME_DIFFICULTY_EASY:
                    numLives = 4;
                    break;
                case GAME_DIFFICULTY_MEDIUM:
                    numLives = 6;
                    // numLives = 1;
                    break;
                case GAME_DIFFICULTY_HARD:
                    numLives = 9;
                    break;
                default:
                    break;
            }
            break;
        default:
            // story mode
            if (player->isAI) {
                switch(g_Game.gameDifficulty)
                {
                    case GAME_DIFFICULTY_EASY:
                        numLives = 4;
                        // numLives = 1;
                        break;
                    case GAME_DIFFICULTY_MEDIUM:
                        numLives = 6;
                        // numLives = 1;
                        break;
                    case GAME_DIFFICULTY_HARD:
                        numLives = 6;
                        if (g_Game.isBoss)
                        {
                            numLives += 1;
                        }
                        break;
                    default:
                        break;
                }
                if (g_Game.isBoss)
                {
                    numLives += 1;
                }
            }
            else {
                switch(g_Game.gameDifficulty)
                {
                    case GAME_DIFFICULTY_EASY:
                        numLives = 6;
                        // numLives = 1;
                        break;
                    case GAME_DIFFICULTY_MEDIUM:
                        numLives = 6;
                        // numLives = 1;
                        break;
                    case GAME_DIFFICULTY_HARD:
                        numLives = 4;
                        break;
                    default:
                        break;
                }
            }
            break;
    }
    return numLives;
}

int getStars(void)
{
    int numStars = 0;
    switch(g_Game.gameMode)
    {
        case GAME_MODE_CLASSIC:
            numStars = 1;
            break;
        case GAME_MODE_STORY: {
            switch(g_Game.gameDifficulty)
            {
                case GAME_DIFFICULTY_EASY:
                    numStars = 1;
                    break;
                case GAME_DIFFICULTY_MEDIUM:
                    numStars = 1;
                    break;
                case GAME_DIFFICULTY_HARD:
                    numStars = 2;
                    break;
                default:
                    break;
            }
            break;
        }
        case GAME_MODE_BATTLE:
            switch(g_Game.gameDifficulty)
            {
                case GAME_DIFFICULTY_EASY:
                    numStars = 1;
                    break;
                case GAME_DIFFICULTY_MEDIUM:
                    numStars = 1;
                    break;
                case GAME_DIFFICULTY_HARD:
                    numStars = 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return numStars;
}

void getContinues(void)
{
    if (g_Game.gameMode != GAME_MODE_STORY) {
        return;
    }
    switch(g_Game.gameDifficulty)
    {
        case GAME_DIFFICULTY_EASY:
            g_Players[0].score.continues = 3;
            break;
        case GAME_DIFFICULTY_MEDIUM:
            g_Players[0].score.continues = 2;
            break;
        case GAME_DIFFICULTY_HARD:
            g_Players[0].score.continues = 1;
            break;
        default:
            break;
    }
}

void initPlayers(bool resetInputs)
{    
    for(int8_t i = 0; i < MAX_PLAYERS; i++)
    {
        PPLAYER player = &g_Players[i];
        
        player->playerID = i;
        
        if (resetInputs)
            player->input = nullptr;
        
        player->score.continues = 0;
        player->score.points = 0;
        player->score.total = 0;
        player->score.lastMillion = 0;

        // PLAYER      
        player->startSelection = false;
        player->pressedStart = false;
        player->isReady = false;
        player->pressedB = false; // get rid of this?
        player->isPlaying = false;
        player->isActivated = true;
        player->isDead = false;
        player->scored = false;
        player->isAI = false;
        player->isExploded = false;
        player->onLeftSide = false;
        
        // GAMEPLAY
        player->numLives = 9;
        
        // CHARACTER
        player->character.choice = CHARACTER_NONE;
        player->character.selected = false;
        player->maxSpeed = Fxp_0;
        player->acceleration = Fxp_0;
        player->basePower = Fxp_0;
        player->power = Fxp_0;
        
        // TEAM
        player->teamChoice = TEAM_COUNT;
        player->teamSelected = false;
        
        player->moveHorizontal = false;
        player->moveVertical = false;
        
        // SPRITES
        // assign cursor & bg tile to each player
        player->_cursor[0] = &player_cursor1;
        player->_cursor[0]->id = player->_cursor[0]->anim[0].asset + i;
        player->_cursor[1] = &player_cursor2;
        player->_cursor[1]->id = player->_cursor[1]->anim[0].asset + i;
        
        player->_bg = &player_bg;
        player->_bg->scl.y = PLAYER_BG_Y;
        player->_bg->zmode = _ZmLC;
        assignCharacterSprite(player);

        player->_sprite->isColliding = false;
        
        // cursors
        if (i == 1) {
            hsl_incSprites[HSL_CURSOR].h -= 90;
        }
        else if (i == 2) {
            hsl_incSprites[HSL_CURSOR].h -= 180;
        }
        else if (i == 3) {
            hsl_incSprites[HSL_CURSOR].h -= 270;
        }
        if (i > 0)
        {
            update_palette_Pmenu[i] = update_sprites_color(&p_rangePmenu[i], HSL_CURSOR);
        }
        
        // INPUTS
        player->curPos.dx = Fxp_0;
        player->_sprite->vel.x = Fxp_0;
        player->curPos.dy = Fxp_0;
        player->_sprite->vel.y = Fxp_0;
        
        player->attack1 = false;
        player->attack2 = false;
        player->attack1Frames = 0;
        player->attack2Frames = 0;
        
        player->shield.activate = false;
        
        player->_portrait = &character_portrait;
        player->_portrait->id = player->_portrait->anim[0].asset + CHARACTER_NONE;
        set_spr_scale(player->_portrait, 2, 2);
        
        player->isBig = false;
        player->isSmall = false;
        player->shroomFrames = SHROOM_TIMER;
    }
}

void initAiPlayers(void)
{    
    for(unsigned short i = 0; i < g_Team.maxTeams; i++) // max players instead of teams?
    {
        PPLAYER computer = &g_Players[i];
        if (computer->isPlaying) {
            continue;
        }
        
        computer->teamChoice = TEAM_1;
        validateTeam(computer);
        g_Team.isAvailable[computer->teamChoice] = false;
        g_Team.isActive[computer->teamChoice] = true;
        g_Team.numTeams++;
        g_Game.currentNumPlayers++;
        
        computer->_bg->id = computer->_bg->anim[0].asset + i;
        computer->character.choice = rnd.GetNumber(CHARACTER_MACCHI, CHARACTER_GARF);
        validateCharacters(computer);
        characterAvailable[computer->character.choice] = false;
                        
        assignCharacterSprite(computer);        
        assignCharacterStats(computer);
        
        player_bg.mesh = MESHoff;
        
        computer->shield.activate = false;
        
        computer->isPlaying = true;
        computer->isActivated = true;
        computer->isAI = true;
    }
}

void initStoryCharacters(void)
{
    PPLAYER player = &g_Players[0];
    PPLAYER computer = &g_Players[1];
    
    g_Game.isBoss = false;

    // initialize all as unavailable first
    for (int i = 0; i < CHARACTER_MAX; i++)
    {
        g_StoryProgress.available[i] = false;
        g_StoryProgress.finished[i] = false;
    }

    // normal characters always available
    if (g_GameOptions.bossMode) {
        g_StoryProgress.available [CHARACTER_MACCHI] = false;
        g_StoryProgress.available[CHARACTER_JELLY]  = false;
        g_StoryProgress.available[CHARACTER_PENNY]  = false;
        g_StoryProgress.available[CHARACTER_POTTER] = false;
        g_StoryProgress.available[CHARACTER_SPARTA] = false;
        g_StoryProgress.available[CHARACTER_POPPY]  = false;
        g_StoryProgress.available[CHARACTER_TJ]     = false;
        g_StoryProgress.available[CHARACTER_GEORGE] = false;
    }
    else {
        g_StoryProgress.available [CHARACTER_MACCHI] = true;
        g_StoryProgress.available[CHARACTER_JELLY]  = true;
        g_StoryProgress.available[CHARACTER_PENNY]  = true;
        g_StoryProgress.available[CHARACTER_POTTER] = true;
        g_StoryProgress.available[CHARACTER_SPARTA] = true;
        g_StoryProgress.available[CHARACTER_POPPY]  = true;
        g_StoryProgress.available[CHARACTER_TJ]     = true;
        g_StoryProgress.available[CHARACTER_GEORGE] = true;
    }

    // wuppy always available as opponent
    g_StoryProgress.available[CHARACTER_WUPPY] = true;
    
    // CHARACTER_NONE never available (or are they??)
    g_StoryProgress.available[CHARACTER_NONE] = false;

    switch (player->character.choice)
    {
        case CHARACTER_WUPPY:
            g_StoryProgress.available[CHARACTER_WALRUS] = true;
            break;
            
        case CHARACTER_WALRUS:
            g_StoryProgress.available[CHARACTER_GARF] = true;
            break;
            
        case CHARACTER_GARF:
            g_StoryProgress.available[CHARACTER_NONE] = true;
            break;
            
        case CHARACTER_NONE:
            g_StoryProgress.available[CHARACTER_WALRUS] = true;
            g_StoryProgress.available[CHARACTER_GARF] = true;
            break;
            
        default:
            break;
    }
    
    // player's own character is never an opponent
    g_StoryProgress.available[player->character.choice] = false;

    // set up first opponent - first available character
    for (int i = 0; i < CHARACTER_MAX; i++)
    {
        if (g_StoryProgress.available[i])
        {
            computer->character.choice = i;
            break;
        }
    }

    // team and sprite setup unchanged
    computer->teamChoice = TEAM_2;
    g_Team.isAvailable[computer->teamChoice] = false;
    g_Team.isActive[computer->teamChoice] = true;
    computer->_bg->id = computer->_bg->anim[0].asset + 1;
    assignCharacterSprite(computer);
    assignCharacterStats(computer);
    player_bg.mesh = MESHoff;
    computer->isPlaying = true;
    computer->isActivated = true;
    computer->isDead = false;
    computer->isAI = true;
    g_Team.numTeams = TWO_TEAMS;
}

// this doesn't do much anymore
void nextStoryCharacter(void)
{
    PPLAYER computer = &g_Players[1];

    computer->isActivated = true;
    computer->isDead = false;
    
    initVsModePlayers();
    boundPlayer(computer);
}

void initVsModePlayers(void)
{
    for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PPLAYER player = &g_Players[i];
        
        set_spr_scale_fxp(player->_portrait, Fxp(1.1), Fxp_1);
        player->_bg->id = player->_bg->anim[0].asset + i;
        player_bg.mesh = MESHoff;
        player->_sprite->isColliding = false;
        assignCharacterStats(player);
        
        // PLAYER SPECIFIC ATTRIBUTES
        switch (player->teamChoice) {
            case TEAM_1: {
                player->_sprite->flip = sprNoflip;
                player->onLeftSide = true;
                if (g_Game.gameMode == GAME_MODE_CLASSIC || g_Game.gameMode == GAME_MODE_STORY || g_Team.numTeams == TWO_TEAMS) {
                    player->goalCenterThresholdMax = LARGE_GOAL_THRESHOLD_MAX;
                    player->goalCenterThresholdMin = LARGE_GOAL_THRESHOLD_MIN;
                    set_spr_position(player->_sprite, -1*PLAYER_X, 0, PLAYER_DEPTH);
                }
                else {
                    set_spr_position(player->_sprite, -1*PLAYER_X, -1*PLAYER_Y, PLAYER_DEPTH);
                    player->goalCenterThresholdMax = SMALL_GOAL_THRESHOLD_MAX;
                    player->goalCenterThresholdMin = SMALL_GOAL_THRESHOLD_MIN;
                }
                player->shield_pos = SHIELD_OFFSET;
                shield[i].flip = sprNoflip;
                break;
            } 
            case TEAM_2: {
                player->_sprite->flip = sprHflip;
                player->onLeftSide = false;
                if (g_Game.gameMode == GAME_MODE_CLASSIC || g_Game.gameMode == GAME_MODE_STORY || g_Team.numTeams < FOUR_TEAMS) {
                    player->goalCenterThresholdMax = LARGE_GOAL_THRESHOLD_MAX;
                    player->goalCenterThresholdMin = LARGE_GOAL_THRESHOLD_MIN;
                    set_spr_position(player->_sprite, PLAYER_X, 0, PLAYER_DEPTH);
                }
                else {
                    player->goalCenterThresholdMax = SMALL_GOAL_THRESHOLD_MAX;
                    player->goalCenterThresholdMin = SMALL_GOAL_THRESHOLD_MIN;
                    set_spr_position(player->_sprite, PLAYER_X, -1*PLAYER_Y, PLAYER_DEPTH);
                }
                player->shield_pos = -SHIELD_OFFSET;
                shield[i].flip = sprHflip;
                break;
            }
            case TEAM_3: {
                // set based on status of team 1
                player->_sprite->flip = sprVflip;
                player->onLeftSide = true;
                player->goalCenterThresholdMax = SMALL_GOAL_THRESHOLD_MAX;
                player->goalCenterThresholdMin = SMALL_GOAL_THRESHOLD_MIN;
                set_spr_position(player->_sprite, -1*PLAYER_X, PLAYER_Y, PLAYER_DEPTH);
                player->shield_pos = SHIELD_OFFSET;
                shield[i].flip = sprNoflip;
                break;
            }
            case TEAM_4: {
                // set based on status of team 2
                player->_sprite->flip = sprHVflip;
                player->onLeftSide = false;
                player->goalCenterThresholdMax = SMALL_GOAL_THRESHOLD_MAX;
                player->goalCenterThresholdMin = SMALL_GOAL_THRESHOLD_MIN;
                set_spr_position(player->_sprite, PLAYER_X, PLAYER_Y, PLAYER_DEPTH);
                player->shield_pos = -SHIELD_OFFSET;
                shield[i].flip = sprHflip;
                break;
            }
            default:
                break;
        }
    }
}

void switchPlayerPosition(PPLAYER player)
{       
        // PLAYER SPECIFIC ATTRIBUTES
        switch (player->teamChoice) {
            case TEAM_3: {
                // set based on status of team 1
                player->_sprite->flip = sprHflip;
                player->onLeftSide = false;
                set_spr_position(player->_sprite, PLAYER_X, PLAYER_Y, PLAYER_DEPTH);
                player->shield_pos = -SHIELD_OFFSET;
                shield[player->playerID].flip = sprHflip;
                break;
            }
            case TEAM_4: {
                // set based on status of team 2
                player->_sprite->flip = sprNoflip;
                player->onLeftSide = true;
                set_spr_position(player->_sprite, -1*PLAYER_X, PLAYER_Y, PLAYER_DEPTH);
                player->shield_pos = SHIELD_OFFSET;
                shield[player->playerID].flip = sprNoflip;
                break;
            }
            default:
                break;
        }
        player->goalCenterThresholdMax = LARGE_GOAL_THRESHOLD_MAX;
        player->goalCenterThresholdMin = LARGE_GOAL_THRESHOLD_MIN;
}

void initDemoPlayers(void)
{
    g_Game.numPlayers = rnd.GetNumber(TWO_PLAYER, FOUR_PLAYER);
    g_Team.maxTeams = g_Game.numPlayers + 1;
    g_Team.numTeams = 0;
    g_Game.gameMode = GAME_MODE_BATTLE;
    initPlayers();
    
    for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PPLAYER player = &g_Players[i];
        if (i == 0) {
            player->_sprite = &paw[CHARACTER_MACCHI];
            player->_sprite->id = player->_sprite->anim[0].asset;
            player->_sprite->flip = sprNoflip;
            player->onLeftSide = true;
            player->teamChoice = TEAM_1;
            if (g_Game.numPlayers >= THREE_PLAYER) {
                set_spr_position(player->_sprite, -1*PLAYER_X, -1*PLAYER_Y, PLAYER_DEPTH);
            }
            else {
                set_spr_position(player->_sprite, -1*PLAYER_X, 0, PLAYER_DEPTH);
            }
            player->character.choice = i;
            player->shield_pos = SHIELD_OFFSET;
            g_Team.numTeams++;
            g_Game.currentNumPlayers++;
        }
        else if (i == 1) {
            if (rnd.GetNumber(0, 999) % 2) { // modulus
                player->_sprite = &paw[CHARACTER_JELLY];
                player->character.choice = 1;
            }
            else if (rnd.GetNumber(0, 999) % 9) {
                player->_sprite = &paw[CHARACTER_GARF];
                player->character.choice = 10;
            }
            else {
                player->_sprite = &paw[CHARACTER_SPARTA];
                player->character.choice = 4;
            }
            player->_sprite->id = player->_sprite->anim[0].asset;
            player->_sprite->flip = sprHflip;
            player->onLeftSide = false;
            player->teamChoice = TEAM_2;
            
            if (g_Game.numPlayers <= THREE_PLAYER) {
                set_spr_position(player->_sprite, PLAYER_X, 0, PLAYER_DEPTH);
            }
            else {
                set_spr_position(player->_sprite, PLAYER_X, -1*PLAYER_Y, PLAYER_DEPTH);
            }
            player->shield_pos = -SHIELD_OFFSET;
            g_Team.numTeams++;
            g_Game.currentNumPlayers++;
        }
        else if (i == 2) { // set up player 3 last (we need to know the team count)
            if (rnd.GetNumber(0, 999) % 2) { // modulus
                player->_sprite = &paw[CHARACTER_POPPY];
                player->character.choice = 5;
            }
            else if (rnd.GetNumber(0, 999) % 9) {
                player->_sprite = &paw[CHARACTER_WALRUS];
                player->character.choice = 9;
            }
            else {
                player->_sprite = &paw[CHARACTER_PENNY];
                player->character.choice = 2;
            }
            player->_sprite->id = player->_sprite->anim[0].asset;
            player->_sprite->flip = sprVflip;
            player->onLeftSide = true;
            player->teamChoice = TEAM_3;
            set_spr_position(player->_sprite, -1*PLAYER_X, PLAYER_Y, PLAYER_DEPTH);
            player->shield_pos = SHIELD_OFFSET;
            g_Team.numTeams++;
            g_Game.currentNumPlayers++;
        }
        else if (i == 3) {
            if (rnd.GetNumber(0, 999) % 2) { // modulus
                player->_sprite = &paw[CHARACTER_POTTER];
                player->character.choice = 3;
            }
            else if (rnd.GetNumber(0, 999) % 9) {
                player->_sprite = &paw[CHARACTER_WUPPY];
                player->character.choice = 8;
            }
            else {
                player->_sprite = &paw[CHARACTER_TJ];
                player->character.choice = 6;
            }
            player->_sprite->id = player->_sprite->anim[0].asset;
            player->_sprite->flip = sprHVflip;
            player->onLeftSide = false;
            player->teamChoice = TEAM_4;
            set_spr_position(player->_sprite, PLAYER_X, PLAYER_Y, PLAYER_DEPTH);
            player->shield_pos = -SHIELD_OFFSET;
            g_Team.numTeams++;
            g_Game.currentNumPlayers++;
        }
        
        assignCharacterStats(player);
        player->goalCenterThresholdMax = SMALL_GOAL_THRESHOLD_MAX;
        player->goalCenterThresholdMin = SMALL_GOAL_THRESHOLD_MIN;

        player->_sprite->pos.r = PLAYER_RADIUS;
        player->shield.activate = false;
        player_bg.mesh = MESHoff;
        player->_sprite->mesh = MESHoff;
        player->_portrait->id = player->_portrait->anim[0].asset + player->character.choice;
        set_spr_scale_fxp(player->_portrait, Fxp(1.1), Fxp_1);
        player->isActivated = true;
        player->isPlaying = true;
        player->isAI = true;
        player->_sprite->isColliding = false;
        boundPlayer(player);
    }
    resetTeamState();
}

void assignCharacterSprite(PPLAYER player) {
    player->_sprite = &paw[player->character.choice];
    player->_sprite->anim[0].frame = 0;
    player->_sprite->id = player->_sprite->anim[0].asset;
    player->_sprite->mesh = MESHoff;
    player->_sprite->zmode = _ZmCC;
    if (
        player->playerID == 1 &&
        player->character.choice == CHARACTER_WUPPY && 
        g_Game.gameMode == GAME_MODE_STORY
        )
    {
        player->_sprite->scl = {Fxp(3), Fxp(3)};
        player->_sprite->pos.r = PLAYER_RADIUS * Fxp(1.5);
    }
    else {
        player->_sprite->scl = {Fxp(2), Fxp(2)};
        player->_sprite->pos.r = PLAYER_RADIUS;
    }
}

// this is super ugly (too much repetition) - could be reorganized?
void assignCharacterStats(PPLAYER player) {
    if (player->isAI) {
        switch(g_Game.gameDifficulty)
            {
                case GAME_DIFFICULTY_EASY:
                    if (g_Game.gameMode == GAME_MODE_STORY) {
                        player->maxSpeed = Fxp(characterAttributes[player->character.choice].maxSpeed) * Fxp(0.1);
                        player->basePower = Fxp(characterAttributes[player->character.choice].power) * Fxp(.06);
                        player->acceleration = Fxp(characterAttributes[player->character.choice].acceleration) * Fxp(1.1);
                    }
                    else {
                        player->maxSpeed = Fxp(characterAttributes[player->character.choice].maxSpeed) * Fxp(0.07);
                        player->basePower = Fxp(characterAttributes[player->character.choice].power) * Fxp(.05);
                        player->acceleration = Fxp(characterAttributes[player->character.choice].acceleration);
                    }
                    break;
                case GAME_DIFFICULTY_MEDIUM:
                    if (g_Game.gameMode == GAME_MODE_STORY) {
                        player->maxSpeed = Fxp(characterAttributes[player->character.choice].maxSpeed) * Fxp(0.12);
                        player->basePower = Fxp(characterAttributes[player->character.choice].power) * Fxp(.07);
                        player->acceleration = Fxp(characterAttributes[player->character.choice].acceleration) * Fxp(1.1);
                    }
                    else {
                        player->maxSpeed = Fxp(characterAttributes[player->character.choice].maxSpeed) * Fxp(0.08);
                        player->basePower = Fxp(characterAttributes[player->character.choice].power) * Fxp(.05);
                        player->acceleration = Fxp(characterAttributes[player->character.choice].acceleration);
                    }
                    break;
                case GAME_DIFFICULTY_HARD:
                    if (g_Game.gameMode == GAME_MODE_STORY) {
                        player->maxSpeed = Fxp(characterAttributes[player->character.choice].maxSpeed) * Fxp(0.13);
                        player->basePower = Fxp(characterAttributes[player->character.choice].power) * Fxp(.08);
                        player->acceleration = Fxp(characterAttributes[player->character.choice].acceleration) * Fxp(1.2);
                    }
                    else {
                        player->maxSpeed = Fxp(characterAttributes[player->character.choice].maxSpeed) * Fxp(0.1);
                        player->basePower = Fxp(characterAttributes[player->character.choice].power) * Fxp(.05);
                        player->acceleration = Fxp(characterAttributes[player->character.choice].acceleration);
                    }
                    break;
                default:
                    break;
            }
    }
    else {        
        player->maxSpeed = Fxp(characterAttributes[player->character.choice].maxSpeed) * Fxp(0.1);
        player->basePower = Fxp(characterAttributes[player->character.choice].power) * Fxp(.05);
        player->acceleration = Fxp(characterAttributes[player->character.choice].acceleration);
    }
    player->power = player->basePower;
    
    if (player->isAI) {
        switch (g_Game.gameDifficulty) {
            case GAME_DIFFICULTY_EASY: {
                player->acceleration = player->acceleration * EASY_AI_MOVEMENT_SPEED;
                break;
            }
            case GAME_DIFFICULTY_MEDIUM: {
                player->acceleration = player->acceleration * MEDIUM_AI_MOVEMENT_SPEED;
                break;
            }
            case GAME_DIFFICULTY_HARD: {
                player->acceleration = player->acceleration * HARD_AI_MOVEMENT_SPEED;
                break;
            }
            default:
                player->acceleration = player->acceleration * MEDIUM_AI_MOVEMENT_SPEED;
                break;
        }
    }
    else {
        player->acceleration = player->acceleration * PLAYER_MOVEMENT_SPEED;
    }
}

void getClassicModeInput(void)
{
    for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PPLAYER player = &g_Players[i];
        Digital gamepad(player->input->id);
        
        if(!player->isActivated || player->isDead || player->isAI == true)
        {
            continue;
        }
        player->moveHorizontal = false;
        player->moveVertical = false;
        if (player->input->isAnalog) {
            player->curPos.dy = player->input->axis_y * Fxp_HALF;
            if (player->curPos.dy > Fxp_0 || player->curPos.dy < Fxp_0) {
                player->moveVertical = true;
            }
        }
        else {
            if (gamepad.IsHeld(Digital::Button::Up))
            {
                player->curPos.dy -= X_SPEED_INC;
                player->moveVertical = true;
            }
            if (gamepad.IsHeld(Digital::Button::Down))
            {
                player->curPos.dy += X_SPEED_INC;
                player->moveVertical = true;
            }
        }
        if(player->moveVertical == false)
        {
            player->curPos.dy = 0;
            player->_sprite->vel.y = 0;
        }
        regenPlayerPower(player);
        playerAttack(player);
        
        #if ENABLE_DEBUG_MODE == 1
        if (gamepad.WasPressed(Digital::Button::X))
        {
            if (g_Players[1].numLives > 1)
            {
                g_Players[1].numLives--;
            }
        }
        if (gamepad.WasPressed(Digital::Button::Y))
        {
            if (g_Players[0].numLives > 1)
            {
                g_Players[0].numLives--;
            }
        }
        if (gamepad.WasPressed(Digital::Button::Z))
        {
            g_Gameplay.GameTimer = 2;
        }
        #endif
    }
}

void getPlayersInput(void)
{
    for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PPLAYER player = &g_Players[i];
        Digital gamepad(player->input->id);
        if(!player->isActivated || player->isDead || player->isAI == true)
        {
            continue;
        }
        player->moveHorizontal = false;
        player->moveVertical = false;
        if (player->input->isAnalog) {
            player->curPos.dx = player->input->axis_x;
            player->curPos.dy = player->input->axis_y * Fxp_HALF;
            if (player->curPos.dx > Fxp_0 || player->curPos.dx < Fxp_0) {
                player->moveHorizontal = true;
            }
            if (player->curPos.dy > Fxp_0 || player->curPos.dy < Fxp_0) {
                player->moveVertical = true;
            }
        }
        else {
            if (gamepad.IsHeld(Digital::Button::Left))
            {
                player->curPos.dx -= X_SPEED_INC;
                player->moveHorizontal = true;
            }
            if (gamepad.IsHeld(Digital::Button::Right))
            {
                player->curPos.dx += X_SPEED_INC;
                player->moveHorizontal = true;
            }

            if (gamepad.IsHeld(Digital::Button::Up))
            {
                player->curPos.dy -= X_SPEED_INC;
                player->moveVertical = true;
            }
            if (gamepad.IsHeld(Digital::Button::Down))
            {
                player->curPos.dy += X_SPEED_INC;
                player->moveVertical = true;
            }
        }
        if(player->moveHorizontal == false)
        {
            player->curPos.dx = 0;
            player->_sprite->vel.x = 0;
        }
        if(player->moveVertical == false)
        {
            player->curPos.dy = 0;
            player->_sprite->vel.y = 0;
        }
        
        regenPlayerPower(player);
        playerAttack(player);
        
        #if ENABLE_DEBUG_MODE == 1
        if (gamepad.WasPressed(Digital::Button::X))
        {
            if (g_Players[1].numLives > 1)
            {
                g_Players[1].numLives--;
            }
        }
        if (gamepad.WasPressed(Digital::Button::Y))
        {
            if (g_Players[0].numLives > 1)
            {
                g_Players[0].numLives--;
            }
        }
        if (gamepad.WasPressed(Digital::Button::Z))
        {
            g_Gameplay.GameTimer = 2;
        }
        #endif
    }
}

void playerAttack(PPLAYER player) {
        if (!g_Game.isActive) {
            return;
        }        
        // ATTACK1
        Digital gamepad(player->input->id);
        if (gamepad.WasPressed(Digital::Button::A) && player->shield.power > ATTACK1_COST && !player->attack1)
        {
            if (player->onLeftSide) {
                player->_sprite->pos.x += ATTACK1;
            }
            else {
                player->_sprite->pos.x -= ATTACK1;
            }
            player->attack1 = true;
            player->shield.power -= ATTACK1_COST;
        }
        else if (player->attack1 && player->attack1Frames == ATTACK_FRAMES) {
            if (player->onLeftSide) {
                player->_sprite->pos.x -= ATTACK1;
            }
            else {
                player->_sprite->pos.x += ATTACK1;
            }
            player->attack1Frames = 0;
            player->attack1 = false;
        }
        else if (player->attack1 && player->attack1Frames < ATTACK_FRAMES) {
            player->attack1Frames++;
        }
        // ATTACK2
        if (gamepad.WasPressed(Digital::Button::C) && player->shield.power > ATTACK2_COST && !player->attack2)
        {
            if (player->onLeftSide) {
                player->_sprite->pos.x += ATTACK2;
            }
            else {
                player->_sprite->pos.x -= ATTACK2;
            }
            player->attack2 = true;
            player->shield.power -= ATTACK2_COST;
        }
        else if (player->attack2 && player->attack2Frames == ATTACK_FRAMES) {
            if (player->onLeftSide) {
                player->_sprite->pos.x -= ATTACK2;
            }
            else {
                player->_sprite->pos.x += ATTACK2;
            }
            player->attack2Frames = 0;
            player->attack2 = false;
        }
        else if (player->attack2 && player->attack2Frames < ATTACK_FRAMES) {
            player->attack2Frames++;
        }
        // SHIELD
        if (gamepad.WasPressed(Digital::Button::B) && player->shield.power > SHIELD_COST)
        {
            if (player->shield.power > 1) {
                Pcm::Play(Sounds.Game[ShieldSnd], PlayMode::Protected, 6);
                if (player->isBig) {
                    player->_sprite->pos.r = SHIELD_RADIUS_LARGE;
                }
                else if (player->isSmall) {
                    player->_sprite->pos.r = SHIELD_RADIUS_SMALL;
                }
                else {
                    player->_sprite->pos.r = SHIELD_RADIUS;
                }
                player->shield.activate = true;
            }
            if (!g_GameOptions.testCollision) {
                player->shield.power -= SHIELD_COST;
            }
        }
        else if (!player->shield.activate) {  
            if (player->isBig) {
                player->_sprite->pos.r = PLAYER_RADIUS_LARGE;
            }
            else if (player->isSmall) {
                player->_sprite->pos.r = PLAYER_RADIUS_SMALL;
            }
            else {
                player->_sprite->pos.r = PLAYER_RADIUS;
            }
        }
}

void regenPlayerPower(PPLAYER player)
{
    Digital gamepad(player->input->id);
    // TODO: draw some sort of visual effect when the shield is charging (maybe a sound effect)
    if (player->onLeftSide && player->_sprite->pos.x > -BOUNDARY_SHIELD_REGEN_SLOW) {
        return;
    }
    if (!player->onLeftSide && player->_sprite->pos.x < BOUNDARY_SHIELD_REGEN_SLOW) {
        return;
    }
    uint8_t regen_speed = SHIELD_REGEN_SLOW;
    if (player->onLeftSide && player->_sprite->pos.x < -BOUNDARY_SHIELD_REGEN_FAST) {
        regen_speed = SHIELD_REGEN_FAST;
    }
    if (!player->onLeftSide && player->_sprite->pos.x > BOUNDARY_SHIELD_REGEN_FAST) {
        regen_speed = SHIELD_REGEN_FAST;
    }
    if (!gamepad.IsHeld(Digital::Button::A) || 
        !gamepad.IsHeld(Digital::Button::B) || 
        !gamepad.IsHeld(Digital::Button::C)) {
        if (player->shield.power < SHIELD_POWER) {
            if (g_Game.frame % regen_speed == 0) { // modulus
                player->shield.power++;
            }
        }
    }
}

void updatePlayers(void)
{
    for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PPLAYER player = &g_Players[i];
        
        if(!player->isActivated || player->isDead)
        {
            continue;
        }
        
        // item collision (include AI players!)
        // don't allow collision unless player can see item
        if (g_item.isActive)
        { 
            g_item._sprite->isColliding = checkItemDistance(player->_sprite, g_item._sprite);            
            if (g_item._sprite->isColliding)
            {
                handlePlayerItemCollision(player);
            }
        }
        else {
            g_item._sprite->isColliding = false;
        }
        
        changePlayerSize(player, g_item.timer[i]);
        
        if(player->isAI == true)
        {
            continue;
        }

        speedLimitPlayer(player);

        // move the player
        player->_sprite->pos.y += player->curPos.dy;
        player->_sprite->vel.y += player->curPos.dy;
        player->_sprite->pos.x += player->curPos.dx;
        player->_sprite->vel.x += player->curPos.dx;
        boundPlayer(player);
        
        // ball collision
        detect_player_ball_collision(&pixel_poppy, player);
        
        // if (i == 0) {
            // SRL::Debug::Print(2, 9, "Player isBig %i", player->isBig);
            // SRL::Debug::Print(2, 10, "Player isSmall %i", player->isSmall);
            // SRL::Debug::Print(2, 11, "Player scale %3d", player->_sprite->scl.x.As<int16_t>());
        // }
    }
}

void speedLimitPlayer(PPLAYER player)
{
    Fxp y_up_speed;
    Fxp y_dn_speed;
    Fxp x_l_speed;
    Fxp x_r_speed;
    if (player->isAI == true) {
        y_up_speed = player->maxSpeed;
        y_dn_speed = -player->maxSpeed;
        x_l_speed  = MAX_X_SPEED;
        x_r_speed  = -MAX_X_SPEED;
    }
    else {
        y_up_speed = MAX_Y_SPEED;
        y_dn_speed = -MAX_Y_SPEED;
        x_l_speed  = MAX_X_SPEED;
        x_r_speed  = -MAX_X_SPEED;
    }

    // validate speeds
    if(player->curPos.dx > x_l_speed)
    {
        player->curPos.dx = x_l_speed;
    }

    if(player->curPos.dx < x_r_speed)
    {
        player->curPos.dx = x_r_speed;
    }

    if(player->curPos.dy > y_up_speed)
    {
        player->curPos.dy = y_up_speed;
    }

    if(player->curPos.dy < y_dn_speed)
    {
        player->curPos.dy = y_dn_speed;
    }
}

void boundPlayer(PPLAYER player)
{       
    Fxp boundary_middle;
    if (g_Game.isActive) {
        boundary_middle = PLAYER_BOUNDARY_MIDDLE;
    }
    else {
        boundary_middle = PLAYER_BOUNDARY_MIDDLE_INACTIVE;
    }
    // screen boundaries
    if (player->onLeftSide == true) {
      if (g_GameOptions.testCollision) {
        if(player->_sprite->pos.x > PLAYER_BOUNDARY_RIGHT - PLAYER_WIDTH)
        {
            player->_sprite->pos.x = PLAYER_BOUNDARY_RIGHT - PLAYER_WIDTH;
        }
      }
      else {
        if(player->_sprite->pos.x > -boundary_middle - PLAYER_WIDTH)
        {
            player->_sprite->pos.x = -boundary_middle - PLAYER_WIDTH;
        }
      }
        if(player->_sprite->pos.x < PLAYER_BOUNDARY_LEFT + PLAYER_WIDTH)
        {
            player->_sprite->pos.x = PLAYER_BOUNDARY_LEFT + PLAYER_WIDTH;
        }
    }
    
    else {
        if(player->_sprite->pos.x > PLAYER_BOUNDARY_RIGHT - PLAYER_WIDTH)
        {
            player->_sprite->pos.x = PLAYER_BOUNDARY_RIGHT - PLAYER_WIDTH;
        }
      if (g_GameOptions.testCollision) {
        if(player->_sprite->pos.x < PLAYER_BOUNDARY_LEFT + PLAYER_WIDTH)
        {
            player->_sprite->pos.x = PLAYER_BOUNDARY_LEFT + PLAYER_WIDTH;
        }
      }
      else {
        if(player->_sprite->pos.x < boundary_middle + PLAYER_WIDTH)
        {
            player->_sprite->pos.x = boundary_middle + PLAYER_WIDTH;
        }
      }
    }

    if(player->_sprite->pos.y > SCREEN_BOTTOM - PLAYER_HEIGHT)
    {
        player->_sprite->pos.y = SCREEN_BOTTOM - PLAYER_HEIGHT;
    }

    if(player->_sprite->pos.y < SCREEN_TOP + PLAYER_HEIGHT)
    {
        player->_sprite->pos.y = SCREEN_TOP + PLAYER_HEIGHT;
    }
}

bool explodePLayer(PPLAYER player)
{
    if (player->numLives > 0) {
        player->numLives--;
        touchedBy[player->playerID].touchCount = 0;
        if (player->numLives == 0) {
            // kill player
            player->score.continues--;
            player->isDead = true;
            g_Game.currentNumPlayers--;
            if (player->isAI && g_Game.gameMode == GAME_MODE_STORY) {
                g_Game.countofRounds++; // for story mode only
            }
            g_ExplodeGoal = true;
            g_Transition.explosion_flash = true;
        }
    }
    return true;
}

void killPlayer(int8_t playerID) {
    PPLAYER player = &g_Players[playerID];
    
    player->score.continues--;
    player->isDead = true;
    g_Game.currentNumPlayers--;
    if (player->isAI && g_Game.gameMode == GAME_MODE_STORY) {
        g_Game.countofRounds++;
        PPLAYER computer = &g_Players[1];
        if (g_Game.isBoss)
        {
            initBossFx();
        }
        // unlock character once you've beaten them
        if (!characterUnlocked[computer->character.choice] && g_Game.gameDifficulty > GAME_DIFFICULTY_EASY) {
            characterUnlocked[computer->character.choice] = true;
            save_game_backup();
        }
    }
    g_ExplodeGoal = true;
    g_Transition.explosion_flash = true;
    // player lost all their lives, assign stars to scoring player
    if (lastTouchedBy != -1 && lastTouchedBy != playerID) {
        g_Players[lastTouchedBy].score.stars++;
    }
    else {
        for (uint8_t i = 0; i < TOUCHEDBY_BUFFER; i++) {
            int8_t id = previouslyTouchedBy[i];
            if (id == -1) continue;
            
            PPLAYER opponent = &g_Players[id];
            if (opponent->isDead) continue;
            if (!opponent->isActivated) continue;
            if (id == playerID) continue;
            if (player->onLeftSide == opponent->onLeftSide) continue;
            opponent->score.stars++;
            break;
        }
    }
}

void updatePlayerLives(uint8_t scoredOnPlayerID)
{
    if (g_Players[scoredOnPlayerID].numLives > 0) {
        g_Players[scoredOnPlayerID].numLives--;
        touchedBy[scoredOnPlayerID].touchCount = 0;
    }
    if (g_Players[scoredOnPlayerID].numLives == 0) {
        killPlayer(scoredOnPlayerID);
    }
}