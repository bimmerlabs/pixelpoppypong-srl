#pragma once
#include "player.h"
#include "../core/assets.h"
#include "../game/physics.h"

#define SHROOM_TIMER (15 * 60)
#define BOMB_TIMER (6 * 60)
#define BOMB_FLASH_TIMER (3 * 60)
#define FISH_HUE_INCREMENT 50

#define ITEM_FRICTION_Y Fxp(1.75)
#define ITEM_FRICTION_X Fxp(1.15)

typedef enum _GAME_ITEMS
{
    GAME_ITEM_BOMB = 0,
    GAME_ITEM_FISH,
    GAME_ITEM_SHROOM,
    GAME_ITEM_GARF,
    GAME_ITEM_CRAIG,
    GAME_ITEM_MAX,
} GAME_ITEMS;

typedef struct {
    unsigned int id;
    unsigned int timer[MAX_PLAYERS];
    bool isActive;
    bool update;
    Sprite *_sprite;
} Item;

extern Item g_item;

static Fxp maxItemVelocity = MEDIUM_MAX_VELOCITY;

#ifdef __cplusplus
extern "C" {
#endif

void animateBombColor(bool *_do_update);

void setItemPositions(void);
void drawGameItems(void);
void handlePlayerItemCollision(PPLAYER player);

void bombTimer(void);

static inline void handle_item_player_reaction(PPLAYER player) {    
    Fxp dx = g_item._sprite->pos.x - player->_sprite->pos.x;
    Fxp dy = g_item._sprite->pos.y - player->_sprite->pos.y;

    Fxp distance_squared = dx * dx + dy * dy;
    
    Fxp distance = distance_squared.Sqrt();
    
    Fxp collision_normal_x = dx / distance;
    Fxp collision_normal_y = dy / distance;
    
    Fxp dot_product = player->_sprite->vel.x * collision_normal_x + player->_sprite->vel.y * collision_normal_y;
    
    g_item._sprite->vel.x = dot_product * collision_normal_x * player->power * 0.1;
    g_item._sprite->vel.y = dot_product * collision_normal_y * player->power * 0.1; 
    g_item._sprite->vel.z = g_item._sprite->vel.y * -1;
    
    // Apply player's movement influence
    Fxp rel_vel_x = player->_sprite->vel.x * Fxp(0.20);
    if ((player->onLeftSide && player->_sprite->vel.x > 0) || 
        (!player->onLeftSide && player->_sprite->vel.x < 0)) {
        g_item._sprite->vel.x += rel_vel_x;
    }
}

static inline void item_bounce(void) {
    if (!g_item.update)
    {
        return;
    }
    // Update position based on velocity
    g_item._sprite->pos.x += g_item._sprite->vel.x;
    g_item._sprite->pos.y += g_item._sprite->vel.y;
    Angle VelZ = Angle::FromDegrees(g_item._sprite->vel.z);
    g_item._sprite->rot.z += VelZ;

    // Check for collisions with walls
    if (g_item._sprite->pos.x >= SCREEN_RIGHT) {
        g_item._sprite->pos.x = SCREEN_RIGHT;
        Pcm::Play(Sounds.Game[BumpSnd], PlayMode::Volatile, 7);
        g_item._sprite->vel.x = -g_item._sprite->vel.x; // Reverse X velocity
        // moving right
        if (g_item._sprite->vel.x > MIN_VELOCITY_X) {
            g_item._sprite->vel.x -= ITEM_FRICTION_X;
        }
        // moving left
        else if (g_item._sprite->vel.x < -MIN_VELOCITY_X) {
            g_item._sprite->vel.x += ITEM_FRICTION_X;
        }

        // Adjust Z velocity for horizontal collision
        g_item._sprite->vel.z = calculate_z_velocity(g_item._sprite->vel.x, g_item._sprite->vel.y, true);        
    }
    if (g_item._sprite->pos.x <= SCREEN_LEFT) {
        g_item._sprite->pos.x = SCREEN_LEFT;
        Pcm::Play(Sounds.Game[BumpSnd], PlayMode::Volatile, 7);
        g_item._sprite->vel.x = -g_item._sprite->vel.x; // Reverse X velocity
        // moving right
        if (g_item._sprite->vel.x > MIN_VELOCITY_X) {
            g_item._sprite->vel.x -= ITEM_FRICTION_X;
        }
        // moving left
        else if (g_item._sprite->vel.x < -MIN_VELOCITY_X) {
            g_item._sprite->vel.x += ITEM_FRICTION_X;
        }

        // Adjust Z velocity for horizontal collision
        g_item._sprite->vel.z = calculate_z_velocity(g_item._sprite->vel.x, g_item._sprite->vel.y, true);        
    }
    if (g_item._sprite->pos.y >= SCREEN_BOTTOM - g_item._sprite->pos.r) {
        g_item._sprite->pos.y = SCREEN_BOTTOM - g_item._sprite->pos.r;
        Pcm::Play(Sounds.Game[BumpSnd], PlayMode::Volatile, 7);
        g_item._sprite->vel.y = -g_item._sprite->vel.y; // Reverse Y velocity
        // moving up
        if (g_item._sprite->vel.y < -MIN_VELOCITY_Y) {
            g_item._sprite->vel.y += ITEM_FRICTION_Y;
        }
        // Adjust Z velocity for vertical collision
        g_item._sprite->vel.z = calculate_z_velocity(g_item._sprite->vel.x, g_item._sprite->vel.y, false);
    }
    if (g_item._sprite->pos.y <= SCREEN_TOP + g_item._sprite->pos.r) {
        g_item._sprite->pos.y = SCREEN_TOP + g_item._sprite->pos.r;
        Pcm::Play(Sounds.Game[BumpSnd], PlayMode::Volatile, 7);
        g_item._sprite->vel.y = -g_item._sprite->vel.y; // Reverse Y velocity
        // moving down
        if (g_item._sprite->vel.y > MIN_VELOCITY_Y) {
            g_item._sprite->vel.y -= ITEM_FRICTION_Y;
        }
        // Adjust Z velocity for vertical collision
        g_item._sprite->vel.z = calculate_z_velocity(g_item._sprite->vel.x, g_item._sprite->vel.y, false);
    }

    g_item._sprite->vel.x *= 0.99;
    g_item._sprite->vel.y *= 0.99;
    g_item._sprite->vel.z *= 0.99;
    
    // Llimit g_item._sprite speed
    if (g_item._sprite->vel.x > maxItemVelocity) {
        g_item._sprite->vel.x = maxItemVelocity;
    }
    else if (g_item._sprite->vel.x < -maxItemVelocity) {
        g_item._sprite->vel.x = -maxItemVelocity;
    }
    if (g_item._sprite->vel.y > maxItemVelocity) {
        g_item._sprite->vel.y = maxItemVelocity;
    }
    else if (g_item._sprite->vel.y < -maxItemVelocity) {
        g_item._sprite->vel.y = -maxItemVelocity;
    }
    
    adjust_xy_velocity_based_on_spin(g_item._sprite);
    
    // Keep rotation within 0-359 degrees
    if (ABS(g_item._sprite->rot.z) == 360) {
        g_item._sprite->rot.z = 0;
    }
}

#ifdef __cplusplus
}
#endif