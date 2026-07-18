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
            "Oh! Is that coffee?\nCan I try it??\nOh wait- pong!",
            "\nYeah, no - I don't want your germs.",
            "I was distracted by everything!",               // win: Macchi reacts to losing
            "Focus is everything. Remember that.",               // lose: Macchi taunts you
            "You ran the wrong way again.",
            "How are you this easily distracted?",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_JELLY] =
        {
            "\nOh! Are we playing?! I heard yelling!",
            "Yeah, like I was saying\n- my fluffy tail got caught one time-",
            "Oh!! I think I won!!\nWas that right?!",              // lose: Jelly taunts you
            "I think I distracted you with my stories!",                       // win: Jelly reacts to losing
            "George. GEORGE. The ball, buddy.",
            "Chasing your tail again?",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_PENNY] =
        {
            "\nOh!! Your crown!!\nCan I touch-",
            "\nAbsolutely not.",
            "Now can I touch your crown?!",                   // lose: Penny taunts you
            "You nearly touched my crown. Unacceptable.",        // win: Penny reacts to losing
            "Stop staring at my crown!",
            "Hit the ball! THE BALL!",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_POTTER] =
        {
            "\nOh!! A wand!! What does it do?! Can I hold-",
            "\nThe wand choses its whiskers.",
            "He won't even let me hold it!", // win: Potter reacts to losing
            "The wand is safe. The match is won.",                // lose: Potter taunts you
            "Eyes on the ball, not the wand!",
            "Did you try to sniff my paddle?",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_SPARTA] =
        {
            "\nOh!! What's a lamp?! Where is it?!",
            "\nWOOP!! GOOD QUESTION!! LAMP!! WOOP!!",
            "Oh!! I won!!\nWhat's a lamp though, really?!",        // lose: Sparta taunts you
            "LAMP WINS!!",  // win: Sparta reacts to losing
            "LAMP!",
            "WOOP!",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_POPPY] =
        {
            "Oh!! Your ribbon!!\nIs it silk??\nIt looks like silk!!",
            "\nHehe! Focus, George!",
            "Oh!! I won!!\nCan I feel it now?!",                   // lose: Poppy taunts you
            "Hehe!! I guess the ribbon was distracting!",  // win: Poppy reacts to losing
            "George!! Stop staring!!",
            "Hehe!! You're kinda adorable!!",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_TJ] =
        {
            "\nOh!! Six toes!!\nCan I count them?! One-",
            "\nNo. Play the game and don't stare",
            "Oh!! I won!!\nI only counted to four though!!",            // lose: TJ taunts you
            "Be glad I don't have my lucky shoelace.",
            "I don't think he\ncan count to 6...",            // win: TJ reacts to losingd
            "HIT THE BALL. Not my toes.",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_WUPPY] =
        {
            "Oh!! Wait- are you a cat?!\nHave you seen Mr. Squeakers?!!",
            "I'M A DOG RAISED BY CATS!!\nSORRY I DON'T HAVE YOUR SQUEAKY TOY!!",
            "Oh!! I won!! You're still a dog though, right?!",    // lose: Wuppy taunts you
            "OOOPS, I DID HAVE YOUR TOY!!\nIT'S A LITTLE CHEWED - SORRY!!", // win: Wuppy reacts to losing
            "YAY!! CAN WE DO IT AGAIN?",
            "WE'RE BOTH HAVING SO MUCH FUN!! ARE YOU HAVING FUN?!!",
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_WALRUS] =
        {
            "\nOh!! Are you a golfer?!\nIs this a golf course?!",        // player1
            "It looks like pong, but basically it's the same thing.",                             // player2
            "Oh!! I won!!\nIs that a birdie?!",                    // lose: Craig taunts you
            "Great shot\n(by me).",                                        // win: Craig reacts to losing
            "Right down the middle!",                                       // taunt1
            "Great Shot!",                          // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_GARF] =
        {
            "\nGarfield!! Oh hi!!\nAre you awake?!",            // player1
            "\nBarely.\nWhy are you bothering me?",                                            // player2
            "Oh!! I won!!\nHe was napping the whole time!!",         // lose: Garfield taunts you
            "Good luck kid,\nyou're gonna need it.",          // win: Garfield reacts to losing
            "He makes Odie\nlook like a genius..",                                               // taunt1
            "Why am I even trying?",                                           // taunt2
        };

        quotes[CHARACTER_GEORGE]
              [CHARACTER_NONE] =
        {
            "\nOh!! What ARE you?!",                    // player1
            "\nBEEP BOOP.",                                         // player2
            "Oh!! I beat the beepy thing!!",                 // lose: CPU taunts you
            "BZZT. BEEP.",                                              // win: CPU reacts to losing
            "BEEP.",                                 // taunt1
            "BOOP.",                                              // taunt2
        };

    }
}
