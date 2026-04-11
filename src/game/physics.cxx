#include "physics.h"
#include "gameplay.h"
#include "../specialfx/particlefx.h"
#include "../core/audio.h"
#include "../core/math.h"
#include "../core/screen_transition.h"
#include "../objects/goal.h"

using namespace SRL::Math;

extern PLAYER g_Players[MAX_PLAYERS];

BallTouchTracker touchedBy[MAX_PLAYERS];
unsigned int ballTtouchTimer = 0;
int8_t lastTouchedBy = -1;
int8_t previouslyTouchedBy[TOUCHEDBY_BUFFER];
    
static Fxp maxBallVelocity = 0;

void initTouchCounter(uint8_t resetTouchCount) { // why is this not a bool?
    for(unsigned int i = 0; i < MAX_PLAYERS; i++)
    {
        touchedBy[i].onLeftSide = false;
        touchedBy[i].hasTouched = false;
        if (resetTouchCount == 1) {
            touchedBy[i].touchCount = 0;
        }
        touchedBy[i].teamChoice = 0;
    }
    ballTtouchTimer = 0;
    lastTouchedBy = -1;
    for (int i = 0; i < TOUCHEDBY_BUFFER; i++) {
        previouslyTouchedBy[i] = -1;
    }
}

void stopBallMovement(Sprite *ball) {
    ball->vel.x = 0;
    ball->vel.y = 0;
    ball->vel.z = 0;
}

// Function to initialize the ball's movement
void start_ball_movement(Sprite *ball) {    
    switch(g_Game.gameDifficulty)
    {
        case GAME_DIFFICULTY_EASY:
            maxBallVelocity = EASY_MAX_VELOCITY;
            ball->vel.x = Fxp::Convert(static_cast<int16_t>(rnd.GetNumber(4, 6)));
            ball->vel.y = Fxp::Convert(static_cast<int16_t>(rnd.GetNumber(1, 5)));
            ball->vel.z = Fxp::Convert(static_cast<int16_t>(rnd.GetNumber(1, 10))); // originally 5
            break;
        case GAME_DIFFICULTY_HARD:
            maxBallVelocity = HARD_MAX_VELOCITY;
            ball->vel.x = Fxp::Convert(static_cast<int16_t>(rnd.GetNumber(5, 9)));
            ball->vel.y = Fxp::Convert(static_cast<int16_t>(rnd.GetNumber(1, 8)));
            ball->vel.z = Fxp::Convert(static_cast<int16_t>(rnd.GetNumber(1, 40))); // originally 20
            break;
        default: // GAME_DIFFICULTY_MEDIUM
            maxBallVelocity = MEDIUM_MAX_VELOCITY;
            ball->vel.x = Fxp::Convert(static_cast<int16_t>(rnd.GetNumber(4, 7)));
            ball->vel.y = Fxp::Convert(static_cast<int16_t>(rnd.GetNumber(1, 6)));
            ball->vel.z = Fxp::Convert(static_cast<int16_t>(rnd.GetNumber(1, 20))); // originally 10
            break;
    }

    // Randomize direction
    Fxp rotZ = ball->rot.z.ToDegrees();
    if (rnd.GetNumber(0, 999 * rotZ.As<int32_t>()) % 2 == 0) // modulus
    {
        ball->vel.x = -ball->vel.x;
    }
    if (rnd.GetNumber(0, 999 * rotZ.As<int32_t>()) % 2 == 0) // modulus
    {
        ball->vel.y = -ball->vel.y;
    }
    if (rnd.GetNumber(0, 99999 * rotZ.As<int32_t>()) % 2 == 0) // modulus
    {
        ball->vel.z = -ball->vel.z;
    }
    
    // game is only active if ball is moving
    g_Game.isActive = true;
    g_Game.explodeBall = false;
}

// inline?
void adjust_xy_velocity_based_on_spin(Sprite *ball) {
    // Calculate tangential velocity
    Fxp tangential_velocity = ball->pos.r * ball->vel.z / 360;

    // Scale tangential velocity by friction
    Fxp friction_effect = tangential_velocity * FRICTION_COEFFICIENT;

    // SRL::Debug::Print(2, 13, "TengentVel:%3d    ", tangential_velocity.As<int16_t>());
    // SRL::Debug::Print(2, 14, "Friction:%3d    ", friction_effect.As<int16_t>());
    
    // // Adjust x and y velocities
    ball->vel.x += friction_effect;
    ball->vel.y -= friction_effect;
}

// Function to update the ball's position and check for collisions
void update_ball(Sprite *ball) {
       
    // Update position based on velocity
    ball->pos.x += ball->vel.x;
    ball->pos.y += ball->vel.y;
    Angle VelZ = Angle::FromDegrees( ball->vel.z);
    ball->rot.z += VelZ;
    
    if (!g_Game.explodeBall) {
        auto spin = ABS(ball->vel.z.As<int16_t>());
        if (spin > 50) {
            ball->id = ball->anim[0].asset +6;
        }
        else if (spin > 40 && spin <= 50) {
            ball->id = ball->anim[0].asset + 5;
        }
        else if (spin > 30 && spin <= 40) {
            ball->id = ball->anim[0].asset + 4;
        }
        else if (spin > 20 && spin <= 30) {
            ball->id = ball->anim[0].asset + 3;
        }
        else if (spin > 10 && spin <= 20) {
            ball->id = ball->anim[0].asset + 1;
        }
        else if (spin > 0 && spin <= 10) {
            ball->id = ball->anim[0].asset;
        }
    }
    
    if (!g_GameOptions.testCollision) {
        // Check for collisions with goals
        if (ball->pos.x >= GOAL_RIGHT_BOUNDS) {
            checkRightGoalCollision(ball);
        }
        else if (ball->pos.x <= GOAL_LEFT_BOUNDS) {
            checkLeftGoalCollision(ball);
        }
    }
    
    // Check for collisions with walls
    if (ball->pos.x >= SCREEN_RIGHT) {
        ball->pos.x = SCREEN_RIGHT;
        Pcm::Play(Sounds.Game[BumpSnd], PlayMode::Volatile, 7);
        ball->vel.x = -ball->vel.x; // Reverse X velocity
        // moving right
        if (ball->vel.x > MIN_VELOCITY_X) {
            ball->vel.x -= BALL_FRICTION_X;
            if (ball->vel.x < MIN_VELOCITY_X)
                ball->vel.x = MIN_VELOCITY_X;
        }
        // moving left
        else if (ball->vel.x < -MIN_VELOCITY_X) {
            ball->vel.x += BALL_FRICTION_X;
            if (ball->vel.x > MIN_VELOCITY_X)
                ball->vel.x = -MIN_VELOCITY_X;
        }

        // Adjust Z velocity for horizontal collision
        ball->vel.z = calculate_z_velocity(ball->vel.x, ball->vel.y, true);        
    }
    if (ball->pos.x <= SCREEN_LEFT) {
        ball->pos.x = SCREEN_LEFT;
        Pcm::Play(Sounds.Game[BumpSnd], PlayMode::Volatile, 7);
        ball->vel.x = -ball->vel.x; // Reverse X velocity
        // moving right
        if (ball->vel.x > MIN_VELOCITY_X) {
            ball->vel.x -= BALL_FRICTION_X;
            if (ball->vel.x < MIN_VELOCITY_X)
                ball->vel.x = MIN_VELOCITY_X;
        }
        // moving left
        else if (ball->vel.x < -MIN_VELOCITY_X) {
            ball->vel.x += BALL_FRICTION_X;
            if (ball->vel.x > MIN_VELOCITY_X)
                ball->vel.x = -MIN_VELOCITY_X;
        }

        // Adjust Z velocity for horizontal collision
        ball->vel.z = calculate_z_velocity(ball->vel.x, ball->vel.y, true);        
    }
    if (ball->pos.y >= SCREEN_BOTTOM - ball->pos.r) {
        ball->pos.y = SCREEN_BOTTOM - ball->pos.r;
        Pcm::Play(Sounds.Game[BumpSnd], PlayMode::Volatile, 7);
        ball->vel.y = -ball->vel.y; // Reverse Y velocity
        // moving up
        if (ball->vel.y < -MIN_VELOCITY_Y) {
            ball->vel.y += BALL_FRICTION_Y;
            if (ball->vel.y > MIN_VELOCITY_Y)
                ball->vel.y = -MIN_VELOCITY_Y;
        }
        // Adjust Z velocity for vertical collision
        ball->vel.z = calculate_z_velocity(ball->vel.x, ball->vel.y, false);
    }
    if (ball->pos.y <= SCREEN_TOP + ball->pos.r) {
        ball->pos.y = SCREEN_TOP + ball->pos.r;
        Pcm::Play(Sounds.Game[BumpSnd], PlayMode::Volatile, 7);
        ball->vel.y = -ball->vel.y; // Reverse Y velocity
        // moving down
        if (ball->vel.y > MIN_VELOCITY_Y) {
            ball->vel.y -= BALL_FRICTION_Y;
            if (ball->vel.y < MIN_VELOCITY_Y)
                ball->vel.y = MIN_VELOCITY_Y;
        }
        // Adjust Z velocity for vertical collision
        ball->vel.z = calculate_z_velocity(ball->vel.x, ball->vel.y, false);
    }

    // control ball speed
    if (ball->vel.x > maxBallVelocity) {
        ball->vel.x = maxBallVelocity;
    }
    else if (ball->vel.x < -maxBallVelocity) {
        ball->vel.x = -maxBallVelocity;
    }
    if (ball->vel.y > maxBallVelocity) {
        ball->vel.y = maxBallVelocity;
    }
    else if (ball->vel.y < -maxBallVelocity) {
        ball->vel.y = -maxBallVelocity;
    }
    
    adjust_xy_velocity_based_on_spin(ball);
    
    // Keep rotation within 0-359 degrees
    if (ABS(ball->rot.z) == 360) {
        ball->rot.z = 0;
    }
    
    starCfg.spawnX   = ball->pos.x;
    starCfg.spawnY   = ball->pos.y;
    starCfg.maxVX    = -ball->vel.x * 0.1;
    starCfg.maxVY    = -ball->vel.y * 0.1;
    Fxp emitRate     = 60 / ball->vel.z;
    if (emitRate < 0)
        emitRate *= -1;
    if (emitRate < 1)
        emitRate = 1;
    starCfg.emitRate = emitRate.RawValue() >> 16;
}

// SIMPLER / BETTER? (ball/circle)
void handle_ball_player_reaction(Sprite *ball, PPLAYER player, int32_t distance_squared, int32_t dx, int32_t dy) {
    if (g_Game.explodeBall && !player->isExploded && !player->shield.activate) {
        player->isExploded = explodePLayer(player);
        player->_sprite->isColliding = false;
        return;
    }
    
    Fxp distance = Fxp::Convert(static_cast<int16_t>(ApproximateIntegerSqrt(distance_squared)));
    // Fxp distance = distance_squared.Sqrt();
    
    // Calculate relative position vector
    Fxp collision_normal_x = Fxp::Convert(static_cast<int16_t>(dx)) / distance;
    Fxp collision_normal_y = Fxp::Convert(static_cast<int16_t>(dy)) / distance;

    // Compute the dot product of relative velocity and collision normal
    Fxp dot_product = ball->vel.x * collision_normal_x + ball->vel.y * collision_normal_y;

    if (dot_product > 0) { // remove?
        // Ball is moving away from the player; no need to adjust velocity
        return;
    }

    player->_sprite->isColliding = true;
        
  if (!g_GameOptions.testCollision) {
    // Reflect the ball's velocity along the collision normal, factoring in player's movement    
    ball->vel.x -= dot_product * collision_normal_x * player->power;
    ball->vel.y -= dot_product * collision_normal_y * player->power;
    
    // Apply player's movement influence
    Fxp rel_vel_x = player->_sprite->vel.x * Fxp(0.35);
    if ((player->onLeftSide && player->_sprite->vel.x > 0) || 
        (!player->onLeftSide && player->_sprite->vel.x < 0)) {
        ball->vel.x += rel_vel_x;
    }
  }
}

bool detect_player_ball_collision(Sprite *ball, PPLAYER player) {
    if (player->isDead) {
        return false;
    }
    
    // don't check collision behind player
    if (player->onLeftSide && player->_sprite->pos.x > ball->pos.x) {
        player->_sprite->isColliding = false;
        return false;
    }
    if (!player->onLeftSide && player->_sprite->pos.x < ball->pos.x) {
        player->_sprite->isColliding = false;
        return false;
    }
    
    // Relative position vector
    int32_t dx = ball->pos.x.As<int32_t>() - player->_sprite->pos.x.As<int32_t>();
    int32_t dy = ball->pos.y.As<int32_t>() - player->_sprite->pos.y.As<int32_t>();
    
    // Distance squared between ball and player center
    int32_t distance_squared = dx * dx + dy * dy;
    
    // SRL::Debug::Print(2, 13, "Distance Sqrd:%3d    ", distance_squared);
    
    // Radius of the player (used for the semicircle)
    Fxp player_radius = player->_sprite->pos.r;
    
    // **Step 1: Check collision with the rectangle (depends on player side)**
    Fxp player_left, player_right, player_top, player_bottom;
    if (player->onLeftSide) {
        // Rectangle extends to the **left** of the semicircle
        player_left   = player->_sprite->pos.x - player_radius;
        player_right  = player->_sprite->pos.x;
        // pcm_parameter_change(Sounds.MeowId, 1, PCM_PAN_RIGHT);
        // pcm_parameter_change(Sounds.MeowId, 7, PCM_PAN_LEFT);
    } else {
        // Rectangle extends to the **right** of the semicircle
        player_left   = player->_sprite->pos.x;
        player_right  = player->_sprite->pos.x + player_radius;
        // pcm_parameter_change(Sounds.MeowId, 7, PCM_PAN_RIGHT);
        // pcm_parameter_change(Sounds.MeowId, 1, PCM_PAN_LEFT);
    }
    player_top    = player->_sprite->pos.y - player_radius;
    player_bottom = player->_sprite->pos.y + player_radius;

    // Check if the ball is inside the rectangle
    if (ball->pos.x >= player_left && ball->pos.x <= player_right &&
        ball->pos.y >= player_top && ball->pos.y <= player_bottom) {
        if (!g_Game.explodeBall) {
            updateBallTouch(player);
        }
        if (g_GameOptions.enableMeows && !player->_sprite->isColliding) {
            playCatSound();
        }
        handle_ball_player_reaction(ball, player, distance_squared, dx, dy);
        return true;
    }    
    
    // **Step 2: Check collision with the semicircle**
    int32_t radius_sum = player_radius.As<int32_t>() + ball->pos.r.As<int32_t>();
    int32_t radius_squared = radius_sum * radius_sum;

    // SRL::Debug::Print(2, 14, "Radius Sqrd:%3d    ", radius_squared);
    
    if (distance_squared <= radius_squared) {
        if (!g_Game.explodeBall) {
            updateBallTouch(player);
        }
        if (g_GameOptions.enableMeows && !player->_sprite->isColliding) {
            playCatSound();
        }
        handle_ball_player_reaction(ball, player, distance_squared, dx, dy);
        return true;
    }

    // No collision
    player->_sprite->isColliding = false;
    return false;
}

// distance formula without the square root
// move to items?
bool checkItemDistance(Sprite *player, Sprite *item)
{
    if (!g_Game.isActive) {
        return false;
    }
    
    int32_t total_radius = player->pos.r.As<int32_t>() + ITEM_RADIUS;
    int32_t dist = total_radius * total_radius;
    
    int32_t x_dist = player->pos.x.As<int32_t>() - item->pos.x.As<int32_t>();
    x_dist = x_dist * x_dist;

    int32_t y_dist = player->pos.y.As<int32_t>() - item->pos.y.As<int32_t>();
    y_dist = y_dist * y_dist;

    if(dist > x_dist + y_dist)
    {
        return true;
    }
    return false;
}
