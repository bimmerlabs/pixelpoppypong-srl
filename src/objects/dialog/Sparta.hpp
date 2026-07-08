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
            "I am very smart! I love lamp! Ready?",
            "You are... something.",
            "Yay!  Lamp saved the day!",                         // win: Macchi reacts to losing
            "Exactly as smooth as I expected.",
            "Did you just yell science at the ball?",
            "You ran into your own paddle.",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_JELLY] =
        {
            "Let's go!! I LOVE LAMP!!",
            "What's lamp?  you should tell me about it sometime -",
            "WOOP!! THE DR. WINS!!",                       // lose: Jelly taunts you
            "HELLO?? I lost to the lamp guy??",              // win: Jelly reacts to losing
            "We should talk about the lamp thing sometime.",
            "I asked about the lamp. He just said lamp. Classic.",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_PENNY] =
        {
            "HELLO YOUR MAJESTY!! I love lamp!!",
            "...You're going to be a problem.",
            "LAMP DEFEATS ROYALTY!! WOOP WOOP!!",                 // lose: Penny taunts you
            "I have no words. Just disappointment.",              // win: Penny reacts to losing
            "Stop running in circles.",
            "You just hit your own side. Twice.",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_POTTER] =
        {
            "SCIENCE VS MAGIC!! WOOP WOOP!!",
            "May the best mind win!",
            "SCIENCE!! Well actually lamp. LAMP WOOP!!",          // lose: Potter taunts you
            "I can't believe I lost to... lamp logic.",             // win: Potter reacts to losing
            "Focus your energy!",
            "We are both disasters. I have a wand though.",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_POPPY] =
        {
            "WOOP WOOP POPPY!! LAMP SAYS HI!!",
            "Hehe! Hi lamp, I guess!",
            "LAMP WINS!! WOOP!!",                                  // lose: Poppy taunts you
            "You're really fun, but also kinda chaotic.",         // win: Poppy reacts to losing
            "Is he okay?",
            "...Hehe!!",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_TJ] =
        {
            "SIX TOES!! THAT'S SCIENCE!! WOOP!!",
            "...Please don't touch my feet.",
            "SPARTA WINS!! LAMP!! WOOP!!",                        // lose: TJ taunts you
            "Tch. Lost to the lamp guy. This never leaves the alley.", // win: TJ reacts to losing
            "Get away from my paws.",
            "Hey have you seen Ea- oh, nevermind.",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_GEORGE] =
        {
            "WOOP WOOP!! SCIENCE VS CURIOSITY!! LAMP!!",
            "Oh!! What's a lamp?! Can I see it?!",
            "LAMP WINS!! WOOP!!",                                  // lose: George taunts you
            "I got distracted by the woop sounds. Very interesting sounds.", // win: George reacts to losing
            "Can I touch lamp?",
            "Oh!! His tail is so long!!",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_WUPPY] =
        {
            "WOOP WOOP DOGGY!! LAMP!!",
            "hi!! I love you too!!  Wanna play?!",
            "LAMP WINS WOOP!!",                                   // lose: Wuppy taunts you
            "That was so fun!! Let's do it again??",                   // win: Wuppy reacts to losing
            "I GOT THE BALL!!",
            "I WANNA SEE LAMP!!",
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_WALRUS] =
        {
            "WOOP WOOP GOLF MAN!! LAMP!!",                        // player1
            "...Great shot, buddy.",                              // player2
            "LAMP BEATS GOLF!! WOOP!!",                           // lose: Craig taunts you
            "Found one in the rough.",                                        // win: Craig reacts to losing
            "I'll show you my best shot.",                                        // taunt1
            "Nice energy, kid.",                                  // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_GARF] =
        {
            "WOOP WOOP GARFIELD!! LAMP!!",                        // player1
            "...I don't even have words.",                        // player2
            "I hate lamp. I hate Mondays. I hate everything.",   // win: Garfield reacts to losing
            "LAMP BEATS LASAGNA CAT!! WOOP!!",                    // lose: Garfield taunts you
            "LAMP!",                                              // taunt1
            "WOOP!",                                              // taunt2
        };

        quotes[CHARACTER_SPARTA]
              [CHARACTER_NONE] =
        {
            "\nWOOP WOOP ROBOT!! LAMP!!",                           // player1
            "\nBEEP BOOP.",                                         // player2
            "BZZT.",                                              // win: CPU reacts to losing
            "LAMP BEATS ROBOT!! SCIENCE!! WOOP!!",               // lose: CPU taunts you
            "BOOP.",                                              // taunt1
            "BEEP.",                                              // taunt2
        };
    }
}
