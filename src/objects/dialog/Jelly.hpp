#pragma once
#include "../dialog.hpp"

// JELLY BEAN
namespace Dialog
{
    inline void InitJellyDialog()
    {
        quotes[CHARACTER_JELLY]
              [CHARACTER_MACCHI] =
        {
            "So, I was saying about my sqeaky toy - wait, are we starting?",
            "\nWe started thirty seconds ago.",
            "That was actually smooth.\n\nWell done!",
            "Not bad, coffee cat.\n\nNot bad.",
            "Have you seen my mug?",
            "I'm the best!",
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_PENNY] =
        {
            "Oh hey your highness!\nLove the crown, very shiny-",
            "\nBegin. And do stop talking.",
            "The crown wobbled! I saw it!",                       // win: Penny reacts to losing
            "Silence would suit you better.",                           // lose: Penny taunts you
            "Stop. Talking.",
            "One more hello and it's off with your head!",
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_POTTER] =
        {
            "\nOkay so I have a theory about the wand-",
            "\nCan it wait until after the match?",
            "The wand was just a stick after all...",              // win: Potter reacts to losing
            "Magic wins,\no theory required.",                   // lose: Potter taunts you
            "Silencio! ...Still not working.",
            "By Merlin's whiskers, can you hush?",
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_SPARTA] =
        {
            "\nHey so what IS a lamp, like philosophically-",
            "\nLamp is my friend, I love it!",
            "Talk to my fluffy tail!",                      // lose: Sparta taunts you
            "Lamp didn't help...\n\nlamp never helps...",               // win: Sparta reacts to losing
            "LAMP!",
            "WOOP!",
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_POPPY] =
        {
            "\nPoppy!! Okay, so I have been dying to ask you-",
            "\nHehe! Maybe later, let's play now!",
            "Hehe! Fluffy cat wins!!",
            "Aww, I feel bad.\n\nOnly a little though.",
            "You're so loud!! Hehe!!",
            "That was really close!! Hehe!!",
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_TJ] =
        {
            "T.J.!! Bro!\nOkay so I heard about your shoelace-",
            "\n\n...don't.",
            "So anyway- maybe that dog has your shoelace?",                     // win: TJ reacts to losing
            "Quiet wins.\n\nRemember that.",                        // lose: TJ taunts you
            "Shhhh!",
            "C'mon!",
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_GEORGE] =
        {
            "\nGEORGE!!\nOkay so I was thinking-",
            "\nOh!! What were you thinking?! Tell me!!",
            "Chasing your tail again instead of the ball...", // win: George reacts to losing
            "I thought the ball was my missing bell!",
            "Was that right?!",                     // lose: George taunts you
            "I am distracted by your fluff!",
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_WUPPY] =
        {
            "Okay Wuppy, so funny story about my squeaky toy-",
            "I SWEAR i DIDN'T STEAL IT!\nI JUST WANTED TO SAY HELLO!!",
            "The squeaky toy is safe!\nBut eww, slobber..",            // win: Wuppy reacts to losing
            "I ACCIDENTALLY MIGHT HAVE ATE YOUR TOY!!\nI'M SO SORRY!!",      // lose: Wuppy taunts you
            "YAY!! AGAIN!!",
            "I SWEAR IT WASN'T ME!!",
        };
        
        quotes[CHARACTER_JELLY]
              [CHARACTER_WALRUS] =
        {
            "So are you actually playing golf or is that a bit-",   // player1
            "The ball here sure looks like a golf ball to me.",                         // player2
            "Do you ever say anything else?",                    // taunt2
            "See? Just like golf.",                                        // win: Craig reacts to losing
            "Great shot.",                                        // lose: Craig taunts you
            "Right down the middle!",                                        // taunt1

        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_GARF] =
        {
            "Garfield!!\nOkay so I have been DYING to ask you-", // player1
            "\nNo.",                                               // player2
            "He barely moved and still won. I have questions.",  // win: Garfield reacts to losing
            "Finally, I can get some peace and quiet.",                 // lose: Garfield taunts you
            "Yawn.  I'd rather be napping",        // taunt1
            "Orange cat to Orange cat:\ngot any lasagna?",     // taunt2
        };

        quotes[CHARACTER_JELLY]
              [CHARACTER_NONE] =
        {
            "Oh hey! So I was thinking-\nUh, what?? Hello??",        // player1
            "\nBEEP BOOP.",                                        // player2
            "Are you even listening?",                           // taunt1
            "BEEP (help me) BOOP.",
            "BZZT.",                                             // win: CPU reacts to losing
            "BEEP BOOP.",                                        // lose: CPU taunts you
        };
    }
}
