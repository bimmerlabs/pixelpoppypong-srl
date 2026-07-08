#pragma once
#include "../dialog.hpp"

// WALRUS (CRAIG STADLER)
namespace Dialog
{
    inline void InitWalrusDialog()
    {
        quotes[CHARACTER_WALRUS]
              [CHARACTER_MACCHI] =
        {
            "A ball, a hole, a stick; Yeah, pong is basically just golf.",
            "This isn't golf though?  I'm so confused..",
            "Right down the middle!",                             // lose: Craig taunts you
            "Smooth finish. Good round.",                         // win: Macchi reacts to losing
            "What kind of cat are you anyway?",
            "That is NOT a golf ball!",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_JELLY] =
        {
            "Shhh - Quiet on the tee.",
            "Uh, What's a tee??",
            "Hmmm, you missed it just a little.",                  // lose: Craig taunts you
            "Are you even in the right game?",                     // win: Jelly reacts to losing
            "His cat-fur looks so strange.",
            "Hmmm, maybe he is a cat...",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_PENNY] =
        {
            "Nice golf course you've got here!",
            "It's a royal court.  Now tremble before royalty!",
            "I'll show you my best shot...",                        // lose: Craig taunts you
            "You play pong well. For a golfer.",                       // win: Penny reacts to losing
            "Stop calling it a fairway.",                         // taunt1
            "Eww! Yuck! Arm Hair!",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_POTTER] =
        {
            "Is that a 9-iron? No... weird club.",
            "Uh, it's a wand.  It's magic??",
            "Found one in the rough.",           // lose: Craig taunts you
            "He hits straight. The wand was no help.",            // win: Potter reacts to losing
            "Only magic could make you a real cat!",
            "You must have teleported from another realm.",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_SPARTA] =
        {
            "First tee is... wherever this is.",
            "WOOP!! I LOVE TEA!!",
            "Great birdie! ...by me.",                                      // lose: Craig taunts you
            "WANT TO SEE MY LAMP?",                                // win: Sparta reacts to losing
            "WOOP!",
            "LAMP!",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_POPPY] =
        {
            "Good weather for a round of golf.",
            "Hehe! You're funny!\nBut this is pong?",
            "Well done!\nThis is still basically golf though.",                                         // lose: Craig taunts you
            "Hehe! Nice game, Mr. Golf man!!",                         // win: Poppy reacts to losing
            "Hehe! You're cute, but I think you're confused!",
            "You have lovely form. Hehe!",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_TJ] =
        {
            "I've never played golf against a six-toed cat before.",
            "First time for everything.",
            "I showed you my best shot.",                        // lose: Craig taunts you
            "Tch. The street beats golf. Every time.",             // win: TJ reacts to losing
            "You're the hairiest cat I've ever seen.",
            "Where did you come from anyway?",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_GEORGE] =
        {
            "Ready to play some - hey, stop smelling the ball.",
            "Oh!! It smells like rubber!!",
            "Any way you spin it, this is basically the same as golf.",                                       // lose: Craig taunts you
            "What are you doing with that club?  Oh!!",          // win: George reacts to losing
            "Oh!! Are you a cat?",
            "Oh!! I'm sure you are a cat!",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_WUPPY] =
        {
            "You're a dog. This is golf - dogs don't play golf?",
            "BUT I COULD BE A CAT!!\nWAIT - GOLF?!  WHAT'S THAT?\nIT SOUNDS FUN!!",
            "Yeah, pretty sure dogs can't play golf.",
            "YAY CRAIG!! AM I A GOOD BOY?!",        // win: Wuppy reacts to losing
            "YAY!! CAN WE PLAY GOLF NOW?",
            "THAT WAS FUN!! AGAIN!!",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_GARF] =
        {
            "You look like you'd rather be elsewhere.",
            "I didn't come all this way for nothing. Actually, I did. But still.",
            "Found one in the rough.",                            // lose: Craig taunts you
            "He's the only one here less bothered than me. I respect that.",
            "I don't care. Now where's my Lasagna?",                             // win: Garfield reacts to losing
            "Yawn.  Golf is so boring.",
        };

        quotes[CHARACTER_WALRUS]
              [CHARACTER_NONE] =
        {
            "\nUnusual caddie.",                                    // player1
            "\nBEEP.",                                              // player2
            "Right down the middle!",                             // lose: Craig taunts you
            "That made my shot just a little tougher.",           // taunt2
            "BOOP!",                  // taunt1
            "BZZT.",                                              // win: CPU reacts to losing
        };
    }
}
