#pragma once
#include "../dialog.hpp"

// CURIOUS GEORGE
namespace Dialog
{
    inline void InitGeorgeDialog()
    {
        quotes[CHARACTER_GEORGE]
              [CHARACTER_MACCHI] =
        {
            "Oh! Is that coffee? Can I try it?? Oh wait - pong!",
            "Ball. Focus. Go.",
            "I was distracted by everything!",               // win: Macchi reacts to losing
            "Focus is everything. Remember that.",               // lose: Macchi taunts you
            "You ran the wrong way again.",
            "How are you this easily distracted?",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_JELLY] =
        {
            "Oh! Are we playing?! I heard yelling!",
            "Yeah, like I was saying, my fluffy tail got caught one time-",
            "Oh!! I think I won!! Was that right?!",              // lose: Jelly taunts you
            "I think I distracted you with my stories!",                       // win: Jelly reacts to losing
            "George. GEORGE. The ball, buddy.",
            "Chasing your tail again?",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_PENNY] =
        {
            "Oh!! Your crown!! Can I touch -",
            "Absolutely not.",
            "Oh! Now can I touch it?",                   // lose: Penny taunts you
            "You nearly touched my crown. Unacceptable.",        // win: Penny reacts to losing
            "Stop staring at my crown!",
            "Hit the ball! THE BALL!",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_POTTER] =
        {
            "Oh!! A wand!! What does it do?! Can I hold -",
            "No way! Game first.",
            "He won't even let me hold it!", // win: Potter reacts to losing
            "The wand is safe. The match is won.",                // lose: Potter taunts you
            "EYES ON THE BALL, NOT THE WAND.",
            "Did you try to sniff my paddle?",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_SPARTA] =
        {
            "Oh!! What's a lamp?! Where is it?!",
            "WOOP!! GOOD QUESTION!! LAMP!! WOOP!!",
            "Oh!! I won!! What's a lamp though, really?!",        // lose: Sparta taunts you
            "LAMP WINS!!",  // win: Sparta reacts to losing
            "LAMP!",
            "WOOP!",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_POPPY] =
        {
            "Oh!! Your ribbon!! Is it silk?? It looks silk!!",
            "Hehe! Focus, George!",
            "Oh!! I won!! Can I feel it now?!",                   // lose: Poppy taunts you
            "Hehe!! I guess the ribbon was distracting!",  // win: Poppy reacts to losing
            "George!! Stop staring!!",
            "Hehe!!",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_TJ] =
        {
            "Oh!! Six toes!! Can I count them?! One -",
            "No. Play.",
            "Oh!! I won!! I counted to four though!!",            // lose: TJ taunts you
            "Six toes wins. I only got to four. Oh well!!",            // win: TJ reacts to losing
            "BALL. Not toes.",
            "C'mon!",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_WUPPY] =
        {
            "Oh!! A dog!! Wait - are you a cat?! OH!!",
            "I'M A DOG RAISED BY CATS!! YES!!",
            "Oh!! I won!! You're still a dog though, right?!",    // lose: Wuppy taunts you
            "Wuppy wins. Is he a cat? Oh!! I still don't know!!", // win: Wuppy reacts to losing
            "Yay!!",
            "We're both having so much fun!! Are you having fun?!!",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_WALRUS] =
        {
            "Oh!! Are you a golfer?! Is this golf?! Oh!!",        // player1
            "Basically. Great shot.",                             // player2
            "Great shot.",                                        // win: Craig reacts to losing
            "Oh!! I won!! Is that a birdie?!",                    // lose: Craig taunts you
            "Great shot!!",                                       // taunt1
            "Oh!! He said great shot!!",                          // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_GARF] =
        {
            "Oh!! Garfield!! Are you awake?! OH HI!!",            // player1
            "Barely.",                                            // player2
            "Garfield wins. He was barely moving. Oh!!",          // win: Garfield reacts to losing
            "Oh!! I won!! He was awake the whole time!!",         // lose: Garfield taunts you
            "Oh!!",                                               // taunt1
            "Sleepy!!",                                           // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_NONE] =
        {
            "Oh!! What ARE you?!",                    // player1
            "\nBEEP BOOP.",                                         // player2
            "Oh!! I beat the beepy thing!!",                 // lose: CPU taunts you
            "BZZT.",                                              // win: CPU reacts to losing
            "BEEP.",                                 // taunt1
            "BOOP.",                                              // taunt2
        };

    }
}
