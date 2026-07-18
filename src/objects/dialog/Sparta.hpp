#pragma once
#include "../dialog.hpp"

// DR. SPARTA
namespace Dialog
{
    inline void InitSpartaDialog()
    {
        quotes[CHARACTER_SPARTA]
              [CHARACTER_MACCHI] =
        {
            "\nI am very smart! I love lamp! Ready?",
            "\nYou are... something.",
            "Yay!  Lamp saved the day!",                         // win: Macchi reacts to losing
            "Exactly as smooth as I expected.",
            "Did you just yell science at the ball?",
            "You ran into your own paddle.",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_JELLY] =
        {
            "\nLet's go!!\nI LOVE LAMP!!\n",
            "\nWhat's lamp?\nYou must tell me about it sometime -",
            "WOOP!! THE DR. WINS!!",                       // lose: Jelly taunts you
            "I asked about the lamp. He just said lamp.\nHah! Classic.",
            "We should talk about the lamp thing sometime.",
            "I'm not losing to to the lamp guy!",              // win: Jelly reacts to losing
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_PENNY] =
        {
            "\nHELLO YOUR MAJESTY!!\nI love lamp!!",
            "\nYou're going to be a problem..",
            "LAMP DEFEATS ROYALTY!!\nWOOP WOOP!!",                 // lose: Penny taunts you
            "I have no words. Just disappointment.",              // win: Penny reacts to losing
            "Stop running in circles.",
            "You just scored on your own goal.",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_POTTER] =
        {
            "\nLAMP VS MAGIC!! WOOP WOOP!!",
            "Is that a magic lamp?\nIt doesn't look like any I have seen...",
            "SCIENCE!! Well actually lamp. WOOP!!",          // lose: Potter taunts you
            "We are both disasters.\nAt least I have a wand though.",
            "I am NOT losing to... lamp magic.",             // win: Potter reacts to losing
            "Focus your energy!",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_POPPY] =
        {
            "\nWOOP WOOP HEY POPPY!!\nLAMP SAYS HI!!",
            "\nHehe! Hi lamp, I guess!",
            "LAMP WINS!! WOOP!!",                                  // lose: Poppy taunts you
            "You're really fun, but also kinda chaotic.",         // win: Poppy reacts to losing
            "Is he okay?  I'm a little worred..",
            "...Hehe!!",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_TJ] =
        {
            "SIX TOES!! NOW THAT'S SCIENCE!!\nWOOP!!",
            "\nDon't touch my #$@&%*! paws.",
            "SPARTA WINS!! LAMP!! WOOP!!",                        // lose: TJ taunts you
            "Tch. Talked to the lamp guy. This never leaves the alley.", // win: TJ reacts to losing
            "Get away from my paws.",
            "Hey have you seen Ea- oh, nevermind.",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_GEORGE] =
        {
            "\nWOOP WOOP!! LAMP VS CURIOSITY!!",
            "\nOh!! What's a lamp?! Can I see it?!",
            "LAMP WINS! WOOP!",                                  // lose: George taunts you
            "I got distracted by the woop sounds.\nVery interesting sounds.", // win: George reacts to losing
            "Can I touch the lamp now?",
            "Oh!! His tail is so long!!",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_WUPPY] =
        {
            "\nWOOP WOOP DOGGY!! LAMP!!",
            "\nHI!! I LOVE YOU TOO!!\nWANNA PLAY?!",
            "LAMP WINS WOOP!!",                                   // lose: Wuppy taunts you
            "THAT WAS SO FUN!!\nLET'S DO IT AGAIN??",                   // win: Wuppy reacts to losing
            "I GOT THE BALL!!",
            "I WANNA SEE LAMP!!  CAN I??",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_WALRUS] =
        {
            "\nWOOP WOOP GOLF MAN!! LAMP!!",                        // player1
            "\n...Great shot, buddy.",                              // player2
            "LAMP BEATS GOLF!! WOOP!!",                           // lose: Craig taunts you
            "Found one in the rough.",                                        // win: Craig reacts to losing
            "I'll show you my best shot.",                                        // taunt1
            "Nice energy kid.",                                  // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_GARF] =
        {
            "\nWOOP WOOP GARFIELD!! LAMP!!",                        // player1
            "\n...I don't even have words.",                        // player2
            "LAMP BEATS LASAGNA CAT!! WOOP!!",                    // lose: Garfield taunts you
            "I hate lamp.\nI hate Mondays.\nI hate everything.",   // win: Garfield reacts to losing
            "Not the sharpest tool in the shed...",     // taunt2
            "You practically scored on yourself.",                                              // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_NONE] =
        {
            "\nWOOP WOOP ROBOT!! LAMP!!",                           // player1
            "\nBEEP BOOP.",                                         // player2
            "LAMP BEATS ROBOT!! SCIENCE!! WOOP!!",               // lose: CPU taunts you
            "BZZT.",                                              // win: CPU reacts to losing
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };
    }
}
