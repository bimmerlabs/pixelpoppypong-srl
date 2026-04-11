#include "highscores.h"
#include "name_entry.h"
#include "../main.h"
#include "../core/assets.h"
#include "../core/state.h"
#include "../core/backup.h"
#include "../core/screen_transition.h"
#include "../vdp2/nbg1.h"
#include "../vdp2/lighting.h"
#include "../vdp2/sprite_colors.h"

const char letters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!.< ";

NAME_ENTRY nameEntry = {};

void initNameEntryStruct(void)
{
    nameEntry.timer = NAME_ENTRY_TIMER;
    nameEntry.selection = FIRST_INITIAL;
    nameEntry.rotateLeft = false;
    nameEntry.rotateRight = false;
    nameEntry.initials[0] = 0;  // 3 letters + null terminator
    nameEntry.initials[1] = 0;
    nameEntry.initials[2] = 0;
    nameEntry.initials[3] = 0;
    nameEntry.char_id[0] = 10; // letters[] index
    nameEntry.char_id[1] = 39;
    nameEntry.char_id[2] = 39;
    nameEntry.xRadius = NAME_X_RADIUS;
    nameEntry.yRadius = NAME_Y_RADIUS;
    nameEntry.yPos = NAME_Y_POS;
    nameEntry.angle = 360;
    nameEntry.gapAngle = 0;
    nameEntry.pressedLeft = false;
    nameEntry.pressedRight = false;
    nameEntry.isAngleSnapped = true;
    nameEntry.finished = false;
    nameEntry.end = false;
}

void nameEntryInit(void)
{
    if (g_Assets.titleAssetsLoaded) {
        unloadTitleAssets();
    }
    if (g_Assets.characterAssetsLoaded) {
        unloadGameAssets();
    }
    if (!g_Assets.NameEntryAssetsLoaded)
    {
        loadNameEntryAssets();
    }
    
    SRL::Debug::PrintClearScreen();

    initNameEntryColors();
    initNameEntryStruct();
     
    set_spr_scale(&pixel_poppy, 2, 2);
    pixel_poppy.rot.z = 0;
    set_spr_position(&pixel_poppy, 0, 0, 100);
    // set to "smile"
    pixel_poppy.id = pixel_poppy.anim[0].asset + 1;
        
    convertNumberToDigits(nameEntry.timer);
    font.id = font.anim[0].asset + tens;
    font.id = font.anim[0].asset + ones;
    
    g_Game.lastState = GAME_STATE_NAME_ENTRY;
      
    g_Transition.mosaic_in = true;
    g_Transition.music_in = true;
    g_Transition.fade_in = true;
    g_Transition.all_in = true;
    playCDTrack(NAME_ENTRY_TRACK, true);
}

void nameEntryInput(void)
{
    if (nameEntry.end)
    {
        return;
    }
    
    // need to change this to if debug is enabled in the options instead of being from the makefile
    PPLAYER player = &g_Players[g_Game.winner];
    #if ENABLE_DEBUG_MODE == 1
        Digital gamepad(0);
    #else
        Digital gamepad(player->input->id);
    #endif
    
    if (gamepad.IsHeld(Digital::Button::Up))
    {
        if (nameEntry.yRadius < Fxp_0)
        {
            nameEntry.xRadius -= Fxp_HALF;
            nameEntry.yRadius += Fxp_2;
        }
        else if (nameEntry.yRadius < Fxp_100)
        {
            nameEntry.xRadius += Fxp_HALF;
            nameEntry.yRadius += Fxp_2;
        }
        g_Game.vblankClearScreen = true;
    }
    
    if (gamepad.IsHeld(Digital::Button::Down))
    {
        if (nameEntry.yRadius > Fxp_0)
        {
            nameEntry.xRadius -= Fxp_HALF;
            nameEntry.yRadius -= Fxp_2;
        }
        else if (nameEntry.yRadius > -Fxp_100)
        {
            nameEntry.xRadius += Fxp_HALF;
            nameEntry.yRadius -= Fxp_2;
        }
        g_Game.vblankClearScreen = true;
    }
    
    if (!nameEntry.isAngleSnapped)
    {
         return;
    }
    
    if (gamepad.IsHeld(Digital::Button::Left) && !nameEntry.finished)
    {
        g_Game.vblankClearScreen = true;
        nameEntry.pressedLeft = true;
        nameEntry.pressedRight = false;
        nameEntry.isAngleSnapped = false;
        nameEntry.angle += 1;
        if (nameEntry.angle > 360)
            nameEntry.angle -= 360;
    }
    else if (gamepad.IsHeld(Digital::Button::Right) && !nameEntry.finished)
    {
        g_Game.vblankClearScreen = true;
        nameEntry.pressedLeft = false;
        nameEntry.pressedRight = true;
        nameEntry.isAngleSnapped = false;
        nameEntry.angle -= 1;
        if (nameEntry.angle < 0)
            nameEntry.angle += 360;
    }
    else if (gamepad.WasPressed(Digital::Button::A) || gamepad.WasPressed(Digital::Button::C))
    {
        g_Game.vblankClearScreen = true;
        
        if (nameEntry.finished && nameEntry.angle == GAP_ANGLE)
        {
            pcm_play(g_Assets.load_okPcm8, PCM_VOLATILE, 7);
            nameEntry.end = true;
            return;
        }
        
        if (!nameEntry.finished && nameEntry.angle != GAP_ANGLE)
        {
            pcm_play(g_Assets.name_ketPcm8, PCM_PROTECTED, 7);
            nameEntry.selection++;
        }
        
        if (nameEntry.selection == MAX_INITIAL)
        {
            pcm_play(g_Assets.name_brkPcm8, PCM_VOLATILE, 6);
            nameEntry.finished = true;
            nameEntry.isAngleSnapped = false;
        }
    }
    else if (gamepad.WasPressed(Digital::Button::B))
    {
        g_Game.vblankClearScreen = true;
        pcm_play(g_Assets.name_canPcm8, PCM_PROTECTED, 7);
        
        if (nameEntry.selection == MAX_INITIAL)
        {
            nameEntry.angle = 360;
            nameEntry.selection--;
            nameEntry.char_id[nameEntry.selection] = 39;
            initNameEntryColors();
            nameEntry.finished = false;
            nameEntry.isAngleSnapped = true;
            nameEntry.rotateRight = false;
            nameEntry.rotateLeft = false;
            pixel_poppy.id = pixel_poppy.anim[0].asset + 2;
        }
        else if (nameEntry.selection > FIRST_INITIAL)
        {
            nameEntry.selection--;
        }
    }
        
    if (nameEntry.isAngleSnapped == false)
    {
        pixel_poppy.id = pixel_poppy.anim[0].asset;
    }
    else
    {
        pixel_poppy.id = pixel_poppy.anim[0].asset + 1;
    }
}

void nameEntryUpdate(void)
{
    if (nameEntry.timer > 0 && g_Game.frame % 60 == 0) { // modulus
        nameEntry.timer--;
    }

    SRL::Debug::Print(17, 2, "Name Entry");
    
    if (nameEntry.timer > 0 && !nameEntry.end)
    {
        // make an inline sub for this
        convertNumberToDigits(nameEntry.timer);
        set_spr_position(&font, 0, -170, 50);
        set_spr_scale(&font, 1.1, 1.1);
        font.id = font.anim[0].asset + tens;
        font.zmode = _ZmRC;
        my_sprite_draw(&font);
        font.id = font.anim[0].asset + ones;
        font.zmode = _ZmLC;
        my_sprite_draw(&font);
    }
    
    // make an inline sub for this
    if (nameEntry.char_id[FIRST_INITIAL] != 39)
    {
        set_spr_position(&font, -24, nameEntry.yPos.As<int32_t>(), 50);
        set_spr_scale(&font, 2, 2);
        font.id = font.anim[0].asset + nameEntry.char_id[FIRST_INITIAL];
        font.zmode = _ZmRC;
        my_sprite_draw(&font);
    }
    if (nameEntry.selection >= 1 && nameEntry.char_id[SECOND_INITIAL] != 39)
    {
        set_spr_position(&font, 0, nameEntry.yPos.As<int32_t>(), 50);
        set_spr_scale(&font, 2, 2);
        font.id = font.anim[0].asset + nameEntry.char_id[SECOND_INITIAL];
        font.zmode = _ZmCC;
        my_sprite_draw(&font);
    }
    if (nameEntry.selection >= 2 && nameEntry.char_id[THIRD_INITIAL] != 39)
    {
        set_spr_position(&font, 24, nameEntry.yPos.As<int32_t>(), 50);
        set_spr_scale(&font, 2, 2);
        font.id = font.anim[0].asset + nameEntry.char_id[THIRD_INITIAL];
        font.zmode = _ZmLC;
        my_sprite_draw(&font);
    }
    if (nameEntry.end && nameEntry.xRadius > END_RADIUS)
    {
        pixel_poppy.id = pixel_poppy.anim[0].asset + 3;
        nameEntry.xRadius -= Fxp(6);
        nameEntry.yRadius -= Fxp(4);
        nameEntry.angle += 3;
        if (nameEntry.angle > 360)
            nameEntry.angle -= 360;
        if (nameEntry.yPos > 0)
            nameEntry.yPos -= 2;
    }
    
    font.zmode = _ZmCC;
    nameEntryDraw();
    
    
    nameEntry.initials[0] = letters[nameEntry.char_id[FIRST_INITIAL]];
    nameEntry.initials[1] = letters[nameEntry.char_id[SECOND_INITIAL]];
    nameEntry.initials[2] = letters[nameEntry.char_id[THIRD_INITIAL]];
    nameEntry.initials[3] = '\0';
    
    if(nameEntry.timer == 0 || nameEntry.xRadius <= END_RADIUS)
    {
        SRL::Debug::PrintClearScreen();
        addHighScore(g_Players[g_Game.winner].score.points, nameEntry.initials);
        // save_game_backup();
        g_Game.lastState = GAME_STATE_NAME_ENTRY;
        transitionState(GAME_STATE_HIGHSCORES);
        return;
    }
}

void nameEntryDraw(void)
{
    if (!nameEntry.finished)
    {
        nameEntry.angle = snap_to_nearest_12(nameEntry.angle);
    }
    
    if (nameEntry.finished)
    {
        nameEntry.angle = snap_to_end(nameEntry.angle);
    }
    
    for (nameEntry.gapAngle = 0; nameEntry.gapAngle <= 360; nameEntry.gapAngle += GAP_ANGLE)
    {
            nameEntryPositionUpdate((nameEntry.angle+ 6 + nameEntry.gapAngle), (nameEntry.gapAngle + 102));
    }
    
    do_update_font2All = calculate_sprites_color(&p_rangeFont2All);
    set_spr_scale(&pixel_poppy, 6, 6);
    int poppyAngle = nameEntry.angle;
    if (poppyAngle > 360)
        poppyAngle -= 360;
    pixel_poppy.rot.z = Fxp::Convert(-TO_TURNS*poppyAngle);
    set_spr_position(&pixel_poppy, 0, 0, 100);
    my_sprite_draw_rot(&pixel_poppy);
    
    #if ENABLE_DEBUG_MODE == 1
    if (g_GameOptions.debug_display)
    {
        SRL::Debug::Print(2, 8, "pressedLeft:%d", nameEntry.pressedLeft);
        SRL::Debug::Print(2, 9, "pressedRight:%d", nameEntry.pressedRight);
        SRL::Debug::Print(2, 10, "Rad:X=%3d", nameEntry.xRadius.As<int32_t>());
        SRL::Debug::Print(2, 11, "Rad:Y=%3d", nameEntry.yRadius.As<int32_t>());
        SRL::Debug::Print(2, 12, "Pos:X=%3d", light.x.As<int32_t>());
        SRL::Debug::Print(2, 13, "Pos:Y=%3d", light.y.As<int32_t>());
        SRL::Debug::Print(2, 14, "Angle:%3d", nameEntry.angle);
        SRL::Debug::Print(2, 15, "nameEntry.end:%i", nameEntry.end);
        SRL::Debug::Print(2, 16, "isAngleSnapped:%i", nameEntry.isAngleSnapped);
        SRL::Debug::Print(2, 17, "finished:%i", nameEntry.finished);
    }
    #endif
}

void nameEntryPositionUpdate(int angle, int sprAngle)
{
    if (angle > 360)
        angle -= 360;
    
    if (sprAngle > 360)
        sprAngle -= 360;
        
    int spr_id = ((sprAngle / 12) % 30) + 10; // because letter A starts at 10
        
    int scaleAngle = angle + 90;
    if (scaleAngle > 360)
        scaleAngle -= 360;
        
    Fxp fixedAngle = Fxp::Convert(angle * TO_TURNS);
    light.x = SRL::Math::Trigonometry::Cos(fixedAngle) * nameEntry.xRadius;
    light.y = SRL::Math::Trigonometry::Sin(fixedAngle) * nameEntry.yRadius;
    font.pos.x = 2*(light.x);
    font.pos.y = -2*(light.y);    
    
    if (angle > 262 && angle < 278)
    {
        if (!nameEntry.finished)
        {
            nameEntry.char_id[nameEntry.selection] = spr_id;
        }
        font.scl.x = Fxp(2.7);
    }
    else
    {
        Fxp fixedscaleAngle = Fxp::Convert(scaleAngle * TO_TURNS);
        font.scl.x = Fxp_1 + (Fxp_127 + SRL::Math::Trigonometry::Cos(fixedscaleAngle) * NAME_X_RADIUS) / Fxp(200); // NOT SURE IF THIS NEEDS TO BE FIXED 200?
    }
    
    font.scl.y = font.scl.x;
    
    int zAngle = angle + 91;
    int zPos = 0;
    
    if (zAngle > 360)
        zAngle -= 360;
        
    if (zAngle > 258 && zAngle < 282)
    {
        zPos = 90;  // Keep zPos fixed at 90 within the hysteresis range
    }
    else
    {
        zPos = 180 - ABS(zAngle - 180);
    }
    
    font.pos.z = Fxp::Convert(zPos+50.0f);
    
    int colorid = spr_id + 54; // + 64 degrees -10 (start of "A")
    
    if (!nameEntry.finished)
    {
        hslSprites[colorid].s = 255 - zPos;
        hslSprites[colorid].l = 255 - zPos;
    }
    else
    {
        DateTime time = DateTime::Now();
        int hue = time.Minute()*6;
        hslSprites[colorid].h = hue;
        hslSprites[colorid].s = 240;
        hslSprites[colorid].l = 240;
    }
    
    font.id = font.anim[0].asset + spr_id;
    my_sprite_draw(&font);
}

int snap_to_nearest_12(int angle)
{
    // If already snapped, do nothing
    if (nameEntry.isAngleSnapped)
    {
        return angle;
    }

    // Adjust angle only when a button is pressed
    if (nameEntry.pressedRight)
    {
        angle--;  // Move counterclockwise
        if (angle < 0)
            angle += 360;
    }
    else if (nameEntry.pressedLeft)
    {
        angle++;  // Move clockwise
        if (angle > 360)
            angle -= 360;
    }

    // If angle is now a multiple of 12, stop adjusting
    if (angle % 12 == 0)
    {
        pcm_play(g_Assets.name_curPcm8, PCM_VOLATILE, 7);
        nameEntry.isAngleSnapped = true;  // Mark snapping complete
    }

    return angle;
}

int snap_to_end(int angle)
{
    // If already snapped, do nothing
    if (nameEntry.isAngleSnapped)
    {
        return angle;
    }
    
    if (angle == 0)
        angle = 360;
        
    if (!nameEntry.rotateLeft && !nameEntry.rotateRight)
    {
        if (angle - 180 < 0)
        {
            nameEntry.rotateRight = true;
        }
        else
        {
            nameEntry.rotateLeft = true;
        }
    }
    
    // Adjust angle only when a button is pressed
    if (nameEntry.rotateRight)
    { // need to compare to original angle value and set a boolean?
        angle -= 6;  // Move counterclockwise
        pcm_play(g_Assets.name_curPcm8, PCM_VOLATILE, 7);
        if (angle < 0)
            angle += 360;
    }
    
    if (nameEntry.rotateLeft)
    {
        angle += 6;  // Move clockwise
        pcm_play(g_Assets.name_curPcm8, PCM_VOLATILE, 7);
        if (angle > 360)
            angle -= 360;
    }
    
    // If angle is now a multiple of 12, stop adjusting
    if (angle == 12)
    {
        nameEntry.isAngleSnapped = true;  // Mark snapping complete
    }

    return angle;
}