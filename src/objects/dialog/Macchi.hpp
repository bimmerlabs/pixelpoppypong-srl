#pragma once
#include "../dialog.hpp"

// MACCHATTO
namespace Dialog
{
    inline void InitMacchiDialog()
    {
        quotes[CHARACTER_MACCHI]
              [CHARACTER_JELLY] =
        {
            "Hey - have you seen my favorite mug?\nI really miss it..", // player1
            "Oh sure, I think I -\nwait, are we starting?", // player2
            "You know what pairs well with espresso? Winning.",  // Win
            "Ha! I showed you. Good game though, right?",        // Lose
            "I don't actually like coffee, it gives me the jitters!", // taunt1
            "I had a dream about the ball once.\nTrue story!",  // taunt2
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_PENNY] =
        {
            "\nBy the way,\nI don't bow.",
            "\n\nYou will...",
            "This crown is...\n\ntemporarily tarnished.",              // win: Penny reacts to losing
            "As I expected, you will bow.",                       // lose: Penny taunts you
            "Don't let it go to your head.",
            "Even royalty can appreciate espresso form.",
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_POTTER] =
        {
            "\nMagic won't help your backswing.",
            "\n\nWe'll see about that!",
            "My wand...\n\nit betrayed me again!",                        // win: Potter reacts to losing
            "No enchantment required.",                            // lose: Potter taunts you
            "By Merlin's whiskers!",
            "Wingardium Pongiosa!!",
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_SPARTA] =
        {
            "I've seen smarter cats in the bottom of my missing coffee mug.",
            "I love lamp! Wait -\nwhat about a missing mug?",
            "Lamp didn't help...\n\nLamp never helps!",               // win: Sparta reacts to losing
            "Yay! Lamp did it! WOOP!",
            "WOOP WOOP WOOP!",
            "WOOP WOOP WOOP!",
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_POPPY] =
        {
            "\nDon't let the fluff fool you.",
            "\n\nHehe... too late!",
            "...Okay. You're pretty good!\n\nSorry I couldn't find your mug..",                              // win
            "Cute match. I win! Hehe!",                            // lose: Poppy taunts you
            "Oops! That was close!",
            "Hehe! This is fun!",
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_TJ] =
        {
            "Try not to leave marks on the court.",
            "These paws have more skills than your whole body.",
            "Pfft. Lucky roast.",                                  // win: TJ reacts to losing
            "Street beats cafe`.\n\nEvery time.",                     // lose: TJ taunts you
            "Too slow.",
            "Stay sharp, coffee cat.",
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_GEORGE] =
        {
            "Eyes on the ball, please.",
            "Oh! Okay! Wait -\nis that a new ball? It's so round!",
            "Focus is everything.\n\nRemember that!",               // win:
            "I got distracted by my tail!\n\nIt's following me!", // lose: George reacts to losing
            "Is the ball new? It looks new.",
            "Oh! Have you seen my bell?",
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_WUPPY] =
        {
            "What did you do to my coffee mug?\nIt's smashed to pieces!",
            "OH HI! I DIDN'T MEAN TO KNOCK IT OVER I PROMISE!",
            "Mug or no mug, I still win!",                       // lose: Wuppy taunts you
            "THAT WAS FUN!!\n\nCAN WE FIX YOUR MUG LATER??",        // win: Wuppy reacts to losing
            "YAY!!  WE'RE PLAYING WITH A CAT-BALL!",
            "DID I DO GOOD?!",
        };
        
        quotes[CHARACTER_MACCHI]
              [CHARACTER_WALRUS] =
        {
            "This isn't a golf course...",                          // player1
            "Looks like a fairway to me.",                       // player2
            "You got yours inside mine!\nWell done.",                        // win: Craig reacts to losing
            "Hmm.. You missed it a little.",              // lose: Craig taunts you
            "Great shot!\n(by me)",                                        // taunt1
            "See? This is basically golf.",                                        // taunt2
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_GARF] =
        {
            "Wake up! We're playing cat-pong.",                            // player1
            "I know... I hate it.",                                 // player2
            "I could've been eating right now.",                  // win: Garfield reacts to losing
            "Yep, now it's lasagna time...",      // lose: Garfield taunts you
            "I could really use a nap right now.",                  // taunt1
            "Why am I even here?",                              // taunt2
        };

        quotes[CHARACTER_MACCHI]
              [CHARACTER_NONE] =
        {
            "\n...What are you?",                                   // player1
            "\nBEEP.",                                              // player2
            "Whatever you are, you lose.",                       // lose: CPU taunts you
            "BEEP. BOOP!",                                              // taunt1
            "BZZT.",                                              // win: CPU reacts to losing
            "BEEP.",                                              // taunt2
        };
    }
}
