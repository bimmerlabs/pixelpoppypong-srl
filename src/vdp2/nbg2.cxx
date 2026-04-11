#include "nbg2.h"
#include "../main.h"
// #include "nbg2_3.cel"
// #include "nbg2_3.map"
// #include "nbg2_3.pal"

using namespace SRL::Math::Types;

bool firstNBG2Load = true;
SRL::Tilemap::Interfaces::CubeTile* OptionsTilemap;
SRL::Tilemap::Interfaces::CubeTile* PauseTilemap;

void preload_options_bg(void) {
    // keep in hwram so it doesn't stop music playback
    OptionsTilemap = new SRL::Tilemap::Interfaces::CubeTile("NBG2_0.BIN");
    PauseTilemap = new SRL::Tilemap::Interfaces::CubeTile("NBG2_P.BIN");
}

void init_nbg2_img(void) {
    // if (firstNBG2Load)
    // {
        // // // from Bitmap
        // // SRL::Bitmap::TGA* background = new SRL::Bitmap::TGA("NBG2_1.TGA"); // Load Bitmap image to work RAM
        // // SRL::Tilemap::Interfaces::Bmp2Tile* Tilemap = new SRL::Tilemap::Interfaces::Bmp2Tile(*background); // convert bitmap to tilemap
        // // delete background; // free original bitmap from work ram
        
        // // cubetile
        // // SRL::Tilemap::Interfaces::CubeTile* Tilemap = new SRL::Tilemap::Interfaces::CubeTile("NBG2_0.BIN");
        // // OptionsTilemap = new SRL::Tilemap::Interfaces::CubeTile("NBG2_0.BIN");

        // SRL::VDP2::NBG2::LoadTilemap(*OptionsTilemap); // Transfer tilemap from work RAM to VDP2 VRAM and register with NBG2
        // // delete OptionsTilemap; // free tilemap from work ram 
        
        // firstNBG2Load = false;
    // }
    
    // VDP2 Cel/Map/Pal
    // SRL::Tilemap::TilemapInfo* info = 
        // new SRL::Tilemap::TilemapInfo
        // (
            // SRL::CRAM::TextureColorMode::Paletted256, 
            // PNB_1WORD|CN_10BIT, // 1 word (10 or 12 lower bits) or 2 words
            // CHAR_SIZE_2x2, // 1x1 or 2x2 (8x8px or 16x16px)
            // PL_SIZE_2x1,   // plane size - 1x1, 2x2, or 2x2
            // 32,            // cols
            // 64,            // rows 
            // // 0xC300         // size from nbg2_2.cel
            // 0x10200        // size from nbg2_3.cel
        // );
    // SRL::Tilemap::Interfaces::SGLTile* Tilemap = new SRL::Tilemap::Interfaces::SGLTile(cel_nbg2_2, map_nbg2_2, pal_nbg2_2, *info);
    // delete info;
    // SRL::VDP2::NBG2::LoadTilemap(*Tilemap); 
    // delete Tilemap;
    
    // this is only needed if swapping out the layer between screens
    if (firstNBG2Load)
    {
        SRL::VDP2::NBG2::SetCellAddress(SRL::VDP2::VRAM::Allocate(0x2000,32,SRL::VDP2::VramBank::A1,0),0x2000);  // CELL can be anywhere, but in high res it should be in a different bank since ther are limited timings
        SRL::VDP2::NBG2::SetMapAddress(SRL::VDP2::VRAM::Allocate(0x4000,1024,SRL::VDP2::VramBank::B1,1),0x4000); // MAP needs to be in A1 or B1
        
        firstNBG2Load = false;
    }
    else if (SRL::VDP2::NBG2::TilePalette.GetData())
    {
        SRL::CRAM::SetBankUsedState(SRL::VDP2::NBG2::TilePalette.GetId(), SRL::VDP2::NBG2::Info.ColorMode, false);
        SRL::VDP2::NBG2::TilePalette = SRL::CRAM::Palette();
    }
    
    switch(g_Game.nextState)
    {
        case GAME_STATE_TITLE_OPTIONS:
        {
            SRL::VDP2::NBG2::LoadTilemap(*OptionsTilemap);
            SRL::VDP2::NBG2::SetOpacity(Fxp(0.7));
            break;
        }
        case GAME_STATE_GAMEPLAY:
        {
            // if (g_Game.isPaused) // maybe use this for different game modes
            // {
                SRL::VDP2::NBG2::LoadTilemap(*PauseTilemap);
                SRL::VDP2::NBG2::SetOpacity(Fxp(0.7));
            // }
            break;
        }
        case GAME_STATE_TEAM_SELECT:
        {
            // CubeTile
            if (g_Game.numPlayers == TWO_PLAYER) {
                SRL::Tilemap::Interfaces::CubeTile* Tilemap = new SRL::Tilemap::Interfaces::CubeTile("NBG2_2.BIN");
                SRL::VDP2::NBG2::LoadTilemap(*Tilemap);
                delete Tilemap;
            }
            else if (g_Game.numPlayers == THREE_PLAYER) {
                SRL::Tilemap::Interfaces::CubeTile* Tilemap = new SRL::Tilemap::Interfaces::CubeTile("NBG2_3.BIN");
                SRL::VDP2::NBG2::LoadTilemap(*Tilemap);
                delete Tilemap;
            }
            else {
                SRL::Tilemap::Interfaces::CubeTile* Tilemap = new SRL::Tilemap::Interfaces::CubeTile("NBG2_4.BIN");
                SRL::VDP2::NBG2::LoadTilemap(*Tilemap);
                delete Tilemap;
            }
            SRL::VDP2::NBG2::SetOpacity(Fxp(0.5));
            break;
        }
        default:
            break;
    }

    // this is always the same
    SRL::VDP2::NBG2::SetPriority(SRL::VDP2::Priority::Layer3);
    SRL::VDP2::NBG2::ScrollDisable();
    Vector2D pos = (Fxp(0), Fxp(0));
    SRL::VDP2::NBG2::SetPosition(pos);
}
