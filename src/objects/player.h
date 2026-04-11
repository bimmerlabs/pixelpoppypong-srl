#pragma once
#include <srl.hpp>
#include "../core/assets.h"
#include "../core/sprites.h"
#include "../core/input.h"
#include "characters.h"
#include "object.h"
#include "teams.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;

#define NOT_PLAYING 0
#define PLAYING 1

#define X_SPEED_INC Fxp(1.5)
#define Y_SPEED_INC Fxp(5.0)

#define MAX_Y_SPEED Fxp(15.0)
#define MAX_X_SPEED Fxp(10.0)
#define AI_X_SPEED  Fxp(10.0)

#define TEST Fxp(20)
#define PLAYER_HEIGHT Fxp(20)
#define PLAYER_WIDTH Fxp(40)
#define PLAYER_BOUNDARY_RIGHT  Fxp(328.0)
#define PLAYER_BOUNDARY_LEFT  Fxp(-328.0)
#define PLAYER_BOUNDARY_MIDDLE  Fxp(8)
#define PLAYER_BOUNDARY_MIDDLE_INACTIVE  Fxp(120)

#define PLAYER_MOVEMENT_SPEED Fxp(0.0015)

#define PLAYER_X 340
#define PLAYER_Y 110
#define PLAYER_DEPTH 110
#define PLAYER_RADIUS Fxp(27)
#define SHIELD_RADIUS Fxp(60)
#define SHIELD_OFFSET Fxp(32)
#define SHIELD_POWER 26
#define SHIELD_COST  5
#define SHIELD_REGEN_FAST 8 // POWER OF 2!!
#define SHIELD_REGEN_SLOW 16 // POWER OF 2!!
#define BOUNDARY_SHIELD_REGEN_FAST  Fxp(280.0)
#define BOUNDARY_SHIELD_REGEN_SLOW  Fxp(180.0)

#define PLAYER_RADIUS_SMALL Fxp(10)
#define PLAYER_RADIUS_LARGE Fxp(60)
#define SHIELD_RADIUS_SMALL Fxp(30)
#define SHIELD_RADIUS_LARGE Fxp(100)

#define ATTACK1 Fxp(10)
#define ATTACK1_COST 4
#define ATTACK2 Fxp(20)
#define ATTACK2_COST 6
#define ATTACK_FRAMES 8 // POWER OF 2!!

#define LARGE_PLAYER_SPRITE Fxp(4)
#define SMALL_PLAYER_SPRITE Fxp(1)
#define NORMAL_PLAYER_SPRITE Fxp(2)
#define PLAYER_SPRITE_RATE Fxp(0.1)


typedef enum _PLAYER_STATE
{
    PLAYER_STATE_ACTIVE = 0,
    PLAYER_STATE_DEAD,
} PLAYER_STATE;

typedef struct _SCORE
{
    uint8_t stars;
    int8_t continues;
    unsigned int total;  // total score (story mode)
    unsigned int points; // round score
    unsigned int lastMillion;

} SCORE, *PSCORE;

typedef struct _SHIELD
{
    uint8_t power;
    bool activate;
} SHIELD;

typedef struct _PLAYER
{
    FIXED_POSITION curPos;
    SCORE score;
    CHARACTER character;
    
    // 0-11, controller ID
    PINPUT input;
    int playerID;

    // player
    bool startSelection;
    bool isReady;
    bool pressedB;
    bool pressedStart;
    bool isPlaying;
    bool isActivated;
    bool isDead;
    bool onLeftSide;
    bool scored;
    bool isAI;
    bool isExploded;
    bool isBig;
    bool isSmall;
    int numLives;
    int totalLives;
    
    // Team (replaces team struct values)
    short teamChoice;
    bool teamSelected;
    
    // Attributes from the selected character
    Fxp maxSpeed;
    Fxp acceleration;
    Fxp basePower; // from the character
    Fxp power; // based on inputs / game factors
    
    // FOR GOAL MOVEMENT
    Fxp goalCenterThresholdMax;
    Fxp goalCenterThresholdMin;
    
    // ATTACK
    bool attack1;
    uint8_t attack1Frames;
    bool attack2;
    uint8_t attack2Frames;
    
    // SHIELD
    SHIELD shield;
    
    // how long the mushroom effect lasts
    int shroomFrames; 

    // used for movement acceleration
    bool moveHorizontal;
    bool moveVertical;
    
    // sprites
    Sprite *_bg;
    Sprite *_cursor[2];
    Sprite *_sprite;
    Sprite *_portrait;
    Fxp shield_pos;

} PLAYER, *PPLAYER;

extern PLAYER g_Players[MAX_PLAYERS];

#ifdef __cplusplus
extern "C" {
#endif

void speedLimitPlayer(PPLAYER player);
void boundPlayer(PPLAYER player);
void explodeNeighbors(PPLAYER player);

void regenPlayerPower(PPLAYER player);
void playerAttack(PPLAYER player);
void getClassicModeInput(void);
void getPlayersInput(void);
void updatePlayers(void);

void initPlayers(bool resetInputs = false); // resetting inputs seems kind of confusing.  only reset on multiplayer inputs?
void switchPlayerPosition(PPLAYER player);
void initAiPlayers(void);
void initStoryCharacters(void);
void nextStoryCharacter(void);
void initVsModePlayers(void);
void initDemoPlayers(void);

void assignCharacterSprite(PPLAYER player);
void assignCharacterStats(PPLAYER player);

int getLives(PPLAYER player);
int getStars(void);
void getContinues(void);
void resetPlayerScores(void);
void resetPlayerAttacks(void);
void spawnPlayers(void);
bool explodePLayer(PPLAYER player);
void killPlayer(int8_t playerID);
void updatePlayerLives(uint8_t scoredOnPlayerID);

void cacheInputDirectionPlayer(PPLAYER player, bool* up, bool* down, bool* left, bool *right);

static inline void drawPlayers(void)
{
    for(int8_t i = 0; i <= g_Game.numPlayers; i++)
    {
        PPLAYER player = &g_Players[i];

        if (!player->isActivated || player->isDead) {
            continue;
        }
        my_sprite_draw(player->_sprite);
        // if () {
            looped_animation_pow(player->_sprite, 4); // TODO: change animations based on player input
        // }
    }
}

static inline bool growPlayerSprite(PPLAYER player, Fxp targetSize)
{
    if (player->_sprite->scl.x < targetSize) {
        player->_sprite->scl.x += PLAYER_SPRITE_RATE;
        player->_sprite->scl.y += PLAYER_SPRITE_RATE;
        shield[player->playerID].scl.x = player->_sprite->scl.x;
        shield[player->playerID].scl.y = player->_sprite->scl.y;
        return true;
    }
    // SRL::Debug::Print(22, 9, "BigTargetSize %d", targetSize.As<int16_t>());
    return false;
}

static inline bool shrinkPlayerSprite(PPLAYER player, Fxp targetSize)
{
    if (player->_sprite->scl.x > targetSize) {
        player->_sprite->scl.x -= PLAYER_SPRITE_RATE;
        player->_sprite->scl.y -= PLAYER_SPRITE_RATE;
        shield[player->playerID].scl.x = player->_sprite->scl.x;
        shield[player->playerID].scl.y = player->_sprite->scl.y;
        return true;
    }
    // SRL::Debug::Print(22, 10, "SmallTargetSize %d", targetSize.As<int16_t>());
    return false;
}

static inline void changePlayerSize(PPLAYER player, unsigned int timer)
{
    int i = player->playerID;
    
    if (player->isBig) {
        if (timer == 0) {
        Pcm::Play(Sounds.Game[ShrinkSnd]);
        player->isBig = shrinkPlayerSprite(player, NORMAL_PLAYER_SPRITE);
        }
        else {
        growPlayerSprite(player, LARGE_PLAYER_SPRITE);
        }
    }
    if (player->isSmall)
    {
            if (timer == 0)
            {
                Pcm::Play(Sounds.Game[GrowSnd]);
                player->isSmall = growPlayerSprite(player, NORMAL_PLAYER_SPRITE);
            }
        else
        {
            shrinkPlayerSprite(player, SMALL_PLAYER_SPRITE);
        }
    }
}

#ifdef __cplusplus
}
#endif