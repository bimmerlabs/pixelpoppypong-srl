#include "AI.h"
#include "physics.h"
#include "gameplay.h"
#include "../main.h"
#include "../core/assets.h"
#include "../core/audio.h"
#include "../objects/characters.h"

extern PLAYER g_Players[MAX_PLAYERS];

void playerAI(Sprite *ball) {    
    for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PPLAYER player = &g_Players[i];
        if(!player->isActivated || player->isAI == false  || player->isDead)
        {
            continue;
        }
        if (!g_Game.isBallActive) {
            centerAiPlayer(player);
        }
        else if (player->onLeftSide == true) {
            // Check if the ball is moving towards player 2's goal
            if (ball->vel.x < 0) {

                // Check if the ball is close enough to start tracking
                if (ball->pos.x <= 128) {
                    // animate_paw1 = true;
                }
                if (ball->pos.x <= SCREEN_MIDDLE + FIELD_THRESHOLD) {
                    // animate_paw1 = true;
                    // Move the paw towards the ball's y position
                    Fxp y_diff = ball->pos.y - player->_sprite->pos.y;

                    // Gradual movement
                    player->curPos.dy += player->acceleration * y_diff;
                }
            }
            else {
                centerAiPlayer(player);
            }
        }
        else {
            // Check if the ball is moving towards player 2's goal
            if (ball->vel.x > 0) {

                // Check if the ball is close enough to start tracking
                if (ball->pos.x >= -128) {
                    // animate_paw1 = true;
                }
                if (ball->pos.x >= SCREEN_MIDDLE - FIELD_THRESHOLD) {
                    // animate_paw1 = true;
                    // Move the paw towards the ball's y position
                    Fxp y_diff = ball->pos.y - player->_sprite->pos.y;

                    // Gradual movement
                    player->curPos.dy += player->acceleration * y_diff;
                }
            } 
            else {
                centerAiPlayer(player);
            }
        }
        
        speedLimitPlayer(player);

        // move the player
        player->_sprite->pos.y += player->curPos.dy;
        player->_sprite->pos.x += player->curPos.dx;
        player->_sprite->vel.x += player->curPos.dx;
        player->_sprite->vel.y += player->curPos.dy;
        
        if (detect_player_ball_collision(&pixel_poppy, player))
        {
            if (g_Game.isBoss)
            {
                const char* quote = nullptr;
                BossQuotes& q = bossQuotes[player->character.choice];

                if (player->numLives <= 1 && !g_BossState.phase3Triggered)
                {
                    g_BossState.textFramesRemaining = 3*60;
                    quote = q.phase3;
                    Pcm::Play(Sounds.Game[LaunchSnd], PlayMode::Protected, 7);
                    PrintWrapped(0, 23, 30, quote, Align::CenterX);
                    g_BossState.phase3Triggered = true;
                    g_BossState.emitFramesRemaining = 60;
                    g_BossState.soundPlayed = false;
                    g_BossState.soundDelay = 15;
                }
                else if (player->numLives <= 2 && !g_BossState.phase2Triggered)
                {
                    g_BossState.textFramesRemaining = 3*60;
                    quote = q.phase2;
                    Pcm::Play(Sounds.Game[LaunchSnd], PlayMode::Protected, 7);
                    PrintWrapped(0, 23, 30, quote, Align::CenterX);
                    g_BossState.phase2Triggered = true;
                    g_BossState.emitFramesRemaining = 45;
                    g_BossState.soundPlayed = false;
                    g_BossState.soundDelay = 15;
                }
                else if (player->numLives <= 4 && !g_BossState.phase1Triggered)
                {
                    g_BossState.textFramesRemaining = 3*60;
                    quote = q.phase1;
                    Pcm::Play(Sounds.Game[LaunchSnd], PlayMode::Protected, 7);
                    PrintWrapped(0, 23, 24, quote, Align::CenterX);
                    g_BossState.phase1Triggered = true;
                    g_BossState.emitFramesRemaining = 30;
                    g_BossState.soundPlayed = false;
                    g_BossState.soundDelay = 15;
                }
            }
        }
        boundAiPlayer(player);
    }
}

void centerAiPlayer(PPLAYER player)
{
    Fxp middle;
    PGOAL goal = &g_Goal[player->playerID];
    switch(player->teamChoice)
    {
        case TEAM_1: {
            middle = -AI_GOAL_CENTER;
            if (goal->drawSingleGoal) {
                middle = SCREEN_MIDDLE;
            }
            break;
        }
        case TEAM_2: {
            middle = -AI_GOAL_CENTER;
            if (goal->drawSingleGoal) {
                middle = SCREEN_MIDDLE;
            }
            break;
        }
        default: {
            middle = AI_GOAL_CENTER;
            if (goal->drawSingleGoal) {
                middle = SCREEN_MIDDLE;
            }
            break;
        }
    }
    Fxp center_diff = middle - player->_sprite->pos.y;
    if (center_diff > player->goalCenterThresholdMax || center_diff < -player->goalCenterThresholdMax) {
        player->curPos.dy += MEDIUM_MOVEMENT_FACTOR * center_diff;
    }
    else if (center_diff > player->goalCenterThresholdMin || center_diff < -player->goalCenterThresholdMin) {
        player->curPos.dy -= SLOW_MOVEMENT_FACTOR * center_diff;
    }
    else {
        player->curPos.dy = 0;
    }
    player->_sprite->pos.y += player->curPos.dy;
    player->_sprite->vel.y += player->curPos.dy;
    boundAiPlayer(player);
}

void boundAiPlayer(PPLAYER player)
{
    if (player->onLeftSide == true) {
        if(player->_sprite->pos.x > -PLAYER_BOUNDARY_MIDDLE - PLAYER_WIDTH)
        {
            player->_sprite->pos.x = -PLAYER_BOUNDARY_MIDDLE - PLAYER_WIDTH;
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
        if(player->_sprite->pos.x < PLAYER_BOUNDARY_MIDDLE + PLAYER_WIDTH)
        {
            player->_sprite->pos.x = PLAYER_BOUNDARY_MIDDLE + PLAYER_WIDTH;
        }
    }

    Fxp bottom = SCREEN_BOTTOM;
    Fxp top = SCREEN_MIDDLE;
    PGOAL goal = &g_Goal[player->playerID];
    switch(player->teamChoice)
    {
        case TEAM_1: {
            bottom = SCREEN_MIDDLE;
            top = SCREEN_TOP;
            if (goal->drawSingleGoal) {
                bottom = SCREEN_BOTTOM;
            }
            break;
        }
        case TEAM_2: {
            bottom = SCREEN_MIDDLE;
            top = SCREEN_TOP;
            if (goal->drawSingleGoal) {
                bottom = SCREEN_BOTTOM;
            }
            break;
        }
        default: {
            if (goal->drawSingleGoal) {
                top = SCREEN_TOP;
                bottom = SCREEN_BOTTOM;
            }
            break;
        }
    }
    if(player->_sprite->pos.y > bottom)
    {
        player->_sprite->pos.y = bottom;
        player->curPos.dy = 0;
    }

    if(player->_sprite->pos.y < top)
    {
        player->_sprite->pos.y = top;
        player->curPos.dy = 0;
    }
}