#include <jo/jo.h>
#include "assets.h"
#include "sprites.h"
#include "util.h"

// NOTE: Palette is loaded with the font and shared with all other sprites.

Uint8 palette_transparent_index = 2;

ASSETS g_Assets = {
    .GameplaySoundsLoaded = false,
    .NameEntrySoundsLoaded = false,
};

static void initTileset(jo_tile* tileset, unsigned int numSprites, unsigned int spritesPerRow, int width, int height)
{
    unsigned int col = 0;
    unsigned int row = 0;

    for(unsigned int i = 0; i < numSprites; i++)
    {
        col = i % spritesPerRow; // modulus
        row = i / spritesPerRow;

        tileset[i].x = col * width;
        tileset[i].y = row * height;
        tileset[i].height = height;
        tileset[i].width = width;
    }
}

void loadSprite(Sprite *sprite, int *asset, const char *file, unsigned int cols, unsigned int rows, int w, int h, unsigned char anim_id) {
    jo_tile tileset[cols*rows];
    initTileset(tileset, (cols*rows), rows, w, h);
    asset[0] = jo_sprite_add_tga_tileset(NULL, file, palette_transparent_index, tileset, cols*rows);
        for(unsigned int i = 0; i < (cols*rows); i++)
        {
            asset[i] = asset[0] + i;
        }
        sprite->anim[anim_id].asset = asset;
        sprite->anim[anim_id].max = (cols*rows)-1;
        sprite->spr_id = sprite->anim[anim_id].asset[sprite->anim[anim_id].frame];
        sprite->pos.r = w; // is this needed?
}

void loadCoreSoundAssets(void)
{
    // load_8bit_pcm returns the ID of the sound loaded
    // use pcm_reset, giving the id of the last sound you want to keep, to unload extra sounds
    
    // CORE / MENU SOUNDS
    g_Assets.cancelPcm8 = load_8bit_pcm((Sint8 *)"CANCEL.PCM", 15360);
    g_Assets.cursorPcm8 = load_8bit_pcm((Sint8 *)"CURSOR.PCM", 15360);
    g_Assets.nextPcm8 = load_8bit_pcm((Sint8 *)"NEXT.PCM", 15360);
    g_Assets.startPcm8 = load_8bit_pcm((Sint8 *)"START.PCM", 15360);
    g_Assets.tickPcm8 = load_8bit_pcm((Sint8 *)"TICK.PCM", 15360);
}

bool loadGameplaySoundAssets(void)
{
    // GAMEPLAY SOUNDS
    g_Assets.scoreTotalPcm8 = load_8bit_pcm((Sint8 *)"SCORET.PCM", 15360);
    g_Assets.scoreAddPcm8 = load_8bit_pcm((Sint8 *)"SCOREA.PCM", 15360);
    g_Assets.chain0Pcm8 = load_8bit_pcm((Sint8 *)"CHAIN0.PCM", 15360);
    g_Assets.chain1Pcm8 = load_8bit_pcm((Sint8 *)"CHAIN1.PCM", 15360);
    g_Assets.chain2Pcm8 = load_8bit_pcm((Sint8 *)"CHAIN2.PCM", 15360);
    g_Assets.chain3Pcm8 = load_8bit_pcm((Sint8 *)"CHAIN3.PCM", 15360);
    g_Assets.chain5Pcm8 = load_8bit_pcm((Sint8 *)"CHAIN5.PCM", 15360);
    g_Assets.explod1Pcm8 = load_8bit_pcm((Sint8 *)"EXPLOD1.PCM", 15360);
    g_Assets.growPcm8 = load_8bit_pcm((Sint8 *)"GROW.PCM", 15360);
    g_Assets.shrinkPcm8 = load_8bit_pcm((Sint8 *)"SHRINK.PCM", 15360);
    g_Assets.bloopPcm8 = load_8bit_pcm((Sint8 *)"BLOOP.PCM", 15360);
    g_Assets.stadlerPcm8 = load_8bit_pcm((Sint8 *)"STADLER.PCM", 15360);
    g_Assets.dropPcm8 = load_8bit_pcm((Sint8 *)"DROP.PCM", 15360);
    g_Assets.bouncePcm8 = load_8bit_pcm((Sint8 *)"BOUNCE.PCM", 15360);
    g_Assets.shieldPcm8 = load_8bit_pcm((Sint8 *)"SHIELD.PCM", 15360);
    // g_Assets.rechargePcm8 = load_8bit_pcm((Sint8 *)"RECHARGE.PCM", 15360);
    g_Assets.countdownPcm8 = load_8bit_pcm((Sint8 *)"C_DOWN.PCM", 15360);
    g_Assets.bumpPcm16 = load_16bit_pcm((Sint8 *)"BUMP.PCM", 15360);
    g_Assets.gameOverPcm8 = load_8bit_pcm((Sint8 *)"GMOVR8.PCM", 15360);
    g_Assets.winPcm8 = load_8bit_pcm((Sint8 *)"WIN.PCM", 15360);
    
    // CAT SOUNDS
    g_Assets.meowPcm8[0] = load_8bit_pcm((Sint8 *)"MEOW1.PCM", 15360);
    g_Assets.meowPcm8[1] = load_8bit_pcm((Sint8 *)"MEOW5.PCM", 15360);
    g_Assets.meowPcm8[2] = load_8bit_pcm((Sint8 *)"MEOW2.PCM", 15360);
    g_Assets.meowPcm8[3] = load_8bit_pcm((Sint8 *)"MEOW6.PCM", 15360);
    g_Assets.meowPcm8[4] = load_8bit_pcm((Sint8 *)"MEOW3.PCM", 15360);
    g_Assets.meowPcm8[5] = load_8bit_pcm((Sint8 *)"MEOW7.PCM", 15360);
    g_Assets.meowPcm8[6] = load_8bit_pcm((Sint8 *)"MEOW4.PCM", 15360);
    g_Assets.meowPcm8[7] = load_8bit_pcm((Sint8 *)"MEOW8.PCM", 15360);
    g_Assets.meowPcm8[8] = load_8bit_pcm((Sint8 *)"MEOW9.PCM", 15360);
    g_Assets.meowID = MEOW1;
    return true;
}

bool loadNameEntrySoundAssets(void)
{   
    // NAME ENTRY SOUNDS
    g_Assets.name_ketPcm8 = load_8bit_pcm((Sint8 *)"NAME_KET.PCM", 15360);
    g_Assets.name_curPcm8 = load_8bit_pcm((Sint8 *)"NAME_CUR.PCM", 15360);
    g_Assets.name_canPcm8 = load_8bit_pcm((Sint8 *)"NAME_CAN.PCM", 15360);
    g_Assets.name_brkPcm8 = load_8bit_pcm((Sint8 *)"NAME_BRK.PCM", 15360);
    return true;
}

void loadCommonAssets(void)
{
    jo_sprite_free_all();
    // pixel poppy
    loadSprite(&pixel_poppy, g_Assets.pixel_poppy, "POPPY.TGA", NUM_POPPY_SPRITES, 1, 64, 50, 0);
    // menu cursor
    cursor.spr_id = jo_sprite_add_tga(NULL, "CURSOR.TGA", palette_transparent_index);
    
    // background / UI layers
    loadSprite(&menu_bg1, g_Assets.menubg, "MENUBG.TGA", NUM_MENUBG_SPRITES, 1, 2, 2, 0);
    menu_bg1.spr_id = menu_bg1.anim[0].asset[6];
    menu_bg2.anim[0].asset = g_Assets.menubg;
    menu_bg2.spr_id = menu_bg2.anim[0].asset[5];
    player_bg.anim[0].asset = g_Assets.menubg;
    meter.anim[0].asset = g_Assets.menubg;
    meter.spr_id = meter.anim[0].asset[7];
    
    ppplogo.spr_id = jo_sprite_add_tga(NULL, "PPPLOGO.TGA", palette_transparent_index);
    pppshadow.spr_id = jo_sprite_add_tga(NULL, "PPPSHDW.TGA", palette_transparent_index); 
}

void loadPPPLogoAssets(void)
{        
    ppplogo.spr_id = jo_sprite_add_tga(NULL, "PPPLOGO.TGA", palette_transparent_index);
    pppshadow.spr_id = jo_sprite_add_tga(NULL, "PPPSHDW.TGA", palette_transparent_index);  
    
    g_Game.isLoading = false;
}

void unloadPPPLogoAssets(void)
{
    g_Game.isLoading = true;
    // unloads everything after this point
    jo_sprite_free_from(ppplogo.spr_id);
    
}

void loadNameEntryAssets(void)
{
    loadSprite(&font, g_Assets.font, "FONT2.TGA", NUM_FONT_CHARS, 1, 24, 24, 0);
    if (!g_Assets.NameEntrySoundsLoaded) {
            g_Game.isSoundLoading = true;
            g_Assets.NameEntrySoundsLoaded = loadNameEntrySoundAssets();
            g_Game.isSoundLoading = false;            
    }
    g_Game.isLoading = false;
}

void unloadNameEntryAssets(void)
{
    // unloads everything after this point
    jo_sprite_free_from(font.spr_id);
    
}

void loadTitleScreenAssets(void)
{        
    logo1.spr_id = jo_sprite_add_tga(NULL, "LOGO1.TGA", palette_transparent_index);
    logo2.spr_id = jo_sprite_add_tga(NULL, "LOGO2.TGA", palette_transparent_index);
    loadSprite(&menu_text, g_Assets.menu, "TMENU.TGA", NUM_TITLE_MENU_TEXT, 1, 216, 22, 0);    
    loadSprite(&menu_arrow, g_Assets.arrow, "ARROWS.TGA", NUM_TITLE_MENU_ARROWS, 1, 8, 10, 0);    
    
    g_Game.isLoading = false;
}

void unloadTitleScreenAssets(void)
{
    g_Game.isLoading = true;    
    // unloads everything after this point
    jo_sprite_free_from(logo1.spr_id);
}

void loadCharacterAssets(void)
{
    loadSprite(&character_portrait, g_Assets.characters, "PORTRAIT.TGA", NUM_CHARACTER_SPRITES, 1, 48, 48, 0);
    
    loadSprite(&player_cursor1, g_Assets.pcursor[0], "SELECT.TGA", NUM_PCURSOR_SPRITES, 1, 32, 32, 0);
    // loadSprite(&player_cursor1, g_Assets.pcursor[0], "SELECT_R.TGA", NUM_PCURSOR_SPRITES, 1, 8, 32, 0);
    loadSprite(&player_cursor2, g_Assets.pcursor[1], "SELECT_R.TGA", NUM_PCURSOR_SPRITES, 1, 8, 32, 0);
    // loadSprite(&player_cursor2, g_Assets.pcursor[1], "SELECT.TGA", NUM_PCURSOR_SPRITES, 1, 32, 32, 0);

    loadSprite(&paw[CHARACTER_MACCHI], g_Assets.paw[CHARACTER_MACCHI], "PAW0.TGA",  1, NUM_PAW_SPRITES, 32, 24, 0);
    loadSprite(&paw[CHARACTER_JELLY],  g_Assets.paw[CHARACTER_JELLY],  "PAW1.TGA",  1, NUM_PAW_SPRITES, 32, 24, 0);
    loadSprite(&paw[CHARACTER_PENNY],  g_Assets.paw[CHARACTER_PENNY],  "PAW2.TGA",  1, NUM_PAW_SPRITES, 32, 24, 0);
    loadSprite(&paw[CHARACTER_POTTER], g_Assets.paw[CHARACTER_POTTER], "PAW3.TGA",  1, NUM_PAW_SPRITES, 32, 24, 0);
    loadSprite(&paw[CHARACTER_SPARTA], g_Assets.paw[CHARACTER_SPARTA], "PAW4.TGA",  1, NUM_PAW_SPRITES, 32, 24, 0);
    loadSprite(&paw[CHARACTER_POPPY],  g_Assets.paw[CHARACTER_POPPY],  "PAW5.TGA",  1, NUM_PAW_SPRITES, 32, 24, 0);
    loadSprite(&paw[CHARACTER_TJ],     g_Assets.paw[CHARACTER_TJ],     "PAW6.TGA",  1, NUM_PAW_SPRITES, 32, 24, 0);
    loadSprite(&paw[CHARACTER_GEORGE], g_Assets.paw[CHARACTER_GEORGE], "PAW7.TGA",  1, NUM_PAW_SPRITES, 32, 24, 0);
    loadSprite(&paw[CHARACTER_WUPPY],  g_Assets.paw[CHARACTER_WUPPY],  "PAW8.TGA",  1, NUM_PAW_SPRITES, 32, 24, 0);
    loadSprite(&paw[CHARACTER_WALRUS], g_Assets.paw[CHARACTER_WALRUS], "PAW9.TGA",  1, NUM_PAW_SPRITES, 32, 24, 0);
    loadSprite(&paw[CHARACTER_GARF],   g_Assets.paw[CHARACTER_GARF],   "PAW10.TGA", 1, NUM_PAW_SPRITES, 32, 24, 0);
    loadSprite(&paw[CHARACTER_NONE],   g_Assets.paw[CHARACTER_NONE],   "PAW11.TGA", 1, NUM_PAW_SPRITES, 32, 24, 0);
        
    g_Game.isLoading = false;
}


void loadGameAssets(void)
{
    g_Game.isLoading = true;
    
    // Items (load first so the explosion can be re-used for other elements)
    loadSprite(&bomb_item, g_Assets.bomb, "BOMB.TGA", NUM_BOMB_SPRITES, 1, 24, 24, 0);
    loadSprite(&bomb_item, g_Assets.explosion, "EXPLOD.TGA", NUM_EXPLOD_SPRITES, 1, 72, 72, 1);
    loadSprite(&fishtank_item, g_Assets.fishtank, "FISH.TGA", NUM_FISH_SPRITES, 1, 24, 24, 0);
    loadSprite(&shroom_item, g_Assets.shroom, "SHROOM.TGA", NUM_SHROOM_SPRITES, 1, 24, 24, 0);
    
    // UI elements
    loadSprite(&timer, g_Assets.timer, "NUM1X1.TGA", NUM_TIMER_SPRITES, 1, 16, 16, 0);

    loadSprite(&goal[0], g_Assets.goal[0], "GOAL1.TGA", NUM_GOAL_SPRITES, 1, 32, 12, 0);
    loadSprite(&goal[1], g_Assets.goal[1], "GOAL2.TGA", NUM_GOAL_SPRITES, 1, 32, 12, 0);
    loadSprite(&goal[2], g_Assets.goal[2], "GOAL3.TGA", NUM_GOAL_SPRITES, 1, 32, 12, 0);
    loadSprite(&goal[3], g_Assets.goal[3], "GOAL4.TGA", NUM_GOAL_SPRITES, 1, 32, 12, 0);
    
    goal[0].anim[1].asset = g_Assets.explosion;
    goal[0].anim[1].max = bomb_item.anim[1].max;   
    goal[1].anim[1].asset = g_Assets.explosion;
    goal[1].anim[1].max = bomb_item.anim[1].max;   
    goal[2].anim[1].asset = g_Assets.explosion;
    goal[2].anim[1].max = bomb_item.anim[1].max;   
    goal[3].anim[1].asset = g_Assets.explosion;
    goal[3].anim[1].max = bomb_item.anim[1].max;
    
    loadSprite(&heart, g_Assets.heart, "HEARTS.TGA", NUM_HEART_SPRITES, 1, 8, 8, 0);
    star.anim[0].asset = g_Assets.heart;
    star.spr_id = star.anim[0].asset[3];
    
    loadSprite(&shield[0], g_Assets.shield, "SHIELD.TGA", NUM_SHIELD_SPRITES, 1, 32, 64, 0);
    shield[1].anim[0].asset = g_Assets.shield,
    shield[1].anim[0].max = 6,
    shield[1].spr_id = shield[1].anim[0].asset[6];
    shield[2].anim[0].asset = g_Assets.shield,
    shield[2].anim[0].max = 6,
    shield[2].spr_id = shield[2].anim[0].asset[6];
    shield[3].anim[0].asset = g_Assets.shield,
    shield[3].anim[0].max = 6,
    shield[3].spr_id = shield[3].anim[0].asset[6];
    
    loadSprite(&dead, g_Assets.dead, "X.TGA", NUM_X_SPRITES, 1, 24, 24, 0);
        
    pixel_poppy.anim[1].asset = g_Assets.explosion;
    pixel_poppy.anim[1].max = bomb_item.anim[1].max;
    
    craig_item.spr_id = jo_sprite_add_tga(NULL, "CRAIG.TGA", palette_transparent_index);
    garfield_item.spr_id = jo_sprite_add_tga(NULL, "GARFIELD.TGA", palette_transparent_index);
    
    if (!g_Assets.GameplaySoundsLoaded) {
            g_Game.isSoundLoading = true;
            g_Assets.GameplaySoundsLoaded = loadGameplaySoundAssets();
            g_Game.isSoundLoading = false;            
    }
    g_Game.isLoading = false;
}

void unloadGameAssets(void)
{
    g_Game.isLoading = true;
    // unloads everything after this point
    jo_sprite_free_from(character_portrait.anim[0].asset[0]);
    
}
