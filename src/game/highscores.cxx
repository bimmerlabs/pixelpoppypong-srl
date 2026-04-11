#include "../main.h"
#include "highscores.h"
#include "gameplay.h"
#include "name_entry.h"
#include "player_setup.h"
#include "../objects/characters.h"
#include "../core/screen_transition.h"
#include "../core/sprites.h"
#include "../vdp2/nbg1.h"

using namespace SRL::Input;

static uint32_t highScoreTimer = 0;

static uint8_t scoreEntries = 0;
static uint8_t drawnChars[SCORE_ENTRIES] = {};

HighScoreEntry highScores[SCORE_ENTRIES] = {};

const char *difficulty[] = {
    "Easy",
    "Medium",
    "Hard"
};
void highScore_init(void) {
    highScores[0] = (HighScoreEntry){10000000, "CDS",  0, 1}; // could put an actual score here
    highScores[1] = (HighScoreEntry){5000000,  "GBA", 10, 2};
    highScores[2] = (HighScoreEntry){4500000,  "SES",  8, 1};
    highScores[3] = (HighScoreEntry){4000000,  "OCS",  4, 0};
    highScores[4] = (HighScoreEntry){3500000,  "WUP",  0, 0};
    highScores[5] = (HighScoreEntry){3000000,  "FOO",  7, 1};
    highScores[6] = (HighScoreEntry){2500000,  "CRS",  9, 2};
    highScores[7] = (HighScoreEntry){2000000,  "BAR",  1, 1};
    highScores[8] = (HighScoreEntry){1500000,  "PPP",  5, 1};
    highScores[9] = (HighScoreEntry){1000000,  "DAD",  3, 0};
}

void init_scores(void)
{
    if (g_Assets.GameplayAssetsLoaded) {
        unloadGameAssets();
    }
    if (!g_Assets.characterAssetsLoaded) {
        loadCharacterAssets();
    }
    if (!g_Assets.NameEntryAssetsLoaded)
    {
        loadNameEntryAssets();
    }
    
    init_nbg2_img();
    
    highScoreTimer = 0;
    scoreEntries = 0;
                for (int i = 0; i < SCORE_ENTRIES; i++) {
        drawnChars[i] = 0;
    }        
        for (int i = 0; i < CHARACTER_MAX; i++) {
        set_spr_scale(&paw[i], 1, 1);
        paw[i].flip = sprNoflip;
        paw[i].id = paw[i].anim[0].asset;
        paw[i].mesh = MESHoff;
    }

    sortHighScores(highScores);

    SRL::VDP2::NBG0::SetPriority(SRL::VDP2::Priority::Layer4);
    SRL::VDP2::NBG2::ScrollEnable();  
    
    g_Audio.masterVolume = MAX_VOLUME;
    reset_audio(g_Audio.masterVolume);
    playCDTrack(MATCH_TRACK, false);

    g_Transition.fade_in = true;
    g_Transition.all_in = true;
}
bool draw_header_text = true;

void display_scores(void)
{
    int text_x = 5;
    int text_y = 4;
    
    int paw_x = -260;
    int paw_y = -136;
    
    highScoreTimer++;

    highScoreTitleDraw();
    
    text_y += 2;

    for (int i = 0; i < scoreEntries; i++) {
        
                int xOffset = drawnChars[i] * 16;
        set_spr_position(&paw[highScores[i].character], paw_x + xOffset, paw_y, 95);
        my_sprite_draw(&paw[highScores[i].character]);
        
        SRL::Debug::Print(text_x, text_y, "%2d. %s - %09d - %s", i + 1, highScores[i].initials, highScores[i].score, difficulty[highScores[i].difficulty]);
        SRL::Debug::Print(text_x + drawnChars[i], text_y, "                            ");
                if (drawnChars[i] < 31)
            drawnChars[i]++;
        
        text_y += 2;
        paw_y += 32;
    }

    update_bg_position();
        if (highScoreTimer == SCORE_EXIT_TIME) {
        if (g_Game.lastState == GAME_STATE_NAME_ENTRY) {
            exitHighScoresHelper();
            transitionState(GAME_STATE_CREDITS);
        }
        else {
            exitHighScoresHelper();
            transitionState(GAME_STATE_UNINITIALIZED);
        }
    }    
        // play a sound?
    if (g_Game.frame % 40 == 0) { // modulus
        if (scoreEntries < SCORE_ENTRIES)
            scoreEntries++;
    }
}

constexpr Angle backgroundAngleAdder = Angle(0.0027777777777778);static Angle backgroundAngle = Angle();

void update_bg_position(void) {
    if (attrNbg1.x_scroll > Fxp(0)) {
        attrNbg1.x_pos += attrNbg1.x_scroll;
        if (attrNbg1.x_pos > Fxp(512.0))
            attrNbg1.x_pos = Fxp(0);
    }
    slScrPosNbg1(attrNbg1.x_pos.RawValue(), attrNbg1.y_pos.RawValue());
}

void score_input(void)	{
    PPLAYER player = &g_Players[0];
    
    check_ui_inputs();    

    if (!player->input->isSelected)
    {
        return;
    }

    Digital gamepad(player->input->id);
    
    if (gamepad.IsHeld(Digital::Button::START) && g_Game.lastState == GAME_STATE_NAME_ENTRY) {
        exitHighScoresHelper();
        transitionState(GAME_STATE_CREDITS);
    }
    else if (gamepad.IsHeld(Digital::Button::START) && g_Game.lastState != GAME_STATE_NAME_ENTRY) {
        exitHighScoresHelper();
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

void addHighScore(uint32_t newScore, const char *initials, uint8_t character) {
    // Check if the new score qualifies
    if (newScore <= highScores[SCORE_ENTRIES - 1].score) {
        return;  // Score is too low, ignore
    }
    // Insert at the last position
    highScores[SCORE_ENTRIES - 1].score = newScore;
    highScores[SCORE_ENTRIES - 1].character = character;
    highScores[SCORE_ENTRIES - 1].difficulty = g_Game.gameDifficulty;
    
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
