#include "character_select.h"
#include "player_setup.h"
#include "../main.h"
#include "../core/input.h"
#include "../core/state.h"
#include "../core/screen_transition.h"
#include "../vdp2/lighting.h"
#include "../vdp2/nbg1.h"
#include "../vdp2/LightUpdater.hxx"

STORY_CHARACTER_SELECT characterSelect = {};

PPLAYER player = &g_Players[0];

static bool press_start = true;
static int newAngle;
static uint8_t randomRotations = 0;

constexpr LightConfig defaultLight(
    Angle(0.0166666666666667),  // angle step (trying to aim for 1 per second)
    Fxp(90),                    // ellipse radius X
    Fxp(90),                    // ellipse radius Y
    Fxp(6),                     // shadow offset X
    Fxp(6),                     // shadow offset Y
    Fxp(0),                     // x position of object casting shadow
    Fxp(-24)                    // y position of object casting shadow
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
    
    if (!g_Assets.characterAssetsLoaded) {
        loadCharacterAssets();
    }

    init_nbg2_img();
    
    SRL::Debug::PrintClearScreen();

    reset_sprites();

    reset_normal_map();
    light.x = Fxp(45);
    light.y = Fxp(200);
    light.z = Fxp(300);
    do_update_ppplogo = true;

    initCharacterSelectStruct();
    initAvailableCharacters(); // this is for the player
    characterAvailable[CHARACTER_NONE] = true; // random

    g_Game.numPlayers = TWO_PLAYER;
    initPlayers();
    g_Game.currentNumPlayers = 2;

    player_bg.mesh = MESHoff;

    set_spr_scale(player->_portrait, 0, 0);
    set_spr_position(player->_portrait, 0, -24, 100);
    player->character.choice = CHARACTER_MACCHI; // default
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

    if (!characterSelect.isAngleSnapped)
    {
         return;
    }

    Digital gamepad(player->input->id);
    
    if (gamepad.WasPressed(Digital::Button::B))
    {
        
        if (characterSelect.selection == CONFIRM_PRESSES)
        {
            Pcm::Play(Sounds.Name[NameCanSnd]);
            g_Game.vblankClearScreen = true;
            characterSelect.finished = false;
            characterSelect.snapEnd = false;
            randomRotations = 0;
            characterSelect.selection--;
        }
        else if (characterSelect.selection == 0)
        {
            Pcm::Play(Sounds.Core[CancelSnd], PlayMode::Volatile, 6);
            g_Game.vblankClearScreen = true;
            SRL::VDP2::NBG2::ScrollDisable();
            transitionState(GAME_STATE_TITLE_SCREEN);
        }
    }
    
    int left_char_id = characterSelect.spr_id - 1;
    if (left_char_id < CHARACTER_MACCHI)
        left_char_id = CHARACTER_NONE;
    
    int right_char_id = characterSelect.spr_id + 1;
    if (right_char_id > CHARACTER_NONE)
        right_char_id = CHARACTER_MACCHI;
    
    if (gamepad.IsHeld(Digital::Button::Left) && !characterSelect.finished)
    {
        if (characterAvailable[left_char_id])
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
        if (characterAvailable[right_char_id])
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
    else if (
              // gamepad.WasPressed(Digital::Button::START) || 
              gamepad.WasPressed(Digital::Button::A) || 
              gamepad.WasPressed(Digital::Button::C))
    {
        if (!characterSelect.finished)
        {
            Pcm::Play(Sounds.Name[LoadOkSnd], PlayMode::Volatile);
            characterSelect.selection++;
        }

        if (characterSelect.selection == CONFIRM_PRESSES)
        {
            characterSelect.finished = true;
        }
    }
    else if (gamepad.WasPressed(Digital::Button::START) && !characterSelect.end)
    {        
        if (characterSelect.finished && characterSelect.isAngleSnapped)
        {
            Pcm::Play(Sounds.Name[NameBrkSnd], PlayMode::Volatile);
            characterSelect.end = true;
            press_start = false;
            SRL::Debug::Print(19, 12, "     ");
            SRL::Debug::Print(20, 13, "     ");
            return;
        }
    }
    else
    {
        characterSelect.pressedLeft = false;
        characterSelect.pressedRight = false;
    }
}

void characterSelectUpdate(void)
{
    if (characterSelect.start)
    {
        SRL::VDP2::NBG2::ScrollEnable(); // don't need to call this every frame..
    }
    if (characterSelect.timer > 0 && g_Game.frame % 60 == 0 && characterSelect.start && !characterSelect.end) // modulus
    {
        characterSelect.timer--;
    }
    
    if (characterSelect.start)
    {
        // make an inline sub for this
        convertNumberToDigits(characterSelect.timer);
        set_spr_position(&font, 0, -170, 50);
        set_spr_scale(&font, 1.0, 1.0);
        font.id = font.anim[0].asset + tens;
        font.zmode = _ZmRC;
        my_sprite_draw(&font);
        font.id = font.anim[0].asset + ones;
        font.zmode = _ZmLC;
        my_sprite_draw(&font);
    }

    if (characterSelect.end && characterSelect.xRadius > CHARACTER_END_RADIUS)
    {
        characterSelect.xRadius -= Fxp(3);
        characterSelect.yRadius += Fxp(2);
        characterSelect.angle += 4;
        // SRL::Debug::Print(2, 10, "Rad:X=%3d", characterSelect.xRadius.As<int32_t>());
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

    if(characterSelect.timer == 0 || characterSelect.xRadius <= CHARACTER_END_RADIUS)
    {
        // this is broken for "random" characters?
        // leave as-is - "random" is playable as a secret character if you let the selection time out
        characterSelect.end = true;
        characterSelect.finished = true;
        player->character.selected = true;
        player->_portrait->id = player->_portrait->anim[0].asset + player->character.choice;
        assignCharacterSprite(player);
        SRL::Debug::PrintClearScreen();
        SRL::VDP2::NBG2::ScrollDisable();
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
            SRL::Debug::PrintClearScreen();
            newAngle = selectRandomCharacter();
            characterSelect.isAngleSnapped = false;
            characterSelect.snapEnd = true;
        }
        snap_to_random_character(newAngle);

        if (!characterSelect.end && characterSelect.isAngleSnapped)
        {
            if (press_start) {                
                SRL::Debug::Print(19, 12, "Press");
                SRL::Debug::Print(20, 13, "Start");
            }
            else {                
                SRL::Debug::Print(19, 12, "     ");
                SRL::Debug::Print(20, 13, "     ");
            }  
                  
            if (g_Game.frame % 16 == 0) { // modulus
                press_start = !press_start;
            }
        }
    }

        
    if (characterSelect.isAngleSnapped && characterSelect.start) // take this out of the characterSelectPositionUpdate loop
    {
        if (!g_GameOptions.debug_display && !characterSelect.pressedLeft && !characterSelect.pressedRight)
        {
            characterNameDraw(fullCharacterNames[player->character.choice]);
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
        characterSelectTitleDraw();
        
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
    
    lock.pos.x = paw[spr_id].pos.x;
    lock.pos.y = paw[spr_id].pos.y;
    
    if (angle > 262 && angle < 278)
    {
        paw[spr_id].scl.x = Fxp(3);
        if (!characterSelect.end) {
            characterSelect.spr_id = spr_id;
            player->character.choice = spr_id;
            assignPlayerStats(player);
        }
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
    
    lock.scl.x = paw[spr_id].scl.x;
    lock.scl.y = paw[spr_id].scl.y;
    
    if (characterSelect.end && characterSelect.xRadius > CHARACTER_END_RADIUS) {
        paw[spr_id].mesh = MESHoff;
    }
    else if (paw[spr_id].scl.x < 1.5) {
        paw[spr_id].mesh = MESHon;
    }
    else {
        paw[spr_id].mesh = MESHoff;
    }
    
    lock.mesh = paw[spr_id].mesh;
    
    paw[spr_id].zmode = _ZmCC;
    
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
    
    lock.pos.z = paw[spr_id].pos.z;

    paw[spr_id].flip = sprNoflip;
    my_sprite_draw(&paw[spr_id]);
    
    if (!characterAvailable[spr_id] && spr_id != CHARACTER_NONE && !characterSelect.end)
    {
        my_sprite_draw(&lock);
    }
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