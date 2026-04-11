#include "assets.h"
#include "sprites.h"
#include "util.h"

ASSETS g_Assets = {};

TilemapObject* coreTiles = nullptr;
TilemapObject* titleTiles = nullptr;
TilemapObject* characterTiles = nullptr;
TilemapObject* gameplayTiles = nullptr;
TilemapObject* fontTiles = nullptr;

void loadCoreSoundAssets(void)
{
    // load_8bit_pcm returns the ID of the sound loaded
    // use pcm_reset, giving the id of the last sound you want to keep, to unload extra sounds
    // CORE / MENU SOUNDS
    g_Assets.cancelPcm8 = load_8bit_pcm((int8_t *)"CANCEL.PCM", 15360);
    g_Assets.cursorPcm8 = load_8bit_pcm((int8_t *)"CURSOR.PCM", 15360);
    g_Assets.nextPcm8 = load_8bit_pcm((int8_t *)"NEXT.PCM", 15360);
    g_Assets.startPcm8 = load_8bit_pcm((int8_t *)"START.PCM", 15360);
    g_Assets.tickPcm8 = load_8bit_pcm((int8_t *)"TICK.PCM", 15360);
}

bool loadGameplaySoundAssets(void)
{
    // GAMEPLAY SOUNDS
    g_Assets.scoreTotalPcm8 = load_8bit_pcm((int8_t *)"SCORET.PCM", 15360);
    g_Assets.scoreAddPcm8 = load_8bit_pcm((int8_t *)"SCOREA.PCM", 15360);
    g_Assets.chain0Pcm8 = load_8bit_pcm((int8_t *)"CHAIN0.PCM", 15360);
    g_Assets.chain1Pcm8 = load_8bit_pcm((int8_t *)"CHAIN1.PCM", 15360);
    g_Assets.chain2Pcm8 = load_8bit_pcm((int8_t *)"CHAIN2.PCM", 15360);
    g_Assets.chain3Pcm8 = load_8bit_pcm((int8_t *)"CHAIN3.PCM", 15360);
    g_Assets.chain5Pcm8 = load_8bit_pcm((int8_t *)"CHAIN5.PCM", 15360);
    g_Assets.explod1Pcm8 = load_8bit_pcm((int8_t *)"EXPLOD1.PCM", 15360);
    g_Assets.growPcm8 = load_8bit_pcm((int8_t *)"GROW.PCM", 15360);
    g_Assets.shrinkPcm8 = load_8bit_pcm((int8_t *)"SHRINK.PCM", 15360);
    g_Assets.bloopPcm8 = load_8bit_pcm((int8_t *)"BLOOP.PCM", 15360);
    g_Assets.stadlerPcm8 = load_8bit_pcm((int8_t *)"STADLER.PCM", 15360);
    g_Assets.dropPcm8 = load_8bit_pcm((int8_t *)"DROP.PCM", 15360);
    g_Assets.bouncePcm8 = load_8bit_pcm((int8_t *)"BOUNCE.PCM", 15360);
    g_Assets.shieldPcm8 = load_8bit_pcm((int8_t *)"SHIELD.PCM", 15360);
    // g_Assets.rechargePcm8 = load_8bit_pcm((int8_t *)"RECHARGE.PCM", 15360);
    g_Assets.countdownPcm8 = load_8bit_pcm((int8_t *)"C_DOWN.PCM", 15360);
    g_Assets.bumpPcm16 = load_16bit_pcm((int8_t *)"BUMP.PCM", 15360);
    g_Assets.gameOverPcm8 = load_8bit_pcm((int8_t *)"GMOVR8.PCM", 15360);
    g_Assets.winPcm8 = load_8bit_pcm((int8_t *)"WIN.PCM", 15360);
    
    // CAT SOUNDS
    g_Assets.meowPcm8[0] = load_8bit_pcm((int8_t *)"MEOW1.PCM", 15360);
    g_Assets.meowPcm8[1] = load_8bit_pcm((int8_t *)"MEOW5.PCM", 15360);
    g_Assets.meowPcm8[2] = load_8bit_pcm((int8_t *)"MEOW2.PCM", 15360);
    g_Assets.meowPcm8[3] = load_8bit_pcm((int8_t *)"MEOW6.PCM", 15360);
    g_Assets.meowPcm8[4] = load_8bit_pcm((int8_t *)"MEOW3.PCM", 15360);
    g_Assets.meowPcm8[5] = load_8bit_pcm((int8_t *)"MEOW7.PCM", 15360);
    g_Assets.meowPcm8[6] = load_8bit_pcm((int8_t *)"MEOW4.PCM", 15360);
    g_Assets.meowPcm8[7] = load_8bit_pcm((int8_t *)"MEOW8.PCM", 15360);
    g_Assets.meowPcm8[8] = load_8bit_pcm((int8_t *)"MEOW9.PCM", 15360);
    g_Assets.meowID = MEOW1;
    return true;
}

bool loadNameEntrySoundAssets(void)
{   
    // NAME ENTRY SOUNDS
    g_Assets.name_ketPcm8 = load_8bit_pcm((int8_t *)"NAME_KET.PCM", 15360);
    g_Assets.name_curPcm8 = load_8bit_pcm((int8_t *)"NAME_CUR.PCM", 15360);
    g_Assets.name_canPcm8 = load_8bit_pcm((int8_t *)"NAME_CAN.PCM", 15360);
    g_Assets.name_brkPcm8 = load_8bit_pcm((int8_t *)"NAME_BRK.PCM", 15360);
    g_Assets.load_okPcm8 = load_8bit_pcm((int8_t *)"LOAD_OK.PCM", 15360);
    return true;
}

void loadCoreAssets(void)
{
    SRL::VDP1::ResetTextureHeap();
    SRL::Bitmap::TGA::LoaderSettings settings;
    settings.TransparentColorIndex = 0; // needs to always be index 0 for VDP1/VDP2 (maybe can be configured for VDP1 internally?)
    
    coreTiles = new TilemapObject("CORE.TM", PaletteID, false);    

    pixel_poppy.id = coreTiles->sprite[CORE_SPRITE_POPPY].SpriteIndex;
    pixel_poppy.anim[0].asset = pixel_poppy.id;
    pixel_poppy.anim[0].max = coreTiles->sprite[CORE_SPRITE_POPPY].MaxFrames;
    pixel_poppy.anim[0].frame = 0;

    cursor.id = coreTiles->sprite[CORE_SPRITE_CURSOR].SpriteIndex;
    cursor.anim[0].asset = cursor.id;

    menu_bg1.id = coreTiles->sprite[CORE_SPRITE_MENUBG].SpriteIndex + 4;
    menu_bg1.anim[0].asset = coreTiles->sprite[CORE_SPRITE_MENUBG].SpriteIndex;
    menu_bg2.id = coreTiles->sprite[CORE_SPRITE_MENUBG].SpriteIndex + 5;
    menu_bg2.anim[0].asset = coreTiles->sprite[CORE_SPRITE_MENUBG].SpriteIndex;

    player_bg.id = coreTiles->sprite[CORE_SPRITE_MENUBG].SpriteIndex;
    player_bg.anim[0].asset = player_bg.id;

    
    // HALLOWEEN
    if (g_Game.timeSeason == S_HALLOWEEN && g_GameOptions.use_rtc)
    {
        pixel_poppy.id = coreTiles->sprite[CORE_SPRITE_PUMPKIN].SpriteIndex;
        pixel_poppy.anim[0].asset = pixel_poppy.id;
        pixel_poppy.anim[0].max = coreTiles->sprite[CORE_SPRITE_PUMPKIN].MaxFrames;
        pixel_poppy.anim[0].frame = 0;
        
        cursor.id = cursor.anim[0].asset + 1;
    }

    g_Game.isLoading = false;
    SRL::Debug::PrintClearScreen();
}

void loadTitleScreenAssets(void)
{ 
    titleTiles = new TilemapObject("TITLESCR.TM", PaletteID, false);
    
    menu_arrow.id = titleTiles->sprite[TITLE_SPRITE_ARROWS].SpriteIndex;
    menu_arrow.anim[0].asset = menu_arrow.id;
    menu_arrow.anim[0].max = titleTiles->sprite[TITLE_SPRITE_ARROWS].MaxFrames;
    menu_arrow.anim[0].frame = 0;
    
    logo1.id = titleTiles->sprite[TITLE_SPRITE_LOGO].SpriteIndex;
    logo1.anim[0].asset = logo1.id;
    logo1.anim[0].max = titleTiles->sprite[TITLE_SPRITE_LOGO].MaxFrames;
    logo1.anim[0].frame = 0;    
    // logo2.id = titleTiles->sprite[TITLE_SPRITE_LOGO2].SpriteIndex;
    
    ppplogo.id = titleTiles->sprite[TITLE_SPRITE_PPPLOGO].SpriteIndex;
    pppshadow.id = titleTiles->sprite[TITLE_SPRITE_PPPLOGO].SpriteIndex + 1;
    
    menu_text.id = titleTiles->sprite[TITLE_SPRITE_TMENU].SpriteIndex;
    menu_text.anim[0].asset = menu_text.id;
    menu_text.anim[0].max = titleTiles->sprite[TITLE_SPRITE_TMENU].MaxFrames;
    menu_text.anim[0].frame = 0;
    
    g_Assets.titleAssetsLoaded = true;
    g_Game.isLoading = false;
    SRL::Debug::PrintClearScreen();
}

// missing the meter

void loadCharacterAssets(void)
{
    g_Game.isLoading = true;
        
    characterTiles = new TilemapObject("TEAMSELE.TM", PaletteID, false);
    
    uint8_t characterOffset = 0;
    uint8_t maxFrames = characterTiles->sprite[TEAM_SPRITE_PAWS].MaxFrames;
    uint16_t baseSpriteIndex = characterTiles->sprite[TEAM_SPRITE_PAWS].SpriteIndex;

    for (uint8_t character = CHARACTER_MACCHI; character <= CHARACTER_NONE; ++character)
    {
        paw[character].id = baseSpriteIndex + characterOffset;
        paw[character].anim[0].asset = paw[character].id;
        paw[character].anim[0].max = maxFrames;
        paw[character].anim[0].frame = 0;

        characterOffset += maxFrames;
    }
    
    character_portrait.id = characterTiles->sprite[TEAM_SPRITE_PORTRAIT].SpriteIndex;
    character_portrait.anim[0].asset = character_portrait.id;
    character_portrait.anim[0].max = CHARACTER_NONE;
    character_portrait.anim[0].frame = 0;
    shadow.id = character_portrait.anim[0].asset + CHARACTER_MAX;
    
    player_cursor1.id = characterTiles->sprite[TEAM_SPRITE_SELECT1].SpriteIndex;
    player_cursor1.anim[0].asset = player_cursor1.id;
    player_cursor1.anim[0].max = 3;
    player_cursor1.anim[0].frame = 0;
    player_cursor2.id = characterTiles->sprite[TEAM_SPRITE_SELECT2].SpriteIndex;
    player_cursor2.anim[0].asset = player_cursor2.id;
    player_cursor2.anim[0].max = 3;
    player_cursor2.anim[0].frame = 0;
    
    meter.id = characterTiles->sprite[TEAM_SPRITE_METER].SpriteIndex;
    meter.anim[0].asset = meter.id;
    meter.anim[0].max = characterTiles->sprite[TEAM_SPRITE_METER].MaxFrames;
    meter.anim[0].frame = 0;
    
    g_Game.isLoading = false;
    g_Assets.characterAssetsLoaded = true;
    SRL::Debug::PrintClearScreen();
}

void loadGameAssets(void)
{
    g_Game.isLoading = true;
        
    gameplayTiles = new TilemapObject("GAMEPLAY.TM", PaletteID, false);
    
    // GAME_SPRITE_EXPLOD
    // used as 2nd asset in other sprites
    uint8_t explosionSpr = gameplayTiles->sprite[GAME_SPRITE_EXPLOD].SpriteIndex;
    uint8_t explosionMax = gameplayTiles->sprite[GAME_SPRITE_EXPLOD].MaxFrames; 
    
    // poppy explosion
    pixel_poppy.anim[1].asset = explosionSpr;
    pixel_poppy.anim[1].max = explosionMax;
    pixel_poppy.anim[1].frame = 0;
    
    // GAME_SPRITE_BOMB
    bomb_item.id = gameplayTiles->sprite[GAME_SPRITE_BOMB].SpriteIndex;
    bomb_item.anim[0].asset = bomb_item.id;
    bomb_item.anim[0].max = gameplayTiles->sprite[GAME_SPRITE_BOMB].MaxFrames;
    bomb_item.anim[0].frame = 0;
    bomb_item.anim[1].asset = explosionSpr;
    bomb_item.anim[1].max = explosionMax;
    bomb_item.anim[1].frame = 0;

    // GAME_SPRITE_CRAIG
    craig_item.id = gameplayTiles->sprite[GAME_SPRITE_CRAIG].SpriteIndex;
    craig_item.anim[0].asset = craig_item.id;

    // GAME_SPRITE_FISH
    fishtank_item.id = gameplayTiles->sprite[GAME_SPRITE_FISH].SpriteIndex;
    fishtank_item.anim[0].asset = fishtank_item.id;
    fishtank_item.anim[0].max = gameplayTiles->sprite[GAME_SPRITE_FISH].MaxFrames;
    fishtank_item.anim[0].frame = 0;

    // GAME_SPRITE_GARF
    garfield_item.id = gameplayTiles->sprite[GAME_SPRITE_GARF].SpriteIndex;
    garfield_item.anim[0].asset = garfield_item.id;

    // GAME_SPRITE_GOAL
    goals[0].id = gameplayTiles->sprite[GAME_SPRITE_GOAL].SpriteIndex;
    goals[0].anim[0].asset = goals[0].id;
    goals[0].anim[1].asset = explosionSpr;
    goals[0].anim[1].max = explosionMax; 
    
    goals[1].id = goals[0].id;
    goals[1].anim[0].asset = goals[1].id;
    goals[1].anim[1].asset = explosionSpr;
    goals[1].anim[1].max = explosionMax; 
    
    goals[2].id = goals[0].id;
    goals[2].anim[0].asset = goals[2].id;
    goals[2].anim[1].asset = explosionSpr;
    goals[2].anim[1].max = explosionMax; 
    
    goals[3].id = goals[0].id;
    goals[3].anim[0].asset = goals[0].id;
    goals[3].anim[1].asset = explosionSpr;
    goals[3].anim[1].max = explosionMax; 
    
    // GAME_SPRITE_HEARTS
    heart.id = gameplayTiles->sprite[GAME_SPRITE_HEARTS].SpriteIndex;
    heart.anim[0].asset = heart.id;
    star.id = heart.id + 3;
    star.anim[0].asset = star.id;
    
    // GAME_SPRITE_TIMER
    timer.id = gameplayTiles->sprite[GAME_SPRITE_TIMER].SpriteIndex;
    timer.anim[0].asset = timer.id;

    // GAME_SPRITE_SHIELD
    shield[0].id = gameplayTiles->sprite[GAME_SPRITE_SHIELD].SpriteIndex;
    shield[0].anim[0].asset = shield[0].id;
    shield[0].anim[0].max = gameplayTiles->sprite[GAME_SPRITE_SHIELD].MaxFrames;
    shield[0].anim[0].frame = 0;           
     
    shield[1].id = shield[0].id;
    shield[1].anim[0].asset = shield[1].id;
    shield[1].anim[0].max = gameplayTiles->sprite[GAME_SPRITE_SHIELD].MaxFrames;
    shield[1].anim[0].frame = 0;
     
    shield[2].id = shield[0].id;
    shield[2].anim[0].asset = shield[2].id;
    shield[2].anim[0].max = gameplayTiles->sprite[GAME_SPRITE_SHIELD].MaxFrames;
    shield[2].anim[0].frame = 0;
     
    shield[3].id = shield[0].id;
    shield[3].anim[0].asset = shield[3].id;
    shield[3].anim[0].max = gameplayTiles->sprite[GAME_SPRITE_SHIELD].MaxFrames;
    shield[3].anim[0].frame = 0;
    
    // GAME_SPRITE_SHROOM
    shroom_item.id = gameplayTiles->sprite[GAME_SPRITE_SHROOM].SpriteIndex;
    shroom_item.anim[0].asset = shroom_item.id;
    shroom_item.anim[0].max = gameplayTiles->sprite[GAME_SPRITE_SHROOM].MaxFrames;
    shroom_item.anim[0].frame = 0;
    
    // GAME_SPRITE_X
    dead.id = gameplayTiles->sprite[GAME_SPRITE_X].SpriteIndex;
    dead.anim[0].asset = dead.id;
    
    // HALLOWEEN
    if (g_Game.timeSeason == S_HALLOWEEN && g_GameOptions.use_rtc)
    {
        craig_item.id = craig_item.anim[0].asset + 1; // VAMPIRE CRAIG
        garfield_item.id = garfield_item.anim[0].asset + 1; // VAMPIRE GARF
        heart.id = gameplayTiles->sprite[GAME_SPRITE_CORN].SpriteIndex; // CANDY CORN
        heart.anim[0].asset = heart.id;
    }        
    
    g_Assets.GameplayAssetsLoaded = true;
    
    if (!g_Assets.GameplaySoundsLoaded) {
            g_Game.isSoundLoading = true;
            SRL::Debug::PrintClearLine(15);
            g_Assets.GameplaySoundsLoaded = loadGameplaySoundAssets();
            g_Game.isSoundLoading = false;            
    }
    
    g_Game.isLoading = false;
    SRL::Debug::PrintClearScreen();
}

void loadNameEntryAssets(void)
{
    g_Game.isLoading = true;
    
    fontTiles = new TilemapObject("NAMEENTR.TM", PaletteID, false);
    
    font.id = fontTiles->sprite[0].SpriteIndex;
    font.anim[0].asset = font.id;
    
    if (!g_Assets.NameEntrySoundsLoaded) {
        g_Game.isSoundLoading = true;
        SRL::Debug::PrintClearLine(15);
        g_Assets.NameEntrySoundsLoaded = loadNameEntrySoundAssets();
        g_Game.isSoundLoading = false;            
    }
    
    g_Assets.NameEntryAssetsLoaded = true;
    g_Game.isLoading = false;
    SRL::Debug::PrintClearScreen();
}

void unloadTitleAssets(void)
{
    // titleTiles->~TilemapObject(); 
    SRL::VDP1::ResetTextureHeap(menu_arrow.id);
    g_Assets.titleAssetsLoaded = false;
}

void unloadGameAssets(void)
{
    // characterTiles->~TilemapObject();
    SRL::VDP1::ResetTextureHeap(meter.id);
    g_Assets.characterAssetsLoaded = false;
    g_Assets.GameplayAssetsLoaded = false;
}

void unloadNameEntryAssets(void)
{
    SRL::VDP1::ResetTextureHeap(font.id);
    g_Assets.NameEntryAssetsLoaded = false;
}

void switchCoreAssets(void)
{
    // HALLOWEEN
    if (g_Game.timeSeason == S_HALLOWEEN && g_GameOptions.use_rtc)
    {
        pixel_poppy.id = coreTiles->sprite[CORE_SPRITE_PUMPKIN].SpriteIndex;
        pixel_poppy.anim[0].asset = pixel_poppy.id;
        pixel_poppy.anim[0].max = coreTiles->sprite[CORE_SPRITE_PUMPKIN].MaxFrames;
        pixel_poppy.anim[0].frame = 0;
        
        cursor.id = cursor.anim[0].asset + 1;
    }
    else {
        pixel_poppy.id = coreTiles->sprite[CORE_SPRITE_POPPY].SpriteIndex;
        pixel_poppy.anim[0].asset = pixel_poppy.id;
        pixel_poppy.anim[0].max = coreTiles->sprite[CORE_SPRITE_POPPY].MaxFrames;
        pixel_poppy.anim[0].frame = 0;
        
        cursor.id = cursor.anim[0].asset;
    }
}