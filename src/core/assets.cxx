#include "assets.h"
#include "sprites.h"
#include "util.h"

ASSETS g_Assets = {};
SoundAssets Sounds = {};

TilemapObject* coreTiles = nullptr;
TilemapObject* titleTiles = nullptr;
TilemapObject* characterTiles = nullptr;
TilemapObject* gameplayTiles = nullptr;
TilemapObject* fontTiles = nullptr;

void loadCoreSoundAssets(void)
{
    // CORE / MENU SOUNDS
    Pcm::LoadSound("CORE.SND", Sounds.Core, 5);
}

bool loadGameplaySoundAssets(void)
{
    // GAMEPLAY SOUNDS
    Pcm::LoadSound("GAMEPLAY.SND", Sounds.Game, 19);
    
    // CAT SOUNDS
    Pcm::LoadSound("CAT.SND", Sounds.Meow, 9);
    Sounds.MeowId = MEOW1;
    return true;
}

bool loadNameEntrySoundAssets(void)
{   
    // NAME ENTRY SOUNDS
    Pcm::LoadSound("NAME.SND", Sounds.Name, 5);
    return true;
}

void loadCoreAssets(void)
{
    SRL::VDP1::ResetTextureHeap();
    SRL::Bitmap::TGA::LoaderSettings settings;
    settings.TransparentColorIndex = 0; // needs to always be index 0 for VDP1/VDP2 (maybe can be configured for VDP1 internally?)
    
    coreTiles = new TilemapObject("CORE.LZ", PaletteID, false, true);    

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
    titleTiles = new TilemapObject("TITLESCR.LZ", PaletteID, false, true);
    
    menu_arrow.id = titleTiles->sprite[TITLE_SPRITE_ARROWS].SpriteIndex;
    menu_arrow.anim[0].asset = menu_arrow.id;
    menu_arrow.anim[0].max = titleTiles->sprite[TITLE_SPRITE_ARROWS].MaxFrames;
    menu_arrow.anim[0].frame = 0;
    
    logo1.id = titleTiles->sprite[TITLE_SPRITE_LOGO].SpriteIndex;
    logo1.anim[0].asset = logo1.id;
    logo1.anim[0].max = titleTiles->sprite[TITLE_SPRITE_LOGO].MaxFrames;
    logo1.anim[0].frame = 0;
    
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
        
    characterTiles = new TilemapObject("TEAMSELE.LZ", PaletteID, false, true);
    
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
        
    gameplayTiles = new TilemapObject("GAMEPLAY.LZ", PaletteID, false, true);
    
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
    
    if (!Sounds.GameplayFxLoaded) {
            g_Game.isSoundLoading = true;
            SRL::Debug::PrintClearLine(15);
            Sounds.GameplayFxLoaded = loadGameplaySoundAssets();
            g_Game.isSoundLoading = false;            
    }
    
    g_Game.isLoading = false;
    SRL::Debug::PrintClearScreen();
}

void loadNameEntryAssets(void)
{
    g_Game.isLoading = true;
    
    fontTiles = new TilemapObject("NAMEENTR.LZ", PaletteID, false, true);
    
    font.id = fontTiles->sprite[0].SpriteIndex;
    font.anim[0].asset = font.id;
    
    if (!Sounds.NameEntryFxLoaded) {
        g_Game.isSoundLoading = true;
        SRL::Debug::PrintClearLine(15);
        Sounds.NameEntryFxLoaded = loadNameEntrySoundAssets();
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