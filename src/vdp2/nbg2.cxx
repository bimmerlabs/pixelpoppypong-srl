#include "nbg2.h"
#include "../main.h"
// #include "nbg2_3.cel"
// #include "nbg2_3.map"
// #include "nbg2_3.pal"

using namespace SRL::Math::Types;

bool firstNBG2Load = true;
SRL::Tilemap::Interfaces::CubeTile* OptionsTilemap;
SRL::Tilemap::Interfaces::CubeTile* GameTilemap1;
SRL::Tilemap::Interfaces::CubeTile* GameTilemap2;
SRL::Tilemap::Interfaces::CubeTile* PauseTilemap;

void preload_options_bg(void) {
    // keep in hwram so it doesn't stop music playback
    // OptionsTilemap = new SRL::Tilemap::Interfaces::CubeTile("TEST.BIN");
    OptionsTilemap = new SRL::Tilemap::Interfaces::CubeTile("NBG2_0.BIN");
    GameTilemap1   = new SRL::Tilemap::Interfaces::CubeTile("NBG2GP1.BIN");
    GameTilemap2   = new SRL::Tilemap::Interfaces::CubeTile("NBG2GP2.BIN");
    PauseTilemap   = new SRL::Tilemap::Interfaces::CubeTile("NBG2_P.BIN");
}

void init_nbg2_img(void) {
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
        case GAME_STATE_HIGHSCORES:
        {
            SRL::Tilemap::Interfaces::CubeTile* Tilemap = new SRL::Tilemap::Interfaces::CubeTile("NBG2HS.BIN");
            SRL::VDP2::NBG2::LoadTilemap(*Tilemap);
            delete Tilemap;
            SRL::VDP2::NBG2::SetOpacity(Fxp(0.5));
            break;
        }
        // THIS WON'T WORK UNLESS I PRE-LOAD BOTH THE UI AND PAUSE
        case GAME_STATE_GAMEPLAY:
        case GAME_STATE_DEMO_LOOP:
        {
            if (g_Game.numPlayers >= THREE_PLAYER) {
                SRL::VDP2::NBG2::LoadTilemap(*GameTilemap2);
            }
            else {
                SRL::VDP2::NBG2::LoadTilemap(*GameTilemap1);
            }
            SRL::VDP2::NBG2::SetOpacity(Fxp(0.5));
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
        case GAME_STATE_CHARACTER_SELECT:
        {
            SRL::Tilemap::Interfaces::CubeTile* Tilemap = new SRL::Tilemap::Interfaces::CubeTile("NBG2CS.BIN");
            SRL::VDP2::NBG2::LoadTilemap(*Tilemap);
            delete Tilemap;
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


void switch_nbg2_img(void) {
    SRL::VDP2::NBG2::ScrollDisable();
    if (g_Game.isPaused)
    {
        SRL::VDP2::NBG2::LoadTilemap(*PauseTilemap);
        SRL::VDP2::NBG2::SetOpacity(Fxp(0.5));
    }
    else if (g_Game.numPlayers >= THREE_PLAYER) {
        SRL::VDP2::NBG2::LoadTilemap(*GameTilemap2);
    }
    else {
        SRL::VDP2::NBG2::LoadTilemap(*GameTilemap1);
    }
    SRL::VDP2::NBG2::SetOpacity(Fxp(0.5));
    SRL::VDP2::NBG2::ScrollEnable();
}