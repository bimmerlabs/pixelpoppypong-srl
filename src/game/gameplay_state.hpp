#pragma once
#include <srl.hpp>
#include "../main.h"
#include "../core/backup.h"
#include "gameplay.h"
#include "storymode.h"
#include "highscores.h"

using namespace SRL::Types;
using namespace SRL::Math::Types;


namespace Gameplay
{
    // one of these is fucking up the music
    // zzz
    static const int32_t END_DELAY = 5 * 60;
    static const int32_t RESULT_DELAY = 5 * 60;
    
    static const int32_t BALL_TOUCH_TIMEOUT = 5 * 60;
    static const int32_t GAME_END_DELAY_TIMEOUT = 5 * 60;
    static const int32_t LIFE_COUNT_DELAY_TIMEOUT = 2 * 60;
    static const int32_t NEXT_BATTLE_DELAY_TIMEOUT = 1 * 60;
    static const int32_t WIN_GAME_DELAY_TIMEOUT = 1.5 * 60;
    static const int32_t ROUND_OVER_DELAY_TIMEOUT = 1 * 60;
    static const int32_t GAME_OVER_DELAY_TIMEOUT = 4 * 60;
    static const int32_t GAME_OVER_SOUND_TIMEOUT = 1 * 30;
    
    
    // need to add these back and remove round stuff from the g_Game struct
    typedef enum
    {
        ROUND_STATE_CHARACTER_SELECT, // 0
        ROUND_STATE_PLAYING, // 1
        ROUND_STATE_NEXTROUND, // 2
        ROUND_STATE_SHOWMESSAGE, // 3
        ROUND_STATE_SHOWRESULT, // 4
        ROUND_STATE_ENDING
    } RoundState;

    typedef struct
    {
        int32_t winner;
        int32_t endDelayTimer;
        int32_t GameOverTimer;
        bool timeOver;
        bool spriteAssigned;
        bool gameOverSndPlayed;
        RoundState roundState;
        
    } GameStateData;
    
    inline GameStateData g_GameState = {};
        
    static inline void InitGameState(void)
    {
        g_GameState.winner = -2;
        g_GameState.endDelayTimer = END_DELAY;
        g_GameState.timeOver = false;
        g_GameState.roundState = ROUND_STATE_PLAYING;
        g_GameState.GameOverTimer = GAME_OVER_DELAY_TIMEOUT;  // sets the time after the round is over
        g_GameState.gameOverSndPlayed = false;
    }
    
    static inline void UpdateCharacterSelect()
    {
        storySelectUpdate();
    }

    static inline void EnterCharacterSelect()
    {
        Gameplay::g_GameState.spriteAssigned = false;
        
        if (Gameplay::g_GameState.winner == -1 || Gameplay::g_GameState.timeOver)
        {
            SRL::VDP2::NBG2::ScrollDisable();
            initContinue();
            initNextRound();
        }
        else if (Gameplay::g_GameState.winner == 0 && g_Game.countofRounds > 0)
        {
            SRL::VDP2::NBG2::ScrollDisable();
            initNextRound();
        }
        
        // if (g_Game.countofRounds > 0) // I think this is the source of my bug
        // {
            // if (Gameplay::g_GameState.winner == -1)
            // {
                // initContinue();
            // }
            // initNextRound();
        // }
        
        g_Transition.fade_in = true;
        g_Transition.all_in = true;
        
        playCDTrack(BEGIN_GAME_TRACK, false);
    }

    static inline void EnterEndingState()
    {
        SRL::VDP2::NBG2::ScrollDisable();
        SRL::Debug::PrintClearScreen();

        g_Game.isActive = false;
        g_Game.isBallActive = false;
        g_Game.isRoundOver = true;
        g_Game.frame = 0;
        g_Gameplay.isGameOver = false;
        g_GameState.endDelayTimer = END_DELAY;
        
        if (g_GameState.timeOver)
        {
            SRL::Debug::Print(16, 14, "Outta Time!");
            initPixelPoppy();
            
            g_GameState.winner = -2;
            if (!g_Players[0].isDead && g_Game.gameMode == GAME_MODE_STORY)
            {
                g_GameState.winner = -1;
                g_Gameplay.GameTimer = 60;
                g_Players[0].score.continues--;
                g_Players[0].isDead = true;
            }
        }
        else
        {
            g_GameState.winner = determineWinner();
            
            // mark opponent as finished immediately when player wins
            if (g_Game.gameMode == GAME_MODE_STORY)
            {                
                uint8_t playerid   = g_Players[0].character.choice;
                uint8_t computerid = g_Players[1].character.choice;
                if (g_GameState.winner == 0)
                { // win
                    PrintWrapped(0, 0, 30, Dialog::quotes[playerid][computerid].win, Align::CenterBoth);
                    g_StoryProgress.finished[g_Players[1].character.choice] = true;
                }
                else
                { // lose
                    PrintWrapped(0, 0, 30, Dialog::quotes[playerid][computerid].lose, Align::CenterBoth);
                }
            }
            else
            {
                g_GameState.endDelayTimer = 0;
            }
        }
        if (g_GameOptions.mosaic_display)
        {
            g_Transition.mosaic_out = true;
        }
        g_Transition.story_fade_out = true;
        g_Transition.all_out = true;
        
        if (!g_Game.isBoss || allOpponentsBeaten())
            playCDTrack(MATCH_TRACK, false);
    }
    
    static inline void EnterBattleResult()
    {
        SRL::Debug::PrintClearScreen();
        g_GameState.endDelayTimer = RESULT_DELAY;

        // set nextState and draw initial messages...
    }
    
    static inline void EnterClassicResult()
    {
        SRL::Debug::PrintClearScreen();
        g_GameState.endDelayTimer = RESULT_DELAY;

        // set nextState and draw initial messages...
    }
    
    static inline void EnterStoryResult()
    {
        SRL::Debug::PrintClearScreen();
        g_GameState.endDelayTimer = RESULT_DELAY;

        // set nextState and draw initial messages...
    }
    
    static inline void EnterShowResult()
    {
        static void (*EnterResultByMode[])(void) =
        {
            // ORDER IS FIXED - must match GAME_MODE_STORY/BATTLE/CLASSIC defines in main.h
            // compiler cannot catch mismatches because those are #defines not an enum
            // if modes are added or reordered in main.h, this table must be updated manually
            EnterStoryResult,
            EnterBattleResult,
            EnterClassicResult
        };

        EnterResultByMode[g_Game.gameMode]();
    }
    
    static inline void EnterTransition()
    {
        g_Gameplay.isGameOver = true;
    }
    
    static inline void EnterPlaying()
    {
        g_GameState.timeOver = false;
        g_GameState.winner = -2;
        g_GameState.endDelayTimer = 0;
        SRL::VDP2::NBG2::ScrollEnable();
        if (g_GameOptions.mosaic_display)
        {
            g_Transition.mosaic_in = true;
        }
        g_Transition.fade_in = true;
        g_Transition.all_in = true;
    }

    static inline void SetRoundState(RoundState newState)
    {
        g_GameState.roundState = newState;
        
        SRL::Debug::PrintClearScreen(); // putting this here could eliminate from the following
        
        switch (newState)
        {
            case ROUND_STATE_ENDING:
                EnterEndingState();
                break;

            case ROUND_STATE_SHOWRESULT:
                EnterShowResult();
                break;
                
            case ROUND_STATE_PLAYING:
                EnterPlaying();
                break;
                
            case ROUND_STATE_CHARACTER_SELECT:
                EnterCharacterSelect();
                break;
                
            default:
                break;
        }
    }
    
    static inline void UpdatePlaying(void)
    {
        if (!g_Game.isPaused) {
            
            gameplay_timer();
            
            if (g_GameState.timeOver)
            {
                SetRoundState(ROUND_STATE_ENDING);
                return;
            }
            
            switch(g_Game.gameMode)
            {
                case GAME_MODE_BATTLE:
                    drawVsMode();
                    drawGameUI();
                    break;
                case GAME_MODE_CLASSIC:
                    drawClassicMode();
                    drawGameUI();
                    break;
                case GAME_MODE_STORY:
                    drawVsMode();
                    drawGameUI();
                    break;
                default:
                    break;
            }
        }
    }
    
    static inline void UpdateBattleResult(void)
    {
        g_GameState.endDelayTimer--;
        
        // CASE 1: Player wins 
        if (g_GameState.winner > -1)
        {            
            SRL::Debug::Print(17, 14, "Game Over!");
            if (g_GameState.endDelayTimer < WIN_GAME_DELAY_TIMEOUT)
            {
                SRL::Debug::Print(15, 16, "%s Wins!", classicCharacterNames[g_GameState.winner]);
                if (!g_GameState.gameOverSndPlayed)
                {
                    Pcm::Play(Sounds.Game[GmOverSnd]);
                    g_GameState.gameOverSndPlayed = true;
                }
            }
                
            g_Game.nextState = GAME_STATE_CREDITS;
            
            if (g_GameState.endDelayTimer <= 0)
                transitionState(g_Game.nextState);
        }

        // CASE 2: Player lost (or time over)
        else
        {
            if (g_Game.gameMode == GAME_MODE_STORY)
            {
                uint8_t playerid   = g_Players[0].character.choice;
                uint8_t computerid = g_Players[1].character.choice;
                SRL::Debug::Print(17, 12, "Game Over!");
                
                bool useTaunt2 = rnd.GetNumber(0, 1);
                const char* taunt = useTaunt2 ? Dialog::quotes[playerid][computerid].taunt2
                                               : Dialog::quotes[playerid][computerid].taunt1;
                PrintWrapped(0, 14, 20, taunt, Align::CenterX);
            }
            else
            {
                SRL::Debug::Print(17, 14, "Game Over!");
            }
            
            if (g_GameState.endDelayTimer < WIN_GAME_DELAY_TIMEOUT)
            {
                SRL::Debug::Print(18, 16, "You Lose");
                if (!g_GameState.gameOverSndPlayed)
                {
                    Pcm::Play(Sounds.Game[GmOverSnd]);
                    g_GameState.gameOverSndPlayed = true;
                }
            }

            g_Game.nextState = GAME_STATE_UNINITIALIZED;
            
            if (g_GameState.endDelayTimer <= 0)
                transitionState(g_Game.nextState);
        }
    }
        
    static inline void UpdateStoryResult()
    {
        // CASE 1: Player wins final round
        if (g_GameState.winner == 0 && allOpponentsBeaten())
        {
            SRL::Debug::Print(17, 10, "Game Over!");
            tallyScore();
            if (g_GameState.endDelayTimer < WIN_GAME_DELAY_TIMEOUT)
            {
                if (!g_GameState.gameOverSndPlayed)
                {
                    Pcm::Play(Sounds.Game[GmOverSnd]);
                    g_GameState.gameOverSndPlayed = true;
                }
                SRL::Debug::Print(17, 18, "You Win!!!");
            }

            if (g_GameState.endDelayTimer <= 0 && g_Game.frame == 239)
            {
                PPLAYER winner = &g_Players[g_GameState.winner];
    
                // don't continue if player's score is too low
                if (!checkHighScore(winner->score.total))
                {
                    transitionState(GAME_STATE_HIGHSCORES);
                    return;
                }
                else
                {
                    // unlocks and save...
                    transitionState(GAME_STATE_NAME_ENTRY);
                }
            }
        }
        // CASE 2: Lost or time over
        else if (g_GameState.winner == -1)
        {
            if (g_Players[0].score.continues >= 0)
            {
                SRL::Debug::Print(17, 14, "Try Again!");
                
                g_Players[0].isDead = false;
                
                if (g_Players[0].score.continues > 0)
                {
                    SRL::Debug::Print(12, 16, "Remaining Continues:");
                    draw_star_element(&star,
                        g_Players[0].score.continues,
                        Fxp(172), Fxp(24), Fxp(16));
                }
                else
                {
                    SRL::Debug::Print(16, 16, "Last Chance!");
                }

                g_GameState.endDelayTimer--;
                if (g_GameState.endDelayTimer <= 0)
                    SetRoundState(ROUND_STATE_CHARACTER_SELECT);
            }
            else
            {
                SRL::Debug::Print(17, 14, "Game Over!" );
                if (g_GameState.endDelayTimer < GAME_OVER_SOUND_TIMEOUT)
                {                    
                    if (!g_GameState.gameOverSndPlayed)
                    {
                        Pcm::Play(Sounds.Game[GmOverSnd]);
                        g_GameState.gameOverSndPlayed = true;
                    }
                }
                if (g_GameState.endDelayTimer < WIN_GAME_DELAY_TIMEOUT)
                {
                    SRL::Debug::Print(18, 16, "You Lose");
                }

                g_GameState.endDelayTimer--;
                if (g_GameState.endDelayTimer <= 0 && g_Game.frame == 239)
                    transitionState(GAME_STATE_UNINITIALIZED);
            }
        }
        // CASE 3: Won round, not final
        else
        {
            tallyScore();
            if (g_GameState.endDelayTimer < NEXT_BATTLE_DELAY_TIMEOUT)
                SRL::Debug::Print(15, 20, "Next Battle..");
            if (g_GameState.endDelayTimer <= 0 && g_Game.frame == 239)
            {
                SetRoundState(ROUND_STATE_CHARACTER_SELECT); 
            }
        }
    }
        
    static inline void UpdateEnding()
    {
        if (--g_GameState.endDelayTimer <= 0)
        {
            SetRoundState(ROUND_STATE_SHOWRESULT);
        }
    }
    
    static inline void UpdateShowResult()
    {
        // ORDER IS FIXED - must match GAME_MODE_STORY/BATTLE/CLASSIC defines in main.h
        // compiler cannot catch mismatches because those are #defines not an enum
        // if modes are added or reordered in main.h, this table must be updated manually
        static void (*UpdateResultByMode[])(void) =
        {
            UpdateStoryResult,
            UpdateBattleResult,
            UpdateBattleResult
        };
        
        UpdateResultByMode[g_Game.gameMode]();
    }
    
    static inline void GameUpdateState(void)
    {        
        switch (g_GameState.roundState)
        {
            case ROUND_STATE_PLAYING:
                UpdatePlaying();
                break;

            case ROUND_STATE_ENDING:
                UpdateEnding();
                break;

            case ROUND_STATE_SHOWRESULT:
                UpdateShowResult();
                break;
                
            case ROUND_STATE_CHARACTER_SELECT:
                UpdateCharacterSelect();
                break;
                
            default:
                break;
        }
    }
}