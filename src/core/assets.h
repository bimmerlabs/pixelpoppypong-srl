#pragma once

#include <srl.hpp>
#include <ponesound.hpp>
#include "../main.h"
#include "sprites.h"
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
using namespace SRL::Ponesound;

// tmsf format loads in alphabetical order
typedef enum
{
    CORE_SPRITE_CURSOR = 0,
    CORE_SPRITE_MENUBG,
    CORE_SPRITE_POPPY,
    CORE_SPRITE_PUMPKIN,
    CORE_SPRITE_SANTA,
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
    TEAM_SPRITE_LOCK = 0,
    TEAM_SPRITE_METER,
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
    GAME_SPRITE_TREES,
    GAME_SPRITE_X,
    GAME_SPRITE_MAX,
} GAME_SPRITES;

typedef enum _CORE_SND
{
    BackSnd = 0,
    CancelSnd,
    CursorSnd,
    NextSnd,
    StartSnd,
    TickSnd,
    CORE_SND_MAX
} CORE_SND;

typedef enum _GAME_SND
{
    BloopSnd = 0,
    BounceSnd,
    BumpSnd,
    CntDownSnd,
    Chain0Snd,
    Chain1Snd,
    Chain2Snd,
    Chain3Snd,
    Chain5Snd,
    DropSnd,
    ExplodeSnd,
    Explode2Snd,
    LaunchSnd,
    BangSnd,
    GrowSnd,
    ShrinkSnd,
    ScoreAddSnd,
    ScoreTotalSnd,
    ShieldSnd,
    StadlerSnd,
    WinSnd,
    GmOverSnd,
    GAME_SND_MAX
} GAME_SND;

typedef enum _CAT_SND
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
    MEOW_MAX
} CAT_SND;

typedef enum _NAME_SND
{
    LoadOkSnd = 0,
    NameBrkSnd,
    NameCanSnd,
    NameCurSnd,
    NameKetSnd,
    NAME_SND_MAX
} NAME_SND;

// PCM samples / Sound Test
#define FIRST_SAMPLE 0
#define LAST_SAMPLE 41

// holds sprite and audio assets
typedef struct _assets
{
    
    bool coreAssetsLoaded;
    bool titleAssetsLoaded;
    bool characterAssetsLoaded;    
    bool NameEntryAssetsLoaded;
    bool GameplayAssetsLoaded;
    uint16_t startofTitleAssets;
    uint16_t startofCharAssets;
    uint16_t startofGameAssets;
    uint16_t startofNameAssets;
} ASSETS, *PASSETS;

extern ASSETS g_Assets;

typedef struct _SoundAssets
{    
    // CORE / MENU SOUNDS
    short Core[CORE_SND_MAX];

    // GAMEPLAY SOUNDS
    short Game[GAME_SND_MAX];    
    // CAT SOUNDS
    short Meow[MEOW_MAX];
    short MeowId;
    bool GameplayFxLoaded;
    
    // NAME ENTRY SOUNDS
    short Name[NAME_SND_MAX];
    bool NameEntryFxLoaded;

} SoundAssets;

extern SoundAssets Sounds;

extern TilemapObject* coreTiles;
extern TilemapObject* particleTiles;
extern TilemapObject* titleTiles;
extern TilemapObject* characterTiles;
extern TilemapObject* gameplayTiles;
extern TilemapObject* fontTiles;
extern TilemapObject* nameTiles;

extern uint8_t explosionSpr;

#ifdef __cplusplus
extern "C" {
#endif

void loadCoreAssets(void);
void loadCoreSoundAssets(void);

void loadTitleScreenAssets(void);

void loadCharacterAssets(void);
void loadGameAssets(void);
bool loadGameplaySoundAssets(void);

void loadNameEntryAssets(void);
bool loadNameEntrySoundAssets(void);

// void unloadTitleAssets(void);
void unloadGameAssets(void);
void unloadNameEntryAssets(void);

void switchCoreAssets(void);

static inline void playCatSound(void)
{
    Pcm::Play(Sounds.Meow[Sounds.MeowId]);
    Sounds.MeowId++;
    if (Sounds.MeowId > MEOW9)
        Sounds.MeowId = MEOW1;
}

#ifdef __cplusplus
}
#endif