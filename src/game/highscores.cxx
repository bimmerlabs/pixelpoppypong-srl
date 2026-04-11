// #include <jo/jo.h>
#include "../main.h"
#include "highscores.h"
#include "gameplay.h"
#include "name_entry.h"
#include "player_setup.h"
#include "../core/screen_transition.h"
#include "../core/sprites.h"
// #include "../core/backup.h"
#include "../vdp2/nbg1.h"

using namespace SRL::Input;

static uint32_t highScoreTimer = 0;

HighScoreEntry highScores[SCORE_ENTRIES] = {};

void highScore_init(void) {
    highScores[0] = (HighScoreEntry){10000000, "CDS"}; // could put an actual score here
    highScores[1] = (HighScoreEntry){5000000, "GBA"};
    highScores[2] = (HighScoreEntry){4500000, "SES"};
    highScores[3] = (HighScoreEntry){4000000, "OCS"};
    highScores[4] = (HighScoreEntry){3500000, "WUP"};
    highScores[5] = (HighScoreEntry){3000000, "FOO"};
    highScores[6] = (HighScoreEntry){2500000, "CRS"};
    highScores[7] = (HighScoreEntry){2000000, "BAR"};
    highScores[8] = (HighScoreEntry){1500000, "PPP"};
    highScores[9] = (HighScoreEntry){1000000, "DAD"};
}

void init_scores(void)
{
    if (g_Game.lastState == GAME_STATE_NAME_ENTRY) {
        // unloadNameEntryAssets();
    }
    g_Transition.fade_in = true;
    g_Transition.all_in = true;
    
    // #if ENABLE_DEBUG_MODE == 1
    // if (g_GameOptions.debug_mode) { // only needed if manually changing states
        // reset_sprites();
        // do_update_All = true;
        // updateAllColors();
        // updateAllPalette();
        // set_spr_scale(&pixel_poppy, 6, 6);
        // pixel_poppy.rot.z = Angle();
        // set_spr_position(&pixel_poppy, 0, 0, 100);
        // sprite_frame_reset(&pixel_poppy);
    // }
    // #endif
    
    highScoreTimer = 0;
    
    if (g_GameOptions.mesh_display) {
        menu_bg2.mesh = MESHon;
    }
    else {
        menu_bg2.mesh = MESHoff;
    }
    menu_bg2.id = menu_bg2.anim[0].asset + 4;
    menu_bg2.zmode = _ZmCC;
    set_spr_position(&menu_bg2, 0, 0, 95);
    set_spr_scale(&menu_bg2, 200, 480);
    
    sortHighScores(highScores);

    g_Audio.masterVolume = MAX_VOLUME;
    reset_audio(g_Audio.masterVolume);
    playCDTrack(GOAL1_TRACK, false);
}
 bool draw_header_text = true;

void display_scores(void)
{
    int text_x = 12;
    int text_y = 4;
    highScoreTimer++;
    
    if (g_Game.frame % 8 == 0) { // modulus
        draw_header_text = !draw_header_text;
    }
    if (draw_header_text) {
        SRL::Debug::Print(text_x+5, text_y, "High Scores");
    }
    else {
        SRL::Debug::Print(text_x+5, text_y, "           ");
    }
    text_y += 2;
    // TODO: increment score_entries after every line is printed, animating a character portrait/ball, etc for each line
    for (int i = 0; i < SCORE_ENTRIES; i++) {
        SRL::Debug::Print(text_x, text_y, "%2d. %s - %09d", i + 1, highScores[i].initials, highScores[i].score);
        text_y += 2;
    }
    my_sprite_draw(&menu_bg2);
    update_bg_position();    if (highScoreTimer == SCORE_DISPLAY_TIME) {
        if (g_Game.lastState == GAME_STATE_NAME_ENTRY) {
            g_Game.lastState = GAME_STATE_HIGHSCORES;
            SRL::Debug::PrintClearScreen();
            transitionState(GAME_STATE_CREDITS);
        }
        else {
            g_Game.lastState = GAME_STATE_HIGHSCORES;
            SRL::Debug::PrintClearScreen();
            transitionState(GAME_STATE_UNINITIALIZED);
        }
    }
}

constexpr Angle backgroundAngleAdder = Angle(0.0027777777777778);static Angle backgroundAngle = Angle();

void update_bg_position(void) {
    if (g_Game.frame % 2 == 0) {
        backgroundAngle -= backgroundAngleAdder;
        // if (backgroundAngle == 0)
            // backgroundAngle = 360;
        attrNbg1.x_pos = Fxp_127 + (SRL::Math::Trigonometry::Cos(backgroundAngle) * Fxp_127);
        slScrPosNbg1(attrNbg1.x_pos.RawValue(), attrNbg1.y_pos.RawValue());
    }
}

void score_input(void)	{
    PPLAYER player = &g_Players[0];
    
    if (!player->input->isSelected)
    {
        check_ui_inputs();
    }

    Digital gamepad(player->input->id);
    
    if (gamepad.IsHeld(Digital::Button::START) && g_Game.lastState == GAME_STATE_NAME_ENTRY) {
        g_Game.lastState = GAME_STATE_HIGHSCORES;
        SRL::Debug::PrintClearScreen();
        transitionState(GAME_STATE_CREDITS);
    }
    else if (gamepad.IsHeld(Digital::Button::START) && g_Game.lastState != GAME_STATE_NAME_ENTRY) {
        g_Game.lastState = GAME_STATE_HIGHSCORES;
        SRL::Debug::PrintClearScreen();
        transitionState(GAME_STATE_UNINITIALIZED);
    }
}

// Sorting function (Descending order)
void sortHighScores(HighScoreEntry scores[]) {
    for (int i = 0; i < SCORE_ENTRIES - 1; i++) {
        for (int j = i + 1; j < SCORE_ENTRIES; j++) {
            if (scores[j].score > scores[i].score) {
                HighScoreEntry temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }
}

void addHighScore(uint32_t newScore, const char *initials) {
    // Check if the new score qualifies
    if (newScore <= highScores[SCORE_ENTRIES - 1].score) {
        return;  // Score is too low, ignore
    }
    // Insert at the last position
    highScores[SCORE_ENTRIES - 1].score = newScore;
    
    for (int i = 0; i <= MAX_INITIAL; ++i) {
        highScores[SCORE_ENTRIES - 1].initials[i] = initials[i];
    }

    // Sort the list
    sortHighScores(highScores);
}

void calculateScore(Sprite *ball, uint8_t playerID) {
    Fxp BallVelX = ball->vel.x.Abs();
    Fxp BallVelY = ball->vel.y.Abs();
    uint32_t points = (BallVelX.As<uint32_t>() * 50) 
                         + (BallVelY.As<uint32_t>() * 500) 
                         + (ABS(ball->vel.z.As<int32_t>()) * 1000);
    g_Players[playerID].score.points += points * touchedBy[playerID].touchCount;
    ballTtouchTimer = 0;
}

void updateScore(Sprite *ball, int playerID) {
    PPLAYER player = &g_Players[playerID];
    
    if (player->isDead) {
        return;
    }
    // Assign score if a valid player touched it
    if (lastTouchedBy != -1 && playerID != lastTouchedBy) {
        calculateScore(ball, lastTouchedBy);        
    }
    else {
        for (uint8_t i = 0; i < TOUCHEDBY_BUFFER; i++) {
            int8_t id = previouslyTouchedBy[i];
            if (id == -1) continue;
            PPLAYER opponent = &g_Players[id];
            if (opponent->isDead) continue;
            if (!opponent->isActivated) continue;
            if (id == playerID) continue;
            if (player->onLeftSide == opponent->onLeftSide) continue;
            calculateScore(ball, id);
            break;
        }
    }
    updatePlayerLives(playerID);
    g_Game.isGoalScored = true; // still set to true - no score assigned to a player, but somebody loses a life
    playCDTrack(g_Audio.currentTrack, false);
    nextcurrentTrack();
}
