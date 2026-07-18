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
            "...Was that a beep of victory?\nI can't tell.",
            "BZZT.",
            "I think you may have had too much caffine!",
            "Maybe robots shouldn't have coffee?",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_JELLY] =
        {
            "\nBEEP BOOP.",
            "\nHELLO?? ARE YOU TRYING TO TALK TO ME??",
            "It beeped when I lost.\nI think it was laughing?",   // lose: Jelly, convinced they bonded
            "BOOP.",
            "Are you even listening?",                           // taunt1
            "I feel like we could really talk if you tried.",    // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_PENNY] =
        {
            "\nBEEP.",
            "\n...How peculiar.",
            "It beeped at the crown.\nI think it was bowing?",    // lose: Penny choosing to believe this
            "BEEP.",
            "Did it just beep at me?",                            // taunt1
            "I tire of your insolence!",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_POTTER] =
        {
            "\nBEEP BOOP.",
            "\nA mechanical familiar!! Fascinating!!",
            "It countered my spell with a boop.\nMust be dark magic!",    // lose: Potter, genuinely concerned
            "BZZT.",                                              // win
            "Is it casting something?",                           // taunt1
            "By Merlin's whiskers.",                                   // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_SPARTA] =
        {
            "\nBEEP BOOP.",
            "\nAre you some kind of robot??",
            "It made a noise.\nI think It sounded like a woop?",  // lose: Sparta, delighted
            "BOOP.",
            "Lamp beats robot!",
            "Are you a robot scientist?.",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_POPPY] =
        {
            "\nBEEP.",
            "\nUm... hehe? Hi?",
            "It beeped very softly when it won.\nAlmost sweet.",  // lose: Poppy, somehow charmed
            "BOOP. BOOP!!",
            "That was weird!! Hehe!!",                            // taunt1
            "Aww, can I boop you back?",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_TJ] =
        {
            "\nBEEP BOOP.",
            "\n...You don't talk much. I respect that.",
            "Lost to the #$@&%*! thing.\nTch. It's got moves.",   // lose: TJ, grudging respect
            "BZZT.",                                              // win
            "C'mon, stop beeping!",
            "Pfft, that's all you got?.",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_GEORGE] =
        {
            "\nBEEP BOOP.",
            "Oh!! BEEP BOOP!!\n\nWait, what does that mean?!",
            "BOOP BEEP BOOP!.",                                              // win
            "Oh!! I beat the beepy thing!!",      // lose: George, fascinated
            "Oh!! Shiny robot!!",                                 // taunt1
            "I think we could be friends!",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_WUPPY] =
        {
            "\nBEEP BOOP.",
            "\nHI!! ARE YOU A CAT?! YOU SMELL LIKE A CAT!!",
            "IT WON AND THEN IT BEEPED AT ME.\nI THINK WE'RE FRIENDS!!", // lose: Wuppy, certain of this
            "BZZT... BEEP BOOP!!",                                              // win
            "ARE YOU A CAT?? YOU SEEM LIKE A CAT!!", 
            "AT LEAST YOU'RE NOT MAD AT ME! ARE YOU!?.",
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_WALRUS] =
        {
            "\nBEEP.",
            "\nAren't you an unusual caddie?",
            "Ouch! Right down the middle!",                                        // lose: Craig, unfazed as always
            "BOOP.",
            "Have you even played golf before?",                  // taunt1
            "That made your shot just a little tougher.",           // taunt2
        };

        quotes[CHARACTER_NONE]
              [CHARACTER_GARF] =
        {
            "\nBEEP BOOP.",
            "\n...what?  Why are you bothering me?",
            "It said something at the end.\nAlmost sounded like Lasagna!", // lose: Garfield, the only one who noticed
            "BEEP.",
            "You're weird enough that I'm not even bored.",                                              // win
            "Well, now I am bored...",
        };
    }
}
