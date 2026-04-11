#pragma once

#include <srl.hpp>
#include "../main.h"
#include "sprites.h"
#include "pcmsys.h"
#include "../vdp2/palette.h"
#include "../vdp2/nbg2.h"
#include <tmsf.hpp>

#define NUM_PAW_SPRITES 5
#define NUM_POPPY_SPRITES 7

#define NUM_CHARACTER_SPRITES 12
#define NUM_X_SPRITES 1
#define NUM_PCURSOR_SPRITES 4

#define NUM_FONT_CHARS 40

#define NUM_TITLE_MENU_TEXT 12
#define NUM_TITLE_MENU_ARROWS 4

#define NUM_GOAL_SPRITES 4
#define NUM_TIMER_SPRITES 12
#define NUM_HEART_SPRITES 4
#define NUM_SHIELD_SPRITES 7

#define NUM_MENUBG_SPRITES 9

#define NUM_BOMB_SPRITES 4
#define NUM_EXPLOD_SPRITES 6
#define NUM_FISH_SPRITES 4
#define NUM_SHROOM_SPRITES 8

using namespace SRL::Types;
using namespace SRL::Math::Types;

// tmsf format loads in alphabetical order
typedef enum
{
    CORE_SPRITE_CURSOR = 0,
    CORE_SPRITE_MENUBG,
    CORE_SPRITE_POPPY,
    CORE_SPRITE_PUMPKIN,
    CORE_SPRITE_MAX,
} CORE_SPRITES;

typedef enum
{
    TITLE_SPRITE_ARROWS = 0,
    TITLE_SPRITE_LOGO,
    TITLE_SPRITE_PPPLOGO,
    TITLE_SPRITE_TMENU,
    TITLE_SPRITE_MAX,
} TITLE_SPRITES;

typedef enum
{
    TEAM_SPRITE_METER = 0,
    TEAM_SPRITE_PAWS,
    TEAM_SPRITE_PORTRAIT,
    TEAM_SPRITE_SELECT1,
    TEAM_SPRITE_SELECT2,
    TEAM_SPRITE_MAX,
} TEAM_SPRITES;

typedef enum
{
    GAME_SPRITE_BOMB = 0,
    GAME_SPRITE_CORN, // CANDY CORN (HEARTS)
    GAME_SPRITE_CRAIG,
    GAME_SPRITE_EXPLOD,
    GAME_SPRITE_FISH,
    GAME_SPRITE_GARF,
    GAME_SPRITE_GOAL,
    GAME_SPRITE_HEARTS,
    GAME_SPRITE_TIMER,
    GAME_SPRITE_SHIELD,
    GAME_SPRITE_SHROOM,
    GAME_SPRITE_X,
    GAME_SPRITE_MAX,
} GAME_SPRITES;

typedef enum _MEOW
{
    MEOW1 = 0,
    MEOW2,
    MEOW3,
    MEOW4,
    MEOW5,
    MEOW6,
    MEOW7,
    MEOW8,
    MEOW9,
    MEOW_MAX,
} MEOW;

// holds sprite and audio assets
typedef struct _assets
{
    
    bool coreAssetsLoaded;
    bool titleAssetsLoaded;
    bool characterAssetsLoaded;    
    bool NameEntryAssetsLoaded;
    bool GameplayAssetsLoaded;
    
    // audio assets
    // CORE / MENU SOUNDS
    short cancelPcm8; // b button
    short cursorPcm8; // d-pad
    short nextPcm8;   // normal menu selection
    short startPcm8;  // start button first press
    short tickPcm8;   // analog adjustment
    
    // GAMEPLAY SOUNDS
    short gameOverPcm8;
    short scoreAddPcm8;
    short scoreTotalPcm8;
    short chain0Pcm8;
    short chain1Pcm8;
    short chain2Pcm8;
    short chain3Pcm8;
    short chain5Pcm8;
    short explod1Pcm8;
    short growPcm8;
    short shrinkPcm8;
    short bloopPcm8;
    short stadlerPcm8;
    short dropPcm8;
    short bouncePcm8;
    short shieldPcm8;
    // short rechargePcm8;
    short countdownPcm8;
    short winPcm8;
    short bumpPcm16;
    
    // CAT SOUNDS
    short meowPcm8[9];
    short meowID;
    
    bool GameplaySoundsLoaded;
    
    // NAME ENTRY SOUNDS
    short name_ketPcm8;
    short name_curPcm8;
    short name_canPcm8;
    short name_brkPcm8;
    short load_okPcm8;
    bool NameEntrySoundsLoaded;

} ASSETS, *PASSETS;

extern ASSETS g_Assets;

extern TilemapObject* coreTiles;
extern TilemapObject* titleTiles;
extern TilemapObject* characterTiles;
extern TilemapObject* gameplayTiles;
extern TilemapObject* fontTiles;

#ifdef __cplusplus
extern "C" {
#endif

// assets
void loadCoreAssets(void);
void loadCoreSoundAssets(void);

void loadTitleScreenAssets(void);

void loadCharacterAssets(void);
void loadGameAssets(void);
bool loadGameplaySoundAssets(void);

void loadNameEntryAssets(void);
bool loadNameEntrySoundAssets(void);

void unloadTitleAssets(void);
void unloadGameAssets(void);
void unloadNameEntryAssets(void);

void switchCoreAssets(void);

#ifdef __cplusplus
}
#endif