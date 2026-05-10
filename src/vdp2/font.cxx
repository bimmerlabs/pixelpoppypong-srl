#include "font.h"

void init_sgl_font(void) {
    // Initialize ascii print to use NBG3
    SRL::ASCII::LoadFontSG((uint8_t*)(VDP2_VRAM_B1 + 0x800), 0);
    SRL::ASCII::SetPalette(0);
    int myID = SRL::CRAM::GetFreeBank(SRL::CRAM::TextureColorMode::Paletted16);
    SRL::CRAM::SetBankUsedState(myID, SRL::CRAM::TextureColorMode::Paletted16, true);
    SRL::ASCII::SetFont(0);
}

void init_font(void) {
    // Initialize ascii print to use NBG0
    
    // Reye says to use new functions instead of directly doing it?
    slCharNbg0(COL_TYPE_16, CHAR_SIZE_1x1);
    slPageNbg0((void*)(VDP2_VRAM_B1 + 0x1D000), 0, PNB_1WORD | CN_10BIT);
    slPlaneNbg0(PL_SIZE_1x1);
    slMapNbg0((void*)(VDP2_VRAM_B1 + 0x1E000), (void*)(VDP2_VRAM_B1 + 0x1E000), (void*)(VDP2_VRAM_B1 + 0x1E000), (void*)(VDP2_VRAM_B1 + 0x1E000));
    
    SRL::ASCII::Clear();
    SRL::Bitmap::TGA* font = new SRL::Bitmap::TGA("FONT.TGA");
    SRL::ASCII::LoadFont(font, 1);
    delete font;
    SRL::ASCII::SetPalette(0);
    SRL::ASCII::SetFont(1);

    SRL::VDP2::NBG0::SetPriority(SRL::VDP2::Priority::Layer7);
    SRL::VDP2::NBG0::ScrollEnable();
    
    // #ifdef SRL_HIGH_RES_NON_INTERLACED
        slZoomNbg0(toFIXED(0.50), toFIXED(1.0));
    // #endif
}
