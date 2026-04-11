#include "character_select.h"
#include "player_setup.h"
#include "../main.h"
#include "../core/assets.h"
#include "../core/input.h"
#include "../core/state.h"
#include "../core/backup.h"
#include "../core/screen_transition.h"
#include "../vdp2/sprite_colors.h"
#include "../vdp2/lighting.h"
#include "../vdp2/nbg1.h"
#include "../vdp2/LightUpdater.hxx"

STORY_CHARACTER_SELECT characterSelect = {};

PPLAYER player = &g_Players[0];

static bool draw_portrait = true;
static int newAngle;
static uint8_t randomRotations = 0;

// constexpr configs
constexpr LightConfig defaultLight(
    Angle(0.0166666666666667), // angle step (trying to aim for 1 per second)
    Fxp(90),                  // ellipse radius X
    Fxp(90),                   // ellipse radius Y
    Fxp(6),                    // shadow offset X
    Fxp(6)                     // shadow offset Y
);

LightUpdater updater(defaultLight);

    
void initCharacterSelectStruct(void)
{
    characterSelect.timer = CHARACTER_SELECT_TIMER;
    characterSelect.selection = 0;
    characterSelect.rotateLeft = false;
    characterSelect.rotateRight = false;

    characterSelect.xRadius = CHARACTER_X_RADIUS * 4;
    characterSelect.yRadius = CHARACTER_Y_RADIUS * 4;
    characterSelect.angle = 0;
    characterSelect.gapAngle = 0;
    characterSelect.spr_id = 0;
    characterSelect.pressedLeft = false;
    characterSelect.pressedRight = false;
    characterSelect.isAngleSnapped = true;
    characterSelect.snapEnd = false;
    characterSelect.start = false;
    characterSelect.finished = false;
    characterSelect.end = false;
    randomRotations = 0;
    newAngle = 0;
}

void characterSelectInit(void)
{
    g_Game.lastState = GAME_STATE_CHARACTER_SELECT;
    if (g_Assets.titleAssetsLoaded) {
        unloadTitleAssets();
    }
    if (g_Assets.NameEntryAssetsLoaded) {
        unloadNameEntryAssets();
    }
    if (!g_Assets.characterAssetsLoaded) {
        loadCharacterAssets();
    }
    if (!g_Assets.NameEntryAssetsLoaded)
    {
        loadNameEntryAssets();
    }
    
    SRL::Debug::PrintClearScreen();

    reset_sprites();
    
    reset_normal_map();
    light.x = Fxp(45);
    light.y = Fxp(200);
    light.z = Fxp(300);
    do_update_ppplogo = true;
    
    initCharacterSelectStruct();    
    initAvailableCharacters();
    characterAvailable[CHARACTER_NONE] = true; // random
    
    g_Game.numPlayers = TWO_PLAYER;
    initPlayers();
    // initTeams();
    g_Game.currentNumPlayers = 2; // problematic?
                
    player_bg.mesh = MESHoff;
    
    set_spr_scale(player->_portrait, 0, 0);
    set_spr_position(player->_portrait, 0, -1, 100);
    player->character.choice = CHARACTER_MACCHI;
    validateCharacters(player);
    assignCharacterSprite(player); 
        
    convertNumberToDigits(characterSelect.timer);
    font.id = font.anim[0].asset + tens;
    font.id = font.anim[0].asset + ones;
    
    g_Game.lastState = GAME_STATE_CHARACTER_SELECT;
      
    g_Transition.mosaic_in = true;
    g_Transition.music_in = true;
    g_Transition.fade_in = true;
    g_Transition.all_in = true;
}

void characterSelectInput(void)
{
    if (characterSelect.end)
    {
        return;
    }

    Digital gamepad(player->input->id);
    
    // if (gamepad.IsHeld(Digital::Button::L))
    // {
        // light.x -= Fxp_1;
        // // light.y -= Fxp_1;
        // do_update_ppplogo = true;
    // }    
    // if (gamepad.IsHeld(Digital::Button::R))
    // {
        // light.x += Fxp_1;
        // // light.y -= Fxp_1;
        // do_update_ppplogo = true;
    // }
    
    // if (gamepad.IsHeld(Digital::Button::X))
    // {
        // // light.x -= Fxp_1;
        // light.y -= Fxp_1;
        // do_update_ppplogo = true;
    // }    
    // if (gamepad.IsHeld(Digital::Button::Y))
    // {
        // // light.x += Fxp_1;
        // light.y += Fxp_1;
        // do_update_ppplogo = true;
    // }
    // if (gamepad.IsHeld(Digital::Button::Z))
    // {
        // // light.x += Fxp_1;
        // light.z -= Fxp_1;
        // do_update_ppplogo = true;
    // }
    // if (gamepad.IsHeld(Digital::Button::START))
    // {
        // // light.x += Fxp_1;
        // light.z += Fxp_1;
        // do_update_ppplogo = true;
    // }
    
    if (gamepad.IsHeld(Digital::Button::Up))
    {
        if (characterSelect.yRadius < Fxp_0)
        {
            characterSelect.xRadius -= Fxp_HALF;
            characterSelect.yRadius += Fxp_2;
        }
        else if (characterSelect.yRadius < Fxp_100)
        {
            characterSelect.xRadius += Fxp_HALF;
            characterSelect.yRadius += Fxp_2;
        }
        g_Game.vblankClearScreen = true;
    }
    
    if (gamepad.IsHeld(Digital::Button::Down))
    {
        if (characterSelect.yRadius > Fxp_0)
        {
            characterSelect.xRadius -= Fxp_HALF;
            characterSelect.yRadius -= Fxp_2;
        }
        else if (characterSelect.yRadius > -Fxp_100)
        {
            characterSelect.xRadius += Fxp_HALF;
            characterSelect.yRadius -= Fxp_2;
        }
        g_Game.vblankClearScreen = true;
    }
    
    if (!characterSelect.isAngleSnapped)
    {
         return;
    }

        
    if (gamepad.WasPressed(Digital::Button::B) && !player->character.selected)
    {
        if (characterSelect.selection > 0)
        {
            characterSelect.selection--;
        }
        if (characterSelect.selection == 0)
        {
            Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
            g_Game.vblankClearScreen = true;
            // SRL::VDP2::NBG2::ScrollDisable();
            transitionState(GAME_STATE_TITLE_SCREEN);
        }
    }
    
    if (gamepad.IsHeld(Digital::Button::Left) && !characterSelect.finished)
    {
        int next_char_id = characterSelect.spr_id -= 1;
        if (next_char_id < CHARACTER_MACCHI)
            next_char_id = CHARACTER_NONE;
        // SRL::Debug::Print(2, 9, "next_char_id:%d  ", next_char_id);
        // SRL::Debug::Print(2, 10, "characterAvailable:%d", characterAvailable[next_char_id]);
        
        if (characterAvailable[next_char_id])
        {
            g_Game.vblankClearScreen = true;
            characterSelect.isAngleSnapped = false;
            characterSelect.pressedLeft = true;
            characterSelect.pressedRight = false;
            characterSelect.angle += MOVEMENT_SPEED;
            if (characterSelect.angle > 360)
                characterSelect.angle -= 360;
        }
    }
    else if (gamepad.IsHeld(Digital::Button::Right) && !characterSelect.finished)
    {
        int next_char_id = characterSelect.spr_id += 1;
        if (next_char_id > CHARACTER_NONE)
            next_char_id = CHARACTER_MACCHI;
        // SRL::Debug::Print(2, 9, "next_char_id:%d  ", next_char_id);
        // SRL::Debug::Print(2, 10, "characterAvailable:%d", characterAvailable[next_char_id]);
                
        if (characterAvailable[next_char_id])
        {
            g_Game.vblankClearScreen = true;
            characterSelect.isAngleSnapped = false;
            characterSelect.pressedLeft = false;
            characterSelect.pressedRight = true;
            characterSelect.angle -= MOVEMENT_SPEED;
            if (characterSelect.angle < 0)
                characterSelect.angle += 360;
        }
    }
    else if (gamepad.WasPressed(Digital::Button::A) || gamepad.WasPressed(Digital::Button::C))
    {     
        if (characterSelect.finished)
        {
            Pcm::Play(Sounds.Name[LoadOkSnd], PlayMode::Volatile);
            characterSelect.end = true;
            return;
        }

        if (!characterSelect.finished)
        {
            Pcm::Play(Sounds.Name[NameKetSnd]);
            characterSelect.selection++;
        }

        if (characterSelect.selection == CONFIRM_PRESSES)
        {
            Pcm::Play(Sounds.Name[NameBrkSnd], PlayMode::Volatile, 6);
            characterSelect.finished = true;
            characterSelect.isAngleSnapped = false;
        }
    }
    else if (gamepad.WasPressed(Digital::Button::B) && player->character.selected)
    {
        g_Game.vblankClearScreen = true;
        Pcm::Play(Sounds.Name[NameCanSnd]);
        if (characterSelect.selection == CONFIRM_PRESSES)
        {
            characterAvailable[player->character.choice] = true;
            player->character.selected = false;
            characterSelect.finished = false;
            characterSelect.selection--;
        }
    }
}

void characterSelectUpdate(void)
{  
    if (characterSelect.timer > 0 && g_Game.frame % 60 == 0 && characterSelect.start) // modulus
    {
        characterSelect.timer--;
    }

    if (characterSelect.timer > 0 && characterSelect.start && !characterSelect.end)
    {
        // make an inline sub for this
        convertNumberToDigits(characterSelect.timer);
        set_spr_position(&font, 0, -170, 50);
        set_spr_scale(&font, 1.1, 1.1);
        font.id = font.anim[0].asset + tens;
        font.zmode = _ZmRC;
        my_sprite_draw(&font);
        font.id = font.anim[0].asset + ones;
        font.zmode = _ZmLC;
        my_sprite_draw(&font);
    }
    
    if (characterSelect.end && characterSelect.xRadius > END_RADIUS)
    {
        characterSelect.xRadius -= Fxp(6);
        characterSelect.yRadius += Fxp(4);
        characterAvailable[player->character.choice] = false;
        player->character.selected = true;
        player->_portrait->id = player->_portrait->anim[0].asset + player->character.choice;
        assignCharacterSprite(player);
    }
       
    if (player->character.choice == CHARACTER_NONE)
    {
        updater.update(light, shadow);
        my_sprite_draw(&shadow);
    }
    
    looped_animation_pow(&paw[characterSelect.spr_id], 4);
    characterSelectDraw();
           
    if(characterSelect.timer == 0 || characterSelect.xRadius <= END_RADIUS)
    {
        // this is broken for "random" characters
        characterSelect.end = true;
        characterSelect.finished = true;
        characterAvailable[player->character.choice] = false;
        player->character.selected = true;
        player->_portrait->id = player->_portrait->anim[0].asset + player->character.choice;
        assignCharacterSprite(player);
        SRL::Debug::PrintClearScreen();
        transitionState(GAME_STATE_GAMEPLAY);
        return;
    }
}

void characterSelectDraw(void)
{    
    Digital gamepad(player->input->id);
        
    if (!characterSelect.finished)
    {
        characterSelect.angle = snap_to_nearest_angle(characterSelect.angle);
    }
    
    if (characterSelect.finished)
    {
        if (!characterSelect.snapEnd && player->character.choice == CHARACTER_NONE)
        {
            newAngle = selectRandomCharacter();
            characterSelect.snapEnd = true;
        }
        else if (!characterSelect.snapEnd ) {
            characterSelect.isAngleSnapped = true;
        }
        snap_to_random_character(newAngle);
    }
        
    if (characterSelect.isAngleSnapped && characterSelect.start) // take this out of the characterSelectPositionUpdate loop
    {
        if (!g_GameOptions.debug_display && !gamepad.IsHeld(Digital::Button::Left) && !gamepad.IsHeld(Digital::Button::Right)) 
        {
            SRL::Debug::Print(15, 10, "%s", fullCharacterNames[player->character.choice]);
            PrintWrapped(4, 19, 36, characterBios[player->character.choice]);
        }
    }
    
    if (!characterSelect.start) // transition in
    {
        if (player->_portrait->scl.x < Fxp_2) 
        {
            player->_portrait->scl.x += Fxp(0.033);
            player->_portrait->scl.y += Fxp(0.033);
        }

        if (characterSelect.xRadius > CHARACTER_X_RADIUS)
        {
            characterSelect.xRadius -= Fxp(7);
        }

        if (characterSelect.yRadius >= CHARACTER_Y_RADIUS)
        {
            characterSelect.start = true;
            player->_portrait->scl.x = Fxp_2;
            player->_portrait->scl.y = Fxp_2;
        }
        else {
            characterSelect.yRadius += Fxp_3;
        }
    }
    else {
        SRL::Debug::Print(12, 2, "Select Your Character");
        
        // SRL::Debug::Print(2, 10, "light.x:%3d", light.x.As<int32_t>());
        // SRL::Debug::Print(2, 11, "light.y:%3d", light.y.As<int32_t>());
        // SRL::Debug::Print(2, 12, "light.z:%3d", light.z.As<int32_t>());

        characterMeterDraw();            
    }

    for (characterSelect.gapAngle = 0; characterSelect.gapAngle <= 360; characterSelect.gapAngle += CHARACTER_GAP_ANGLE)
    {
        int rotationAngle = characterSelect.angle + 0 + characterSelect.gapAngle;
        int sprAngle = characterSelect.gapAngle + 102; // 102 - the magic number?  I don't remember why it has to be 102..
        characterSelectPositionUpdate(rotationAngle, sprAngle);
    }

    player->_portrait->id = player->_portrait->anim[0].asset + characterSelect.spr_id;

    my_sprite_draw(player->_portrait);
    
    #if ENABLE_DEBUG_MODE == 1
    if (g_GameOptions.debug_display)
    {
        // SRL::Debug::Print(2, 8, "pressedLeft:%d", characterSelect.pressedLeft);
        // SRL::Debug::Print(2, 9, "pressedRight:%d", characterSelect.pressedRight);
        // SRL::Debug::Print(2, 10, "Rad:X=%3d", characterSelect.xRadius.As<int32_t>());
        // SRL::Debug::Print(2, 11, "Rad:Y=%3d", characterSelect.yRadius.As<int32_t>());
        // SRL::Debug::Print(2, 12, "Pos:X=%3d", light.x.As<int32_t>());
        // SRL::Debug::Print(2, 13, "Pos:Y=%3d", light.y.As<int32_t>());
        // SRL::Debug::Print(2, 10, "inputSelected:%i", player->input->isSelected);
        // SRL::Debug::Print(2, 11, "startSelection:%i", player->startSelection);
        // SRL::Debug::Print(2, 12, "spr_id:%2d", characterSelect.spr_id);
        // SRL::Debug::Print(2, 13, "character.choice:%2d", player->character.choice);
        SRL::Debug::Print(2, 14, "Angle:%3d", characterSelect.angle);
        // SRL::Debug::Print(2, 15, "sprID:%3d", characterSelect.spr_id);
        SRL::Debug::Print(2, 16, "characterSelect.end:%i", characterSelect.end);
        SRL::Debug::Print(2, 17, "isAngleSnapped:%i", characterSelect.isAngleSnapped);
        // SRL::Debug::Print(2, 18, "finished:%i", characterSelect.finished);
        // SRL::Debug::Print(2, 19, "characterSelect.start:%i", characterSelect.start);
        SRL::Debug::Print(2, 20, "newAngle:%3d", newAngle);
    }
    #endif
}

void characterMeterDraw(void)
{
    int text_x = 2;
    int text_y = 26;
    Fxp meter_x = -Fxp(320);
    Fxp meter_y = Fxp(184);
    
    // SPEED
    if (!g_GameOptions.debug_display) {
        if (g_GameOptions.debug_mode) {
            SRL::Debug::Print(text_x, text_y,   "Speed:%d    ", player->maxSpeed.As<uint8_t>());
        }
        else {
            SRL::Debug::Print(text_x, text_y,   "Speed    ");
        }
    }
    // yellow
    meter.id = meter.anim[0].asset;
    Fxp speed = player->maxSpeed / 4;
    set_spr_scale_fxp(&meter, speed, METER_HEIGHT);
    set_spr_position_fxp(&meter, meter_x, meter_y, 100);
    my_sprite_draw(&meter);
    // red
    meter.id = meter.anim[0].asset + 1;
    set_spr_scale_fxp(&meter, (METER_WIDTH-speed), METER_HEIGHT);
    set_spr_position_fxp(&meter, (meter_x+(Fxp_2 * player->maxSpeed)), meter_y, 100);
    my_sprite_draw(&meter);
    
    // ACCELERATION
    if (!g_GameOptions.debug_display) {
        if (g_GameOptions.debug_mode) {
            SRL::Debug::Print(text_x+14, text_y, "Accel:%d    ", player->acceleration.As<uint8_t>()); 
        }
        else {
            SRL::Debug::Print(text_x+14, text_y, "Accel.    "); 
        }
    }
    
    // yellow       
    meter.id = meter.anim[0].asset;
    Fxp acceleration = player->acceleration / 4;
    set_spr_scale_fxp(&meter, acceleration, METER_HEIGHT);
    set_spr_position_fxp(&meter, (meter_x+Fxp(220)), meter_y, 100);
    my_sprite_draw(&meter);
    // red
    meter.id = meter.anim[0].asset + 1;
    set_spr_scale_fxp(&meter, (METER_WIDTH-acceleration), METER_HEIGHT);
    set_spr_position_fxp(&meter, (meter_x+Fxp(220)+(Fxp_2 * player->acceleration)), meter_y, 100);
    my_sprite_draw(&meter);
    
    // POWER
    if (!g_GameOptions.debug_display) {
        if (g_GameOptions.debug_mode) {
            SRL::Debug::Print(text_x+28, text_y, "Power:%d    ", player->power.As<uint8_t>());
        }
        else {
            SRL::Debug::Print(text_x+28, text_y, "Power    ");
        }
    }
    // yellow
    meter.id = meter.anim[0].asset;
    Fxp power = player->power / 4;
    set_spr_scale_fxp(&meter, power, METER_HEIGHT);
    set_spr_position_fxp(&meter, (meter_x+Fxp(440)), meter_y, 100);
    my_sprite_draw(&meter);
    // red
    meter.id = meter.anim[0].asset + 1;
    set_spr_scale_fxp(&meter, (METER_WIDTH-power), METER_HEIGHT);
    set_spr_position_fxp(&meter, (meter_x+Fxp(440)+(Fxp_2 * player->power)), meter_y, 100);
    my_sprite_draw(&meter);
}

void characterSelectPositionUpdate(int angle, int sprAngle)
{
    if (angle > 360)
        angle -= 360;
    
    if (sprAngle > 360)
        sprAngle -= 360;

    // SRL::Debug::Print(2, 12, "angle:%3d", angle);
    // SRL::Debug::Print(2, 13, "sprAngle:%3d", sprAngle);

    int spr_id = ((sprAngle / CHARACTER_GAP_ANGLE) % 30);
    
    int scaleAngle = angle + 90;
    if (scaleAngle > 360)
        scaleAngle -= 360;
        
    Fxp fixedAngle = Fxp::Convert(angle * TO_TURNS);
    paw[spr_id].pos.x = 2*SRL::Math::Trigonometry::Cos(fixedAngle) * characterSelect.xRadius + Fxp_8;
    paw[spr_id].pos.y = -2*SRL::Math::Trigonometry::Sin(fixedAngle) * characterSelect.yRadius;  
    
    if (angle > 262 && angle < 278)
    {
        paw[spr_id].scl.x = Fxp(3);
        characterSelect.spr_id = spr_id;
        player->character.choice = spr_id;
        assignPlayerStats(player);
        // SRL::Debug::Print(2, 9, "characterAvailable:%d", characterAvailable[spr_id]);
        // SRL::Debug::Print(2, 10, "characterUnlocked:%d", characterUnlocked[spr_id]);
        // SRL::Debug::Print(2, 20, "spr_id:%d", spr_id);
        // SRL::Debug::Print(2, 21, "isAvailable:%d", characterAvailable[player->character.choice]);
    }
    else
    {
        paw[spr_id].id = paw[spr_id].anim[0].asset;
        paw[spr_id].anim[0].frame = 0;
        Fxp fixedscaleAngle = Fxp::Convert(scaleAngle * TO_TURNS);
        paw[spr_id].scl.x = Fxp_1 + (Fxp_127 + SRL::Math::Trigonometry::Cos(fixedscaleAngle) * CHARACTER_X_RADIUS) / Fxp(200); // NOT SURE IF THIS NEEDS TO BE FIXED 200?
    }
            
    paw[spr_id].scl.y = paw[spr_id].scl.x;
    
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
    
    paw[spr_id].pos.z = Fxp::Convert(zPos+50.0f);
    
    int colorid = spr_id + 54; // + 64 degrees -10 (start of "A")
    
    if (!characterSelect.finished)
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
    
    paw[spr_id].flip = sprNoflip;
    my_sprite_draw(&paw[spr_id]);
}

int snap_to_nearest_angle(int angle)
{
    // If already snapped, do nothing
    if (characterSelect.isAngleSnapped)
    {
        return angle;
    }

    // Adjust angle only when a button is pressed
    if (characterSelect.pressedRight)
    {
        angle -= MOVEMENT_SPEED;  // Move counterclockwise
        if (angle < 0)
            angle += 360;
    }
    else if (characterSelect.pressedLeft)
    {
        angle += MOVEMENT_SPEED;  // Move clockwise
        if (angle > 360)
            angle -= 360;
    }

    // If angle is now a multiple of CHARACTER_GAP_ANGLE, stop adjusting
    if (angle % (CHARACTER_GAP_ANGLE) == 0)
    {
        Pcm::Play(Sounds.Name[NameCurSnd], PlayMode::Volatile);
        if (characterAvailable[player->character.choice])
        {
            characterSelect.isAngleSnapped = true;  // Mark snapping complete
        }
        else {
            characterSelect.isAngleSnapped = false;
            // Adjust angle only when a button is pressed
            if (characterSelect.pressedRight)
            {
                angle--;  // Move counterclockwise
                if (angle < 0)
                    angle += 360;
            }
            else if (characterSelect.pressedLeft)
            {
                angle++;  // Move clockwise
                if (angle > 360)
                    angle -= 360;
            }
        }
    }

    return angle;
}

void snap_to_random_character(int targetAngle)
{  
    if (characterSelect.angle == 360)
        characterSelect.angle = 0;
        
    // If already at right location, do nothing
    if (characterSelect.isAngleSnapped)
    {
        return;
    }
        
    if (!characterSelect.rotateLeft && !characterSelect.rotateRight)
    {
        if (characterSelect.angle - 180 < 0)
        {
            characterSelect.rotateRight = true;
        }
        else
        {
            characterSelect.rotateLeft = true;
        }
    }
    
    // Adjust angle only when a button is pressed
    if (characterSelect.rotateRight)
    { // need to compare to original angle value and set a boolean?
        characterSelect.angle -= 5;  // Move counterclockwise
        Pcm::Play(Sounds.Name[NameCurSnd], PlayMode::Volatile);
        if (characterSelect.angle < 0)
            characterSelect.angle += 360;
    }
    
    if (characterSelect.rotateLeft)
    {
        characterSelect.angle += 5;  // Move clockwise
        Pcm::Play(Sounds.Name[NameCurSnd], PlayMode::Volatile);
        if (characterSelect.angle > 360)
            characterSelect.angle -= 360;
    }
        
    if (characterSelect.angle == targetAngle)
    {
        randomRotations++;
    }
    if (randomRotations == 2)
    {
        characterSelect.isAngleSnapped = true;  // Mark snapping complete
    }
}