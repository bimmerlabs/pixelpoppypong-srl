#include "goal.h"
#include "../main.h"
#include "../core/screen_transition.h"
#include "../game/physics.h"
#include "../game/highscores.h"
#include "../vdp2/sprite_colors.h"
#include "../objects/characters.h"

GOAL g_Goal[MAX_PLAYERS] = {};
bool g_AnimateGoal = false;
bool g_ExplodeGoal = false;

static bool goal_increasing = false;
static int goal_h_value = 0;
static short goal_animation_cycles = 0;

void initGoalColors(void)
{
    g_AnimateGoal = false;
    g_ExplodeGoal = false;
    goal_increasing = false;
    goal_h_value = 0;
    goal_animation_cycles = 0;
    for (unsigned int i = 1; i < MAX_PLAYERS; i++)
    {
        // set initial player colors (player 0 uses the default)
        if (i == 1) {
            hsl_incSprites[HSL_GOAL].h -= 90;
        }
        else if (i == 2) {
            hsl_incSprites[HSL_GOAL].h -= 180;
        }
        else if (i == 3) {
            hsl_incSprites[HSL_GOAL].h -= 270;
        }
        update_palette_Goals[i] = update_sprites_color(&p_rangeGoals[i], HSL_GOAL);
    }
}

void animateGoalColor(bool *_do_update) {
    if (!g_AnimateGoal) {
        return;
    }
    if (goal_animation_cycles < 9) {
        if (goal_increasing) {
            if (goal_h_value < 6) {
                goal_h_value += 1;
                hsl_incSprites[HSL_GOAL].h = -5;
            } 
            else {
                goal_increasing = false;
            }
        } 
        else {
            if (goal_h_value > -6) {
                goal_h_value -= 1;
                hsl_incSprites[HSL_GOAL].h = +5;
            } 
            else {
                goal_increasing = true;
            }
            if (goal_h_value == 0) {
                goal_animation_cycles++;
            }
        }
        *_do_update = true;
    }
    else {
        g_AnimateGoal = false;
        goal_animation_cycles = 0;
        // clear taunts if needed
        SRL::Debug::PrintClearLine(14);
        SRL::Debug::PrintClearLine(15);
        SRL::Debug::PrintClearLine(16);
    }
}

void initGoals(void)
{
    for(unsigned int i = 0; i < MAX_PLAYERS; i++)
    {
        PGOAL goal = &g_Goal[i];
        goal->isColliding = false;
        goal->onLeftSide = false;
        goal->drawSingleGoal = true;
        goal->scale = 0;
        goal->pos.x = Fxp_0;
        goal->pos.top = Fxp_0;
        goal->pos.mid = Fxp_0;
        goal->pos.bot = Fxp_0;
        goal->pos.top_flip = 0;
        goal->pos.bot_flip = 0;
        goal->pos.top_zmode = 0;
        goal->pos.mid_zmode = 0;
        goal->pos.bot_zmode = 0;
        goal->id = -1; // is this needed?
        goal->sprite = &goals[i];
    }
}

void setGoalSize(void)
{
    for (int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PGOAL goal = &g_Goal[i];
        goal->player = &g_Players[i];
        if (!goal->player->isActivated) {
            continue;
        }
        goal->id = i;
        
        switch (goal->player->teamChoice) 
        {
            case TEAM_1: {
                if (g_Team.isActive[TEAM_3] == true && (g_Team.isActive[TEAM_2] == true || g_Team.isActive[TEAM_4] == true)) { // 3-4 player mode
                    goal->pos.x = -GOAL_X_POS;
                    goal->pos.top = -GOAL_Y_POS_TOP_VS_MODE;
                    goal->pos.mid = -GOAL_Y_POS_MID_VS_MODE;
                    goal->pos.bot = -GOAL_Y_POS_BOT_VS_MODE;
                    goal->scale = GOAL_SCALE_VS_MODE;
                    goal->drawSingleGoal = false;
                }
                else { // 2-3 player mode
                    goal->pos.x = -GOAL_X_POS;
                    goal->pos.top = -GOAL_Y_POS_MEDIUM;
                    goal->pos.mid = GOAL_CENTER_POS;
                    goal->pos.bot = GOAL_Y_POS_MEDIUM;
                    goal->scale = GOAL_SCALE_MEDIUM;
                    goal->drawSingleGoal = true;
                }
                goal->pos.top_flip = sprNoflip;
                goal->pos.bot_flip = sprVflip;
                goal->pos.top_zmode = _ZmLT;
                goal->pos.mid_zmode = _ZmLC;
                goal->pos.bot_zmode = _ZmLB;
                break;
            }
            case TEAM_2: {
                if (g_Team.isActive[TEAM_4] == true && (g_Team.isActive[TEAM_1] == true || g_Team.isActive[TEAM_3] == true)) { // 3-4 player mode
                    goal->pos.x = GOAL_X_POS;
                    goal->pos.top = -GOAL_Y_POS_TOP_VS_MODE;
                    goal->pos.mid = -GOAL_Y_POS_MID_VS_MODE;
                    goal->pos.bot = -GOAL_Y_POS_BOT_VS_MODE;
                    goal->scale = GOAL_SCALE_VS_MODE;
                    goal->drawSingleGoal = false;
                }
                else { // 2-3 player mode
                    goal->pos.x = GOAL_X_POS;
                    goal->pos.top = -GOAL_Y_POS_MEDIUM;
                    goal->pos.mid = GOAL_CENTER_POS;
                    goal->pos.bot = GOAL_Y_POS_MEDIUM;
                    goal->scale = GOAL_SCALE_MEDIUM;
                    goal->drawSingleGoal = true;
                }
                goal->pos.top_flip = sprHflip;
                goal->pos.bot_flip = sprHVflip;
                goal->pos.top_zmode = _ZmRT;
                goal->pos.mid_zmode = _ZmRC;
                goal->pos.bot_zmode = _ZmRB;
                break;
            }
            case TEAM_3: {
                goal->pos.top_flip = sprNoflip;
                goal->pos.bot_flip = sprVflip;
                goal->pos.top_zmode = _ZmLT;
                goal->pos.mid_zmode = _ZmLC;
                goal->pos.bot_zmode = _ZmLB;
                if (g_Team.isActive[TEAM_1] == true && (g_Team.isActive[TEAM_2] == true || g_Team.isActive[TEAM_4] == true)) { // 3-4 player mode
                    goal->pos.x = -GOAL_X_POS;
                    goal->pos.top = GOAL_Y_POS_BOT_VS_MODE;
                    goal->pos.mid = GOAL_Y_POS_MID_VS_MODE;
                    goal->pos.bot = GOAL_Y_POS_TOP_VS_MODE;
                    goal->scale = GOAL_SCALE_VS_MODE;
                    goal->drawSingleGoal = false;
                }
                else if (g_Team.isActive[TEAM_1] == true) { // 2 player mode
                    switchPlayerPosition(goal->player); // move to right side
                    goal->pos.x = GOAL_X_POS;
                    goal->pos.top = -GOAL_Y_POS_MEDIUM;
                    goal->pos.mid = GOAL_CENTER_POS;
                    goal->pos.bot = GOAL_Y_POS_MEDIUM;
                    goal->scale = GOAL_SCALE_MEDIUM;
                    goal->pos.top_flip = sprHflip;
                    goal->pos.bot_flip = sprHVflip;
                    goal->pos.top_zmode = _ZmRT;
                    goal->pos.mid_zmode = _ZmRC;
                    goal->pos.bot_zmode = _ZmRB;
                    goal->drawSingleGoal = true;
                }
                else { // 2-3 player mode
                    goal->pos.x = -GOAL_X_POS;
                    goal->pos.top = -GOAL_Y_POS_MEDIUM;
                    goal->pos.mid = GOAL_CENTER_POS;
                    goal->pos.bot = GOAL_Y_POS_MEDIUM;
                    goal->scale = GOAL_SCALE_MEDIUM;
                    goal->drawSingleGoal = true;
                }
                break;
            }
            case TEAM_4: {
                goal->pos.top_flip = sprHflip;
                goal->pos.bot_flip = sprHVflip;
                goal->pos.top_zmode = _ZmRT;
                goal->pos.mid_zmode = _ZmRC;
                goal->pos.bot_zmode = _ZmRB; 
                if (g_Team.isActive[TEAM_2] == true && (g_Team.isActive[TEAM_1] == true || g_Team.isActive[TEAM_3] == true)) { // 3-4 player mode
                    goal->pos.x = GOAL_X_POS;
                    goal->pos.top = GOAL_Y_POS_BOT_VS_MODE;
                    goal->pos.mid = GOAL_Y_POS_MID_VS_MODE;
                    goal->pos.bot = GOAL_Y_POS_TOP_VS_MODE;
                    goal->scale = GOAL_SCALE_VS_MODE; 
                    goal->drawSingleGoal = false;
                }
                else if (g_Team.isActive[TEAM_2] == true) { // 3-4 player mode
                    switchPlayerPosition(goal->player); // move to left side
                    goal->pos.x = -GOAL_X_POS;
                    goal->pos.top = -GOAL_Y_POS_MEDIUM;
                    goal->pos.mid = GOAL_CENTER_POS;
                    goal->pos.bot = GOAL_Y_POS_MEDIUM;
                    goal->scale = GOAL_SCALE_MEDIUM;
                    goal->pos.top_flip = sprNoflip;
                    goal->pos.bot_flip = sprVflip;
                    goal->pos.top_zmode = _ZmLT;
                    goal->pos.mid_zmode = _ZmLC;
                    goal->pos.bot_zmode = _ZmLB;
                    goal->drawSingleGoal = true;
                }
                else {
                    goal->pos.x = GOAL_X_POS;
                    goal->pos.top = -GOAL_Y_POS_MEDIUM;
                    goal->pos.mid = GOAL_CENTER_POS;
                    goal->pos.bot = GOAL_Y_POS_MEDIUM;
                    goal->scale = GOAL_SCALE_MEDIUM;
                    goal->drawSingleGoal = true;
                } 
                break;
            }
            default:
                break;
        }
        goal->onLeftSide = goal->player->onLeftSide;
    }
}

void drawGoals(void) {
    for (int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PGOAL goal = &g_Goal[i];
        if (!goal->player->isActivated || goal->player->isDead) {
            continue;
        }
        drawGoalSprites(goal->sprite, i*2, 0, 8, goal->pos.top_zmode, goal->pos.top_flip, goal->pos.x, goal->pos.top, 2);
        drawGoalSprites(goal->sprite, i*2, 1, 9, goal->pos.mid_zmode, goal->pos.top_flip, goal->pos.x, goal->pos.mid, goal->scale);
        drawGoalSprites(goal->sprite, i*2, 0, 8, goal->pos.bot_zmode, goal->pos.bot_flip, goal->pos.x, goal->pos.bot, 2);
    }
}

void explodeGoals(void) {
    if (!g_ExplodeGoal) {
        return;
    }
    for (int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PGOAL goal = &g_Goal[i];
        if (g_Team.isActive[goal->player->teamChoice] == true && goal->player->isDead) {
            goal->sprite->rot.z += 1;
            if (g_Transition.explosion_flash) {
                g_Transition.explosion_flash = explosionEffect();
                set_spr_scale(goal->sprite, 3, 3);
                goal->sprite->pos.y = goal->pos.mid;
                goal->sprite->zmode = _ZmCC;
            }
            else {
                my_sprite_draw(goal->sprite);
                g_ExplodeGoal = explode_animation(goal->sprite);
                if (!g_ExplodeGoal) {
                    goal->sprite->rot.z = 0;
                    if (g_Game.gameMode != GAME_MODE_STORY && g_Game.currentNumPlayers > 1) {
                        g_Team.isActive[goal->player->teamChoice] = false;
                        setGoalSize(); // not in story mode
                    }
                }
            }
        }
    }
}

void checkRightGoalCollision(Sprite *ball) {
    // iterate through goals on right side, check bounds
    for (int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PGOAL goal = &g_Goal[i];
        if (!goal->player->isActivated || goal->player->isDead || goal->onLeftSide) {
            continue;
        }
        if (ball->pos.y - GOAL_MARGIN > goal->pos.top && ball->pos.y + GOAL_MARGIN < goal->pos.bot) { // removed ball radius - need another solution
            g_Game.goalID = goal->id;
            g_AnimateGoal = true;
            if (g_Game.gameMode == GAME_MODE_STORY) {
                g_Game.isGoalScored = true;
                initStarsFx();
                calculateScore(ball, 0);
                updatePlayerLives(1);
                if (!g_Game.isBoss) {
                    playCDTrack(g_Audio.currentTrack, false);
                    nextcurrentTrack();
                }
                break;
            }
            else if (!g_Game.isGoalScored) { // scored on TEAM_2 or TEAM_4
                updateScore(ball, goal->id);
                initStarsFx();
                break;
            }
        }
    }
}

void checkLeftGoalCollision(Sprite *ball) {
    // iterate through goals on left side, check bounds
    for (int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PGOAL goal = &g_Goal[i];
        if (!goal->player->isActivated || goal->player->isDead || !goal->onLeftSide) {
            continue;
        }
        if (ball->pos.y - GOAL_MARGIN > goal->pos.top && ball->pos.y + GOAL_MARGIN < goal->pos.bot) { // removed ball radius - need another solution
            g_Game.goalID = goal->id;
            g_AnimateGoal = true;
            if (g_Game.gameMode == GAME_MODE_STORY) {
                g_Game.isGoalScored = true;
                initStarsFx();
                ballTtouchTimer = 0;
                updatePlayerLives(0);
                
                if (g_Players[0].numLives == 4 || g_Players[0].numLives == 2)
                {
                    uint8_t playerid   = g_Players[0].character.choice;
                    uint8_t computerid = g_Players[1].character.choice;

                    bool useTaunt2 = rnd.GetNumber(0, 1);
                    const char* taunt = useTaunt2 ? Dialog::quotes[playerid][computerid].taunt2
                                                   : Dialog::quotes[playerid][computerid].taunt1;
                    PrintWrapped(0, 14, 32, taunt, Align::CenterX);
                }
                
                if (!g_Game.isBoss) {
                    playCDTrack(g_Audio.currentTrack, false);
                    nextcurrentTrack();
                }
                break;
            }
            else if (!g_Game.isGoalScored) { // scored on TEAM_2 or TEAM_4
                updateScore(ball, goal->id);
                initStarsFx();
                break;
            }
        }
    }
}
