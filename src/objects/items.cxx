#include <srl.hpp>
#include "items.h"
#include "../main.h"
#include "../core/screen_transition.h"
#include "../game/gameplay.h"
#include "../vdp2/sprite_colors.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;

static bool animate_bomb = false;
static bool explode_bomb = false;
static bool bomb_heating = false;
static uint16_t bomb_timer = 0;
static Fxp item_velocity = 0.05;

void animateBombColor(bool *_do_update) {
    if (!animate_bomb) {
        return;
    }
    if (g_Game.frame % 4 == 0) {
        if (bomb_heating) {
            hsl_incSprites[HSL_BOMB].h = 180;
            bomb_heating = false;
        } 
        else {
            hsl_incSprites[HSL_BOMB].h = -180;
            bomb_heating = true;
        }
        *_do_update = true;
    }
}

void regenerateItem(void)
{
    if (g_item.scale > 0.0)
    {
        g_item.scale -= item_velocity;
        set_spr_scale_fxp(g_item._sprite, g_item.scale, g_item.scale);
        
    }
    if (g_item.scale <= 0.0)
    {
        g_item.nextItemTimer = 0;
        g_item.lastItemTimer = 0;
        g_item.isActive = false;
        g_item._sprite->active = false;
        g_item.scale = 0.0;
    }
}

void setItemPositions(void) {
    if (g_GameOptions.debug_mode && !g_GameOptions.enableItems) {
        // g_item.id = GAME_ITEM_BOMB;
        g_item.id = GAME_ITEM_FISH;
        // g_item.id = GAME_ITEM_SHROOM;
        // g_item.id = GAME_ITEM_GARF;
        // g_item.id = GAME_ITEM_CRAIG;
        // g_item.id = GAME_ITEM_MAX;
    }
    else {
        int item = rnd.GetNumber(0, 1000000);
        switch(g_Game.gameDifficulty)
        {
            // rebalance item difficulty..
            case GAME_DIFFICULTY_EASY:
                if      (item < 250000) g_item.id = GAME_ITEM_FISH;    // 25%
                else if (item < 450000) g_item.id = GAME_ITEM_BOMB;    // 20%
                else if (item < 700000) g_item.id = GAME_ITEM_SHROOM;  // 25%
                else if (item < 850000) g_item.id = GAME_ITEM_CRAIG;   // 15%
                else                    g_item.id = GAME_ITEM_GARF;    // 15%
                break;
            case GAME_DIFFICULTY_MEDIUM:
                if      (item < 220000) g_item.id = GAME_ITEM_FISH;    // 22%
                else if (item < 440000) g_item.id = GAME_ITEM_BOMB;    // 22%
                else if (item < 660000) g_item.id = GAME_ITEM_SHROOM;  // 22%
                else if (item < 860000) g_item.id = GAME_ITEM_CRAIG;   // 20%
                else                    g_item.id = GAME_ITEM_GARF;    // 14%
                break;
            case GAME_DIFFICULTY_HARD:
                if      (item < 250000) g_item.id = GAME_ITEM_FISH;    // 25%
                else if (item < 550000) g_item.id = GAME_ITEM_BOMB;    // 30%
                else if (item < 800000) g_item.id = GAME_ITEM_SHROOM;  // 25%
                else if (item < 900000) g_item.id = GAME_ITEM_CRAIG;   // 10%
                else                    g_item.id = GAME_ITEM_GARF;    // 10%
                break;
            default:
                g_item.id = GAME_ITEM_MAX;
                break;
        }
    }
    
    switch (g_item.id) {
        case GAME_ITEM_BOMB:
            reset_bomb_color();
            animate_bomb = false;
            bomb_heating = false;
            explode_bomb = false;
            bomb_timer = BOMB_TIMER;
            g_item._sprite = &bomb_item;
            sprite_frame_reset(g_item._sprite);
            break;
        case GAME_ITEM_FISH:
            g_item._sprite = &fishtank_item;
            hsl_incSprites[HSL_FISH].h -= FISH_HUE_INCREMENT;
            do_update_fish = true;
            break;
        case GAME_ITEM_SHROOM:
            g_item._sprite = &shroom_item;
            break;
        case GAME_ITEM_GARF:
            g_item._sprite = &garfield_item;
            break;
        case GAME_ITEM_CRAIG:
            g_item._sprite = &craig_item;
            break;
        default:
            break;
    }
    
    g_item.scale = 0.0;
    g_item.nextItemTimer = 0;
    g_item.lastItemTimer = 0;
    set_item_position(g_item._sprite);
    set_spr_scale_fxp(g_item._sprite, g_item.scale, g_item.scale);
    g_item._sprite->isColliding = false;
    g_item._sprite->rot.z = 0;
    g_item._sprite->active = true;
    g_item.isActive = false;
    g_item.update = false;
    g_item.isStale = false;
}

void drawGameItems(void) {    
    if (g_item._sprite->active) {
        my_sprite_draw_rot(g_item._sprite);
        item_bounce();
    }
    
    if (g_item.isStale)
    {
        return;
    }
            
    switch (g_item.id) {
        case GAME_ITEM_BOMB:
            if (g_item.scale < 2.0) {
                g_item.scale += item_velocity;
                set_spr_scale_fxp(&bomb_item, g_item.scale, g_item.scale);
                if (g_item.scale >= 2.0) {
                    g_item.isActive = true;
                }
            }
            if (explode_bomb) {
                if (g_Transition.explosion_flash) {
                    g_Transition.explosion_flash = explosionEffect();
                }
                explode_bomb = explode_animation(&bomb_item);
                if (explode_bomb == false) {
                    bomb_item.active = false;
                    g_item.isActive = false;
                }
            }
            else {
                looped_animation_pow(&bomb_item, 4);
            }
            break;
        case GAME_ITEM_FISH:
            if (g_item.scale < 2.0) {
                g_item.scale += item_velocity;
                set_spr_scale_fxp(&fishtank_item, g_item.scale, g_item.scale);
                if (g_item.scale >= 2.0) {
                    g_item.isActive = true;
                }
            }
            looped_animation_pow(&fishtank_item, 8);
            break;
        case GAME_ITEM_SHROOM:
            if (g_item.scale < 2.0) {
                g_item.scale += item_velocity;
                set_spr_scale_fxp(&shroom_item, g_item.scale, g_item.scale);
                if (g_item.scale >= 2.0) {
                    g_item.isActive = true;
                }
            }
            looped_animation_pow(&shroom_item, 4);
            hsl_incSprites[HSL_SHROOM].h += 2;
            do_update_shroom = true;
            break;
        case GAME_ITEM_GARF:
            if (g_item.scale < 1.0) {
                g_item.scale += item_velocity;
                set_spr_scale_fxp(&garfield_item, g_item.scale, g_item.scale);
                if (g_item.scale >= 1.0) {
                    g_item.isActive = true;
                }
            }
            break;
        case GAME_ITEM_CRAIG:
            if (g_item.scale < 1.6) {
                g_item.scale += item_velocity;
                set_spr_scale_fxp(&craig_item, g_item.scale, g_item.scale);
                if (g_item.scale >= 1.6) {
                    g_item.isActive = true;
                }
            }
            break;
        default:
            g_item._sprite->active = false;
            g_item.isActive = false;
            break;
    }
}

void handlePlayerItemCollision(PPLAYER player) {
    g_item.nextItemTimer = 0;
    g_item.lastItemTimer = 0;
    switch (g_item.id) {
        case GAME_ITEM_BOMB:
        {
            if (player->shield.activate == true)
            {
                handle_item_player_reaction(player);
                g_item.update = true;
            }
            else
            {
                g_item.isActive = false;
                g_item.isStale = false;
                g_item.update = false;
                explode_bomb = true;
                bomb_heating = false;
                animate_bomb = false;
                bomb_timer = 0;
                g_Transition.explosion_flash = true;
                if (!player->isExploded) {
                    player->isExploded = explodePLayer(player);
                }
            }
            g_GameOptions.bombTouchCounter++;
            break;
        }
        case GAME_ITEM_FISH:
        {
            g_item.isActive = false;
            g_item.isStale = false;
            Pcm::Play(Sounds.Game[BloopSnd]);
            
            int16_t missingLives = (int16_t)player->totalLives - (int16_t)player->numLives;
            uint8_t bonus;

            if (missingLives <= 0)
            {
                bonus = 1;
            }
            else
            {
                bonus = (uint8_t)((missingLives * missingLives) / player->totalLives);
                
                if (bonus < 1) 
                {
                    bonus = 1;
                }
            }

            player->numLives += bonus;

            uint8_t maxCap = player->totalLives * 2;
            if (player->numLives > maxCap)
            {
                player->numLives = maxCap;
            }
            
            fishtank_item.active = false;
            player->score.points += 5000;
            g_GameOptions.fishTouchCounter++;
            break;
        }
        case GAME_ITEM_SHROOM:
        {
            if (player->shield.activate == true)
            {
                handle_item_player_reaction(player);
                g_item.update = true;
            }
            else {
                g_item.isActive = false;
                g_item.isStale = false;
                if (player->isAI && g_Game.gameMode == GAME_MODE_STORY && g_Game.isBoss)
                {
                    g_item.textFramesRemaining = 3*60;
                    PrintWrapped(0, 23, 30, bossQuotes[player->character.choice].mushroom, Align::CenterX);
                }
                else
                {
                    shroom_item.active = false;
                    int16_t shroom_angle = hslSprites[p_rangeShroom.lower].h;
                    g_item.timer[player->playerID] = SHROOM_TIMER;
                    // affect the player depending on the color of the shroom
                    if ((shroom_angle > 0 && shroom_angle <= 90) || (shroom_angle > 270 && shroom_angle <= 360)) {
                        Pcm::Play(Sounds.Game[GrowSnd]);
                        player->_sprite->pos.r = PLAYER_RADIUS_LARGE;
                        player->isBig = true;
                        player->isSmall = false;
                        g_GameOptions.redShroomTouchCounter++;
                    }
                    if (shroom_angle > 90 && shroom_angle <= 270) {
                        Pcm::Play(Sounds.Game[ShrinkSnd]);
                        player->_sprite->pos.r = PLAYER_RADIUS_SMALL;
                        player->isBig = false;
                        player->isSmall = true;
                        g_GameOptions.blueShroomTouchCounter++;
                    }
                    player->score.points += 10000;
                }
            }
            break;
        }
        case GAME_ITEM_GARF:
        {
            g_item.isActive = false;
            g_item.isStale = false;
            garfield_item.active = false;
            
            if (player->isSmall)
            {
                g_item.timer[player->playerID] = 1;
            }
            
            if (g_Game.gameMode == GAME_MODE_STORY)
            {
                g_Gameplay.GameTimer = CalculateBonusSeconds(g_Gameplay.GameTimer, 5, 60, 15, TIMEOUT_STORY_MEDIUM);
                if (g_Gameplay.GameTimer > TIMER_MAX)
                    g_Gameplay.GameTimer = TIMER_MAX;
            }
            
            g_item.textFramesRemaining = 3*60;
            uint8_t quote = rnd.GetNumber(0, GARFIELD_QUOTES);
            PrintWrapped(0, 23, 30, garfieldItemQuotes[quote], Align::CenterX);
            
            player->shield.power = SHIELD_POWER * 4;
            if (touchedBy[player->playerID].touchCount == 0) {
                touchedBy[player->playerID].touchCount = 20;
            }
            else {
                touchedBy[player->playerID].touchCount *= 2;
                if (touchedBy[player->playerID].touchCount > 99) {
                    touchedBy[player->playerID].touchCount = 99;
                }
                else {
                    player->score.points += 50000;
                }
            }
            g_GameOptions.garfTouchCounter++;
            // unlock - but you have to win!
            if (g_GameOptions.garfTouchCounter >= 200) {
                characterUnlocked[CHARACTER_GARF] = true;
                Pcm::Play(Sounds.Game[StadlerSnd]);
            }
            else {
                Pcm::Play(Sounds.Game[Chain5Snd]);
            }
            break;
        }
        case GAME_ITEM_CRAIG:
        {
            g_item.isActive = false;
            g_item.isStale = false;
            craig_item.active = false;
            g_item.timer[player->playerID] = 1; // if garfield is more powerful, maybe this shouldn't be here
            
            if (g_Game.gameMode == GAME_MODE_STORY)
            {
                g_Gameplay.GameTimer = CalculateBonusSeconds(g_Gameplay.GameTimer, 3, 30, 15, TIMEOUT_STORY_MEDIUM);
                if (g_Gameplay.GameTimer > TIMER_MAX)
                    g_Gameplay.GameTimer = TIMER_MAX;
            }
                
            g_item.textFramesRemaining = 3*60;
            uint8_t quote = rnd.GetNumber(0, STADLER_QUOTES);
            PrintWrapped(0, 23, 30, stadlerItemQuotes[quote], Align::CenterX);
           
            player->shield.power = SHIELD_POWER * 2;
            player->score.points += 25000;
            g_GameOptions.craigTouchCounter++;
            // unlock - but you have to win!
            if (g_GameOptions.craigTouchCounter >= 100) {
                characterUnlocked[CHARACTER_WALRUS] = true;
                Pcm::Play(Sounds.Game[StadlerSnd]);
            }
            else {
                Pcm::Play(Sounds.Game[Chain5Snd]);
            }
            break;
        }
        default:
        {
            g_item._sprite->active = false;
            break;
        }
    }
}

void bombTimer(void) {
    if (bomb_timer < BOMB_FLASH_TIMER && !animate_bomb) {
        animate_bomb = true;
    }
    if (bomb_timer == 0 && !explode_bomb) {
        g_item.nextItemTimer = 0;
        g_item.lastItemTimer = 0;
        explode_bomb = true;
        g_Transition.explosion_flash = true;
        animate_bomb = false;
        g_item.nextItemTimer = 0;
        g_item.isActive = false;
    }
    else {
        bomb_timer--;
    }
}