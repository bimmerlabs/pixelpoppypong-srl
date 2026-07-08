#pragma once
#include "../dialog.hpp"

// NONE (random)
namespace Dialog
{
    inline void InitNoneDialog()
    {
        quotes[CHARACTER_NONE]
              [CHARACTER_MACCHI] =
        {
            "\nBEEP.",
            "\n...I'm not dignifying that with a response.",
            "...Was that a beep of victory? I can't tell.",
            "BZZT.",
            "BOOP.",
            "BEEP.",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_JELLY] =
        {
            "\nBEEP BOOP.",
            "\nHELLO?? ARE YOU TRYING TO TALK TO ME??",
            "It beeped when I lost. I think it was laughing?",   // lose: Jelly, convinced they bonded
            "BZZT.",                                              // win
            "BOOP.",
            "BEEP.",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_PENNY] =
        {
            "\nBEEP.",
            "\n...How peculiar.",
            "It beeped at the crown. I think it was bowing?",    // lose: Penny choosing to believe this
            "BZZT.",                                              // win
            "BOOP.",
            "BEEP.",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_POTTER] =
        {
            "\nBEEP BOOP.",
            "\nA mechanical familiar!! Fascinating!!",
            "It countered my spell with a boop. Dark magic.",    // lose: Potter, genuinely concerned
            "BZZT.",                                              // win
            "BOOP.",
            "BEEP.",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_SPARTA] =
        {
            "BEEP BOOP.",
            "ROBOT!! SCIENCE!! WOOP!!",
            "It wooped back. I think. It sounded like a woop?",  // lose: Sparta, delighted
            "BZZT.",                                              // win
            "BOOP.",
            "BEEP.",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_POPPY] =
        {
            "\nBEEP.",
            "\nUm... hehe? Hi?",
            "It beeped very softly when it won. Almost sweet.",  // lose: Poppy, somehow charmed
            "BZZT.",                                              // win
            "BOOP.",
            "BEEP.",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_TJ] =
        {
            "\nBEEP BOOP.",
            "\n...You don't talk much. I respect that.",
            "Lost to the beeping thing. Tch. It's got moves.",   // lose: TJ, grudging respect
            "BZZT.",                                              // win
            "BOOP.",
            "BEEP.",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_GEORGE] =
        {
            "\nBEEP BOOP.",
            "\nOH!! BEEP BOOP!! Wait, what does that mean?!",
            "It booped and I lost. Is boop a move?! OH!!",       // lose: George, fascinated
            "BOOP BEEP BOOP!.",                                              // win
            "BOOP.",
            "BEEP.",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_WUPPY] =
        {
            "\nBEEP BOOP.",
            "\nHI!! ARE YOU A CAT?! YOU SMELL LIKE A CAT!!",
            "IT WON AND THEN IT BEEPED AT ME. I THINK WE'RE FRIENDS!!", // lose: Wuppy, certain of this
            "BZZT... BEEP BOOP!!",                                              // win
            "BOOP.",
            "BEEP.",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_WALRUS] =
        {
            "\nBEEP.",
            "\nAren't you an unusual caddie?",
            "Ouch! Right down the middle!",                                        // lose: Craig, unfazed as always
            "BZZT.",                                              // win
            "BOOP.",
            "BEEP.",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_GARF] =
        {
            "\nBEEP BOOP.",
            "\n...what?  Why are you bothering me?",
            "It said something at the end. Almost sounded like Lasagna!", // lose: Garfield, the only one who noticed
            "BZZT.",                                              // win
            "BOOP.",
            "BEEP.",
        };
    }
}
