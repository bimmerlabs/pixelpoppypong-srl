#pragma once

#include <srl.hpp>
#include "core/state.h"
#include "core/util.h"
#include "core/math.h"
#include "core/audio.h"
#if ENABLE_DEBUG_MODE == 1
    #include "core/debug.h"
#endif

#define VERSION "0.90.3"
#define MAX_PLAYERS 4

// Screen position
#define HORIZONTAL_RES (704)
#define VERTICAL_RES (480)
#define SCREEN_WIDTH  Fxp(HORIZONTAL_RES)
#define SCREEN_HEIGHT  Fxp(VERTICAL_RES)
#define SCREEN_RIGHT  Fxp(HORIZONTAL_RES/2)
#define SCREEN_LEFT  Fxp(-HORIZONTAL_RES/2)
#define SCREEN_MIDDLE  Fxp(0)
#define SCREEN_TOP Fxp(-VERTICAL_RES/2)
#define SCREEN_BOTTOM Fxp(VERTICAL_RES/2)

typedef struct {
    bool debug_mode;
    bool debug_display;
    bool testCollision;
    bool mesh_display;
    bool mosaic_display;
    bool use_rtc;
    bool unlockBigHeadMode;
    bool bigHeadMode;
    bool enableItems;
    bool bossMode;
    bool reservedBool;
    unsigned int bombTouchCounter;
    unsigned int fishTouchCounter;
    unsigned int redShroomTouchCounter;
    unsigned int blueShroomTouchCounter;
    unsigned int craigTouchCounter;
    unsigned int garfTouchCounter;
    unsigned int reservedInt;
} GameOptions, *PGameOptions;
    
extern GameOptions g_GameOptions;

extern SRL::Math::Random<int32_t> rnd;

// 1-4 players
#define ONE_PLAYER       (0)
#define TWO_PLAYER       (1)
#define THREE_PLAYER     (2)
#define FOUR_PLAYER      (3)

// supported game types
#define GAME_MODE_STORY   (0)
#define GAME_MODE_BATTLE  (1) // BATTLE MODE (2 OR 4 PLAYER MODE ONLY)
#define GAME_MODE_CLASSIC (2) // JUST PONG
#define GAME_MODE_MAX     (3)

// supported game difficulty
#define GAME_DIFFICULTY_EASY    (0)
#define GAME_DIFFICULTY_MEDIUM  (1)
#define GAME_DIFFICULTY_HARD    (2)
#define GAME_DIFFICULTY_MAX     (3)

// represents game state
typedef struct _GAME
{
    int frame; // frame counter
    
    Angle cursor_angle; // for title & pawsed menus
    
    // current game state
    GAME_STATE gameState;
    GAME_STATE nextState;
    GAME_STATE lastState;

    // number of players (I think this needs to be signed)
    int8_t minPlayers;
    int8_t maxPlayers;
    int8_t numPlayers;
    int8_t currentNumPlayers;
    
    // classic, story, battle
    int8_t gameMode;

    // easy, medium, hard
    int8_t gameDifficulty;
    
    // // gameplay states
    // RoundState roundState;
    
    // real time clock
    uint8_t timeSlot;
    uint8_t timeSeason;
    
    // TIMERS
    // uint16_t endDelayTimer;
    uint16_t BeginTimer;
    uint16_t roundBeginTimer;
    uint16_t dropBallTimer;
    // bool time_over;

    bool selectStoryCharacter;
    bool isBoss;

    // is the game loading?
    bool isLoading;
    bool isSoundLoading;

    // is the game is paused?
    bool isPaused;

    // did somebody score a goal?
    bool isGoalScored;
    signed char goalID;

    // is the game finished?
    bool isRoundOver; // to be deleted
    int countofRounds;
    
    // int winner;
    
    // is the game playing?
    bool isActive;
    bool isBallActive;
    
    bool explodeBall;
    
    bool vblankClearScreen;
    
} GAME, *PGAME;

extern GAME g_Game;

#ifdef __cplusplus
extern "C" {
#endif

void initGame(void);

#ifdef __cplusplus
}
#endif